#include "common/net/dns.h"
#include "common/util/die.h"

#include <netdb.h>
#include <arpa/inet.h>

std::string resolve_hostname(const std::string& h)
{
	if (h.size() == 0)
		return h;

	struct addrinfo *result;
	int error;

	error = getaddrinfo(h.c_str(), NULL, NULL, &result);
	if (error != 0) {
		if (error == EAI_SYSTEM) {
			die("getaddrinfo");
		} else {
			fprintf(stderr, "error in getaddrinfo: %s\n",
				gai_strerror(error));
		}
		return "";
	}

	if (result == nullptr)
		return "";

	struct in_addr *addr = nullptr;
	if (result->ai_family == AF_INET) {
		struct sockaddr_in *ipv =
		    (struct sockaddr_in *)result->ai_addr;
		addr = &(ipv->sin_addr);
	}
	if (addr == nullptr)
		return "";
	char ipstr[INET_ADDRSTRLEN];
	inet_ntop(result->ai_family, addr, ipstr, sizeof ipstr);
	freeaddrinfo(result);
	return ipstr;
}
