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
    AVFrame *yuvFrame = av_frame_alloc();
    // 读取帧
    int count = 0;
    int width=codecCtx->width;
    int height=codecCtx->height;
    char yuvName[]="res/gura_yuv420p.yuv";
    FILE *fp=NULL;
    fopen_s(&fp,yuvName,"w+b");
    while (av_read_frame(fmtCtx, packet) >= 0)
    {
        if (packet->stream_index == streamIndex)
        {
            count++;
            if (avcodec_send_packet(codecCtx, packet) == 0 && avcodec_receive_frame(codecCtx, yuvFrame) == 0)
            {
                fwrite(yuvFrame->data[0],sizeof(unsigned char),width*height,fp);
                fwrite(yuvFrame->data[1],sizeof(unsigned char),width*height/4,fp);
                fwrite(yuvFrame->data[2],sizeof(unsigned char),width*height/4,fp);
            }
        }
        av_packet_unref(packet); // 清空数据区
    }
    fclose(fp);
    printf("total frames:%d\n", count);
    // 释放内存
    av_packet_free(&packet);
    avcodec_free_context(&codecCtx);
    avformat_free_context(fmtCtx);
    av_frame_free(&yuvFrame);
    return 0;
}