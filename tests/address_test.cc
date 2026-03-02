#include <arpa/inet.h>
#include <gtest/gtest.h>
#include <netinet/in.h>
#include "../include/endpoint_info.hpp"

class AddressTest : public testing::Test {
	protected:
		AddressTest() {
			std::string address{ "127.0.0.1" };
			std::string port{ "8080" };

			addr_ = Address(address, port);
		}

	Address addr_ = Address();
};

TEST_F(AddressTest, PrintsAddressWithPort) {
	testing::internal::CaptureStdout();
	addr_.print_address();
	std::string output{ testing::internal::GetCapturedStdout() };
	std::string addressWithPort{ "127.0.0.1:8080\n" };
	EXPECT_STREQ(addressWithPort.data(), output.data());
}

TEST_F(AddressTest, emits_a_proper_sockaddr_struct_with_the_correct_fields) {
	auto c_sockaddr = addr_.c_addr();

	sockaddr_in *const ipv4_sockaddr{ reinterpret_cast<sockaddr_in *const>(c_sockaddr) };
	EXPECT_EQ(networking::domain::ipv4, ipv4_sockaddr->sin_family);
	EXPECT_EQ(htons(atoi("8080")), ipv4_sockaddr->sin_port);
}

TEST_F(AddressTest, creates_a_copy_of_the_raw_c_struct_when_constructing_with_a_ptr) {
	Address *address;

	{
		sockaddr_in raw_sockaddr{};
		raw_sockaddr.sin_family = AF_INET;
		raw_sockaddr.sin_port = htons(8000);
		raw_sockaddr.sin_len = sizeof(raw_sockaddr);
		inet_pton(AF_INET, "192.168.1.100", &(raw_sockaddr.sin_addr));

		sockaddr *ptr = reinterpret_cast<sockaddr *>(&raw_sockaddr);

		Address *address_ptr = new Address(ptr);

		address = address_ptr;
	}

	address->print_address();
	EXPECT_EQ(AF_INET, address->ip_domain());

	sockaddr_in *const c_addr{ reinterpret_cast<sockaddr_in *>(address->c_addr()) };
	EXPECT_EQ(htons(8000), c_addr->sin_port);

	char ip_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(c_addr->sin_addr), ip_str, sizeof(ip_str));
	EXPECT_STREQ(ip_str, "192.168.1.100");

	delete address;
}
