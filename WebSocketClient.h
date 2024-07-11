// WebSocketClient.h
#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>

class WebSocketClient {
public:
    WebSocketClient(const std::string& host, const std::string& port);
    void send(const std::string& message);
    void close();

private:
    boost::asio::io_context ioc_;
    boost::asio::ip::tcp::resolver resolver_;
    boost::beast::websocket::stream<boost::asio::ip::tcp::socket> ws_;
};

#endif // WEBSOCKETCLIENT_H

