﻿#include <iostream>
#include "GameProxyConfig.h"

#include "asio.hpp"

using asio::ip::tcp;

const int max_length = 1024;

void session(tcp::socket sock)
{
    try
    {
        for (;;)
        {
            char data[max_length];

            std::error_code error;
            size_t length = sock.read_some(asio::buffer(data), error);
            if (error == asio::stream_errc::eof)
                break; // Connection closed cleanly by peer.
            else if (error)
                throw std::system_error(error); // Some other error.

            asio::write(sock, asio::buffer(data, length));
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}

void server(asio::io_context& io_context, unsigned short port)
{
    tcp::acceptor a(io_context, tcp::endpoint(tcp::v4(), port));
    for (;;)
    {
        tcp::socket sock(io_context);
        a.accept(sock);
        std::thread(session, std::move(sock)).detach();
    }
}

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: blocking_tcp_echo_server <port>\n";
            return 1;
        }

        asio::io_context io_context;

        server(io_context, std::atoi(argv[1]));
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

