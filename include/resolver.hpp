#pragma once

#include "endpoint_info.hpp"
#include "tcp.hh"
#include <cstdint>
#include <netdb.h>
#include <string>
#include <vector>

namespace conn_resolver {

struct ResolverHints {
	int32_t endpoint_type;
	int32_t ip_domain;
	int32_t protocol;
	int32_t flags;
};

addrinfo craft_resolver_hints(ResolverHints &hints);

class Resolver {
	using QueryResults = std::vector<AddressInfo>;
	using RawResults = addrinfo *;
public:
	Resolver(std::string hostname, std::string service);
	Resolver();
	~Resolver();
	QueryResults results();
	QueryResults udp_nodes();
	QueryResults tcp_nodes();
	tcp::Connection try_connect_tcp();
	void try_connect_udp(); // TODO: create UDPConnection class
	std::string print_results();

private:
	QueryResults query_results_;
};
} // namespace resolver
