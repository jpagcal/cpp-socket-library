#pragma once

#include <sys/socket.h>
#include <string>

namespace tcp {
	/**
	 * Represents a connected socket
	 */
	class Connection {
		public:
		/**
		 * Creates a Connection object from a connected raw socket
		 */
		Connection(int socketFD) : socket_{ socketFD } {}

		/**
		 * Connects a socket, and then returns the resulting Connection object
		 */
		Connection resolve(const std::string host, const std::string service, const int domain);

		void send();

		void recv();

		int getFileDescriptor();

		private:
		int socket_;
	};

	class Acceptor {
		public:
		private:
	};

}
