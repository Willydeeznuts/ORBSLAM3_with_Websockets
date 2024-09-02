// WebSocketClient.h
#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>
#include <thread>  // Add this line

class WebSocketClient {
public:
    WebSocketClient(const std::string& host, const std::string& port);
    void send(const std::string& message);
    void close();

private:

    void connect();  // New method to handle connection and reconnection
    
    std::string host_;  // Store host for reconnection
    std::string port_;  // Store port for reconnection
    
    boost::asio::io_context ioc_;
    boost::asio::ip::tcp::resolver resolver_;
    boost::beast::websocket::stream<boost::asio::ip::tcp::socket> ws_;
};

#endif // WEBSOCKETCLIENT_H
