#ifndef SOCKET_STREAM_H_
#define SOCKET_STREAM_H_

#include <memory>
#include <string>
#include <sys/socket.h>
#include "socket_address.h"

class Socket {
public:
	// Creates server socket and binds to the local host to
	// accept connections on any interface
	Socket(SockAddr& addr);
	void Listen(int backlog) const;
	void Bind() const;
	Socket Accept() const;
	void Connect() const;
	ssize_t Send(const char *buf, const size_t len) const;
	ssize_t Send(const std::string& buf) const;
	ssize_t Recv(char *buf, const size_t len) const;
	std::string GetNumericName() const;
	Socket(const Socket& other) = delete;
	Socket& operator=(const Socket& other) = delete;
	Socket(Socket&& other);
	Socket& operator=(Socket&& other);
	~Socket();
private:
	Socket(int fd, struct sockaddr_storage& sockaddr, socklen_t socklen);
	int fd_ {-1};
	struct sockaddr_storage sockaddr_ {};
	socklen_t socklen_;
};

#endif // SOCKET_STREAM_H_
