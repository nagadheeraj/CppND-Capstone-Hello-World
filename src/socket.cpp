#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include "socket.h"

Socket::Socket(int fd, struct sockaddr_storage& sockaddr, socklen_t socklen) :
	fd_(fd), sockaddr_(sockaddr), socklen_(socklen) {}

Socket::Socket(SockAddr& addr) :
	sockaddr_(addr.GetAddress()),
	socklen_(addr.GetAddrLen()) {
	fd_ = socket(addr.GetFamily(), addr.GetSocketType(),
		     addr.GetProtocol());
	if (fd_ == -1)
		throw std::runtime_error(strerror(errno));
}

void Socket::Bind() const {
	if (bind(fd_, (const struct sockaddr *)(&sockaddr_),
		 socklen_) != 0)
		throw std::runtime_error(strerror(errno));
};

void Socket::Listen(int backlog) const {
	if (listen(fd_, backlog) != 0)
		throw std::runtime_error(strerror(errno));
}

Socket Socket::Accept() const {
	struct sockaddr_storage clientaddr;
	socklen_t clientlen = sizeof(clientaddr);

	auto client_fd = accept(fd_, (struct sockaddr*)&clientaddr, &clientlen);
	if (client_fd == -1)
		throw std::runtime_error(strerror(errno));

	return Socket(client_fd, clientaddr, clientlen);
}

void Socket::Connect() const {
	if (connect(fd_, (const struct sockaddr *)(&sockaddr_),
		    socklen_) != 0)
		throw std::runtime_error(strerror(errno));
}

ssize_t Socket::Send(const char *buf, const size_t len) const {
	auto ret = send(fd_, buf, len, 0);
	if (ret == -1)
		throw std::runtime_error(strerror(errno));

	return ret;
}

ssize_t Socket::Send(const std::string& buf) const {
	auto ret = send(fd_, buf.c_str(), buf.size(), 0);
	if (ret == -1)
		throw std::runtime_error(strerror(errno));

	return ret;
}

ssize_t Socket::Recv(char *buf, const size_t len) const {
	auto ret = recv(fd_, buf, len, 0);
	if (ret == -1)
		throw std::runtime_error(strerror(errno));

	return ret;
}

std::string Socket::GetNumericName() const {
	char host_addr[100];
	char serv_addr[100];
	auto ret = getnameinfo((const struct sockaddr *)&sockaddr_, socklen_,
			       host_addr, sizeof(host_addr), serv_addr,
			       sizeof(serv_addr), NI_NUMERICHOST);
	if (ret != 0)
		throw std::runtime_error(gai_strerror(ret));

	return std::string(host_addr) + ": " + std::string(serv_addr);
}

Socket::Socket(Socket&& other) {
	fd_ = other.fd_;
	sockaddr_ = other.sockaddr_;
	socklen_ = other.socklen_;
	other.fd_ = -1;
	other.sockaddr_ = (const struct sockaddr_storage) {0};
	other.socklen_ = 0;
}

Socket& Socket::operator=(Socket&& other) {
	if (&other == this)
		return *this;

	fd_ = other.fd_;
	sockaddr_ = other.sockaddr_;
	socklen_ = other.socklen_;
	other.fd_ = -1;
	other.sockaddr_ = (const struct sockaddr_storage) {0};
	other.socklen_ = 0;
	return *this;
}

Socket::~Socket() {
	if (fd_ != -1)
		close(fd_);
}
