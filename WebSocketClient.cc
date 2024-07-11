// WebSocketClient.cc
#include "WebSocketClient.h"
#include <boost/asio/connect.hpp>
#include <boost/beast/websocket/stream.hpp>
#include <iostream>

WebSocketClient::WebSocketClient(const std::string& host, const std::string& port)
    : resolver_(ioc_), ws_(ioc_) {
    auto const results = resolver_.resolve(host, port);
    boost::asio::connect(ws_.next_layer(), results.begin(), results.end());
    ws_.handshake(host, "/");
}

void WebSocketClient::send(const std::string& message) {
    ws_.write(boost::asio::buffer(message));
}

void WebSocketClient::close() {
    ws_.close(boost::beast::websocket::close_code::normal);
}
