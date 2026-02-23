#pragma once

#include <cstdint>
#include <string>
#include <netdb.h>

inline namespace endpoint_info {

class Address {
public:

private:
};

class IPV4Address : Address{

};

class IPV6Address : Address {

};

class AddressInfo {
public:
	AddressInfo(addrinfo *raw_node) :
		raw_node_{ raw_node },
		canonical_name_{ raw_node->ai_canonname } {}
	//TODO: figure out address representation

private:
	addrinfo *raw_node_;
	std::string canonical_name_;
	Address address_;
};

} // namespace endpoint
