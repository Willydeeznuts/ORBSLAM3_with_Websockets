// WebSocketClient.cc
#include "WebSocketClient.h"
#include <boost/asio/connect.hpp>
#include <boost/beast/websocket/stream.hpp>
#include <iostream>
#include <thread>  // Add this line

WebSocketClient::WebSocketClient(const std::string& host, const std::string& port)
    : host_(host), port_(port), resolver_(ioc_), ws_(ioc_) {
    connect();
}

void WebSocketClient::connect() {
    bool connected = false;
    while (!connected) {
        try {
            auto const results = resolver_.resolve(host_, port_);
            boost::asio::connect(ws_.next_layer(), results.begin(), results.end());

            // Set the TCP keep-alive option to prevent disconnection
            boost::asio::socket_base::keep_alive keep_alive_option(true);
            ws_.next_layer().set_option(keep_alive_option);

            ws_.handshake(host_, "/");
            connected = true;
        } catch (const std::exception &e) {
            std::cerr << "Failed to connect to WebSocket server: " << e.what() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));  // Retry after a delay
        }
    }
}

void WebSocketClient::send(const std::string& message) {
    try {
        ws_.write(boost::asio::buffer(message));
    } catch (const std::exception &e) {
        std::cerr << "WebSocket send failed: " << e.what() << std::endl;
        connect();  // Attempt to reconnect if send fails
    }
}

void WebSocketClient::close() {
    ws_.close(boost::beast::websocket::close_code::normal);
}
