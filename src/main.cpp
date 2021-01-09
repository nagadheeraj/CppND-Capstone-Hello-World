#include <iostream>
#include <future>
#include <array>
#include <memory>
#include "socket.h"
#include "counter.h"

static void serve_client(Socket client, std::shared_ptr<Counter> visit_count) {
	std::array<char, 1024> buf;
	int ret;
	std::string ni_name = client.GetNumericName();

	std::cout << ni_name << " connected\n";
	client.Recv(buf.data(), buf.size());
	std::string response(
		"HTTP/1.1 200 OK\r\n"
		"Connection: close\r\n"
		"Content-Type: text/plain\r\n\r\n"
		"Visit count: ");
	response += std::to_string(visit_count->Increment()) + "\r\n";
	client.Send(response);

	std::cout << ni_name << " dis-connected\n";
}

static void start_server() {
	SockAddr addr(SockFamily::IPv4, SockType::STREAM, "8080");
	Socket server(addr);
	std::shared_ptr<Counter> visit_count = std::make_shared<Counter>(0);

	server.Bind();
	server.Listen(10);
	while (true) {
		auto client = server.Accept();
		std::thread(&serve_client, std::move(client), visit_count).detach();
	}
}

int main() {
	try {
		start_server();
	}
	catch (const std::exception& e) {
		std::cerr << "Server error: " << e.what() << "\n";
	}

	return 0;
}
