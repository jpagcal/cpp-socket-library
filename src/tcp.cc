#include "../include/networking.hh"
#include "../include/tcp.hh"
#include <stdexcept>
#include <sys/types.h>
#include <netdb.h>
#include <system_error>

namespace tcp {

Connection Connection::resolve(const std::string host, const std::string service, const int domain) {
	addrinfo hints, *res;

	// zero out hints
	memset(&hints, 0, sizeof(addrinfo));

	hints.ai_family = domain;
	hints.ai_socktype = networking::socket_type::tcp;

	if (!(getaddrinfo(host.c_str(), service.c_str(), &hints, &res))) {
		freeaddrinfo(res);
		throw std::system_error(errno, std::generic_category());
	}

	int socketFD{ socket(domain, networking::socket_type::tcp, 0) };

	// connect the socket to the host
	for (addrinfo *cur{ res }; res != nullptr; cur = cur->ai_next) {
		if (!(connect(socketFD, cur->ai_addr, cur->ai_addrlen))) {
			break;
		}

		// for case n - 1, if it hasnt connected at this point we may throw an exception
		if (cur->ai_next == nullptr) {
			freeaddrinfo(res);
			throw std::runtime_error("Failed to connect to a host");
		}
	}

	freeaddrinfo(res);

	return Connection(socketFD);
}

} // namespace tcp
