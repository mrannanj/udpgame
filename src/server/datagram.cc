#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cassert>
#include <alloca.h>
#include <cctype>
#include <cstring>

#include "server/datagram.h"
#include "common/util/timespec.h"

unsigned subst_nonprintables(char *s)
{
  unsigned n = 0;
  for (; *s; ++s)
  {
    if (!isprint(*s))
    {
      *s = 'X';
      ++n;
    }
  }
  return n;
}

std::ostream& operator<<(std::ostream& out, const Datagram& d)
{
  char addr[INET6_ADDRSTRLEN];
  char port[NI_MAXSERV];
  int err = getnameinfo((sockaddr*)d.sa, d.sa_len, addr,
      INET6_ADDRSTRLEN, port, NI_MAXSERV,
      NI_NUMERICSERV | NI_NUMERICHOST | NI_DGRAM);
  assert(err == 0);
  char* printable_msg = (char*)alloca(d.len+1);
  memcpy(printable_msg, d.buf, d.len+1);
  printable_msg[d.len] = '\0';
  unsigned np = subst_nonprintables(printable_msg);

  out << "Datagram from: " << addr << ":" << port << std::endl;
  out << "Datagram timestamp: " << *(d.ts) << std::endl;
  out << "Datagram len(np): " << d.len << "(" << np << ")" << std::endl;
  out << "Datagram message: '" << printable_msg << '\'';
  return out;
}

