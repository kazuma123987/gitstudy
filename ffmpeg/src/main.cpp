#include "stdio.h"

#ifdef __cplusplus
extern "C"
{
#endif
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
#ifdef __cplusplus
}
#endif
//注意我们把rgbFrame->data[0]与buffer关联了,rgbFrame->data[0]里面存有所有rgb数据,
//即R00,G00,B00,R01,B01,G01...R_0_(WIDTH-1),G_0_(WIDTH-1),B_0_(WIDTH-1)
//R10,G10,B10...
//...
//同时rgbFrame->linesize[0]=3*width
//!注意如果转换格式是AV_PIX_FMT_RGB32,则为RGBA交错,使用fwrite时就不能直接连续写3*width,要单独处理alpha通道
void SaveFrame(AVFrame *rgbFrame, int width, int height, int index)
{
    FILE *fp = NULL;
    char imageName[25];
    sprintf(imageName, "res/image/frame%d.ppm", index);
    fopen_s(&fp, imageName, "wb");
    if (fp == NULL)
        return;
    // 写文件头
    fprintf(fp, "P6\n%d %d\n255\n", width, height);
    // 写数据(逐行)
    for (int i = 0; i < height; i++)
        fwrite(rgbFrame->data[0] + i * rgbFrame->linesize[0], sizeof(unsigned char), width* 3, fp);
    fclose(fp);
}
int main(int argc, char *argv[])
{
    char videoPath[] = "res/gura.mp4";
    // 为format上下文分配空间
    AVFormatContext *fmtCtx = avformat_alloc_context();
    // 打开视频文件
    if (avformat_open_input(&fmtCtx, videoPath, NULL, NULL))
        printf("failed to open the video\n");
    // 查找流信息
    if (avformat_find_stream_info(fmtCtx, NULL) < 0)
        printf("failed to find stream info\n");
    // 查找流索引(这里是视频流)
    int streamIndex = -1;
    streamIndex = av_find_best_stream(fmtCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    if (streamIndex == -1)
        printf("failed to find a video stream\n");
    // 获取编解码器参数
    AVCodecParameters *codecPar = fmtCtx->streams[streamIndex]->codecpar;
    // 通过编解码参数中的id获取编解码器
    const AVCodec *codec = avcodec_find_decoder(codecPar->codec_id);
    // 根据选中的编解码器为编解码器上下文分配空间
    AVCodecContext *codecCtx = avcodec_alloc_context3(codec);
    // 根据编解码参数为编解码器上下文赋值
    avcodec_parameters_to_context(codecCtx, codecPar);
    // 打开编解码器
    avcodec_open2(codecCtx, codec, NULL);
    // 为packet分配空间
    AVPacket *packet = av_packet_alloc();
    // 为packet的数据区分配空间
    av_new_packet(packet, codecCtx->width * codecCtx->height);
    // 为视频帧分配空间
    AVFrame *rgbFrame = av_frame_alloc();
    AVFrame *yuvFrame = av_frame_alloc();
    // 计算需要的buffer大小
    int bufferSize = av_image_get_buffer_size(AV_PIX_FMT_RGB24, codecCtx->width, codecCtx->height, 1); // 格式、宽、高、对齐字节
    unsigned char *buffer = (unsigned char *)av_malloc(sizeof(unsigned char) * bufferSize);
    // 关联buffer和rgbFrame的数据区(即数据区改变则buffer也会改变)
    av_image_fill_arrays(
        (uint8_t **)rgbFrame->data, rgbFrame->linesize,                  // 目标数据区和数据区宽度
        buffer, AV_PIX_FMT_RGB24, codecCtx->width, codecCtx->height, 1); // 源数据、格式、宽、高、对齐字节
    // 数据转换上下文设置(这里是yuv转rgb)
    struct SwsContext *swsCtx = sws_getContext(
        codecCtx->width, codecCtx->height, codecCtx->pix_fmt, // 源文件宽、高、像素格式
        codecCtx->width, codecCtx->height, AV_PIX_FMT_RGB24,  // 目标文件宽、高、像素格式
        SWS_BICUBIC, NULL, NULL, NULL);                       // 缩放算法类型、源过滤器、目标过滤器、缩放算法参数

    // 读取帧
    int count = 0;
    while (av_read_frame(fmtCtx, packet) >= 0)
    {
        if (packet->stream_index == streamIndex)
        {
            if (avcodec_send_packet(codecCtx, packet) == 0 && avcodec_receive_frame(codecCtx, yuvFrame) == 0)
            {
                if (count++ >= 1799 && count <= 1960)//取1800-1960帧的yuv数据转为RGB并保存为ppm文件
                {
                    sws_scale(
                        swsCtx, (const uint8_t *const *)yuvFrame->data, yuvFrame->linesize, // 转换上下文、源数据、源stride
                        0, codecCtx->height, rgbFrame->data, rgbFrame->linesize);           // 目标宽、高、目标数据、目标stride
                    SaveFrame(rgbFrame, codecCtx->width, codecCtx->height, count);
                }
            }
        }
        av_packet_unref(packet); // 清空数据区
    }
    printf("total frames:%d\n", count);
    // 释放内存
    av_packet_free(&packet);
    avcodec_free_context(&codecCtx);
    avformat_free_context(fmtCtx);
    av_frame_free(&rgbFrame);
    av_frame_free(&yuvFrame);
    av_free(buffer);
    return 0;
}