#ifndef SOCKET_ADDRESS_H
#define SOCKET_ADDRESS_H

#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <memory>

enum SockFamily {
	IPv4 = AF_INET,
	IPv6 = AF_INET6,
};

enum SockType {
	STREAM = SOCK_STREAM,
	DGRAM = SOCK_DGRAM,
};

struct SockAddr {
public:
	// Creates address which is mostly suitable for server
	SockAddr(SockFamily family, SockType type, const std::string& port);
	// Creates address which is mostly suitable for client
	SockAddr(SockType type, const std::string& node, const std::string& port);
	SockAddr(const SockAddr& other) = delete;
	SockAddr& operator=(const SockAddr& other) = delete;
	SockAddr(SockAddr&& other);
	SockAddr& operator=(SockAddr&& other);
	~SockAddr();
	int GetFamily() const { return ai_->ai_family; }
	int GetSocketType() const { return ai_->ai_socktype; }
	int GetProtocol() const { return ai_->ai_protocol; }
	struct sockaddr_storage& GetAddress() const { return *((sockaddr_storage *)(ai_->ai_addr)); }
	socklen_t GetAddrLen() const { return ai_->ai_addrlen; }
private:
	std::unique_ptr<struct addrinfo, void(*)(struct addrinfo *)> ai_ =
		std::unique_ptr<struct addrinfo, void(*)(struct addrinfo *)>
		(nullptr, [](struct addrinfo *p){freeaddrinfo(p);});
};

#endif // SOCKET_ADDRESS_H
