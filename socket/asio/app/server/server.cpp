// #define ASIO_STANDALONE
// #ifndef _WIN32_WINNT
// #define _WIN32_WINNT 0x0a00
// #endif
#include "asio.hpp"
#include <iostream>

#define PORT 3200
#define IPV4
// #define IPV4

std::vector<std::string> temp_vec;

class AsyncServer
{
public:
    // 构造函数
    AsyncServer(asio::io_service &io, asio::ip::tcp::endpoint &ep) : io_service(io), tcp_acceptor(io, ep)
    {
        // acceptor(io_service,ep);
        accept_register();
    }
    // 创建新的socket，并注册<接收客户端连接>的回调函数
    void accept_register()
    {
        // auto tcp_socket(new asio::ip::tcp::socket(this->io_service));//使用了两次内存分配，一次是socket对象，一次是shared_ptr对象
        auto tcp_socket = std::make_shared<asio::ip::tcp::socket>(this->io_service);
        // 当有连接进入时回调accept_handler函数
        this->tcp_acceptor.async_accept(*tcp_socket, std::bind(&AsyncServer::accept_handler, this, asio::placeholders::error, tcp_socket));
    }

private:
    asio::io_service &io_service;
    asio::ip::tcp::acceptor tcp_acceptor;

    void accept_handler(const asio::error_code &ec, std::shared_ptr<asio::ip::tcp::socket> tcp_socket)
    {
        if (ec)
            return;
        // 输出客户端连接信息
        std::cout << "server:remote ip:" << tcp_socket->remote_endpoint().address() << std::endl;
        std::cout << "server:remote port:" << tcp_socket->remote_endpoint().port() << std::endl;
        // 异步向客户端发送数据，发送完成时调用write_handler
        tcp_socket->async_write_some(asio::buffer(temp_vec[0]), std::bind(&AsyncServer::write_handler, this, asio::placeholders::error));
        // 再次创建新的tcp socket，并注册<接收客户端连接>的回调函数
        accept_register();
    }

    void write_handler(const asio::error_code &)
    {
        std::cout << "server:send msg complete!" << std::endl;
    }
};

int main(int argc, char *argv[])
{
    try
    {
        temp_vec.emplace_back(std::string("server:I heard you!"));
        // 定义io_service对象
        asio::io_service io_service;
        // 定义服务端endpoint对象(协议和监听端口)
#ifdef IPV4
        asio::ip::tcp::endpoint tcp_endpoint(asio::ip::tcp::v4(), PORT);
#endif

#ifdef IPV6
        asio::ip::tcp::endpoint tcp_endpoint(asio::ip::tcp::v6(), PORT);
#endif
        // 启动异步服务
        AsyncServer server(io_service, tcp_endpoint);
        // 等待异步完成
        io_service.run();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}