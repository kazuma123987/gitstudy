#include "asio.hpp"
#include <iostream>
using asio::ip::tcp;

int main(int argc, char *argv[])
{
    try
    {
        //(1)通过tcp::socket类定义一个tcp client对象socket
        asio::io_service io;
        tcp::socket socket(io);

        //(2)通过connect函数连接服务器，打开socket连接。
        tcp::endpoint end_point(asio::ip::address::from_string("127.0.0.1"), 3200);
        socket.connect(end_point);
        std::array<char, 128> buf;
        asio::error_code error;

        for (;;)
        {
            //(3)通过read_some函数来读数据
            size_t len = socket.read_some(asio::buffer(buf), error);

            if (error == asio::error::eof)
            {
                continue; // connection closed cleadly by peer
            }
            else if (error)
            {
                throw asio::system_error(error); // some other error
            }

            std::cout.write(buf.data(), len);
            buf.fill(0);
        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}