#pragma once

#include <sys/socket.h>
#include <cstdint>

namespace networking {
inline namespace constants {
namespace domain {
	constexpr int ipv4 = AF_INET;
	constexpr int ipv6 = AF_INET6;
} // namespace domain

namespace socket_type {
	constexpr int tcp = SOCK_STREAM;
	constexpr int udp = SOCK_DGRAM;
} // namespace socket_type
} // namespace constants
} // namespace networking
