#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cassert>
#include <alloca.h>

#include "server/datagram.h"
#include "common/util/timespec.h"

void escape_newlines(const char *from, char* const to)
{
  const char* fp = from;
  char* tp = to;

  while (*fp)
  {
    if (*fp != '\n')
    {
      *tp++ = *fp++;
    }
    else
    {
      *tp++ = '\\';
      *tp++ = 'n';
      ++fp;
    }
  }
  *tp = '\0';
}

std::ostream& operator<<(std::ostream& out, const Datagram& d)
{
  char addr_str[INET6_ADDRSTRLEN];
  int err = getnameinfo((sockaddr*)d.sa, d.sa_len, addr_str,
      INET6_ADDRSTRLEN, NULL, 0, NI_NUMERICHOST);
  assert(err == 0);
  char* msg = (char*)alloca(d.len*2);
  escape_newlines(d.buf, msg);

  out << "Datagram from: " << addr_str << std::endl;
  out << "Datagram timestamp: " << *(d.ts) << std::endl;
  out << "Datagram length: " << d.len << std::endl;
  out << "Datagram message: '" << msg << '\'';
  return out;
}

