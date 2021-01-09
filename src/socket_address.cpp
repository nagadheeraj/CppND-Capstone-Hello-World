#include <sys/types.h>
#include <iostream>
#include "socket_address.h"

SockAddr::SockAddr(SockFamily family, SockType type, const std::string& port) {
	struct addrinfo hints = {};
	struct addrinfo *res;

	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = family;
	hints.ai_socktype = type;
	if (getaddrinfo(nullptr, port.c_str(), &hints, &res) != 0)
		throw std::runtime_error("getaddrinfo() failed");

	ai_.reset(res);
}

SockAddr::SockAddr(SockType type, const std::string& node, const std::string& port) {
	struct addrinfo hints = {};
	struct addrinfo *res;

	hints.ai_socktype = type;
	if (getaddrinfo(node.c_str(), port.c_str(), &hints, &res) != 0)
		throw std::runtime_error("getaddrinfo() failed");

	ai_.reset(res);
}

SockAddr::SockAddr(SockAddr&& other) {
	ai_ = std::move(other.ai_);
}

SockAddr& SockAddr::operator=(SockAddr&& other) {
	if (this == &other)
		return *this;

	ai_ = std::move(other.ai_);
	return *this;
}

SockAddr::~SockAddr() {
}
