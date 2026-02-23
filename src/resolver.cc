#include <cstddef>
#include <cstring>
#include <netdb.h>
#include "../include/resolver.hpp"

namespace conn_resolver {
addrinfo craft_resolver_hints(ResolverHints &hints) {
	addrinfo raw_hints{};

	std::memset(&raw_hints, 0, sizeof(addrinfo));

	raw_hints.ai_flags = hints.flags;
	raw_hints.ai_family = hints.ip_domain;
	raw_hints.ai_socktype = hints.endpoint_type;
	raw_hints.ai_protocol = hints.protocol;

	return raw_hints;
}

}
