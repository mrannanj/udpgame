#pragma once

#include "common/proto/udpgame.pb.h"
#include "common/world/entity_id.h"

#include <string>
#include <cstring>
#include <iostream>
#include <memory>
#include <cstddef>

#ifdef _WIN32
#include <WinSock2.h>
#else
#include <arpa/inet.h>
#endif

#include <SFML/Network/TcpSocket.hpp>

const size_t MAXMSG = 1000000;

struct Connection {
  Connection();
  Connection(Connection&&);
  Connection& operator=(Connection&&);

  void sendMessage(const AMessage&);
  template<typename T> int checkMessages(T&);

  int mId;
  size_t mPos;
  std::unique_ptr<sf::TcpSocket> mSocket;
  std::vector<char> mBuf;
  EntityId mLastFrameOk;
};

std::ostream& operator<<(std::ostream& os, const Connection&);

template<typename T>
int Connection::checkMessages(T& handler) {
  if (mPos >= MAXMSG) return -1;
  size_t count = MAXMSG-mPos;
  size_t nread;
  if (sf::Socket::Done != mSocket->receive(&mBuf[mPos], count, nread))
    return -1;
  if (nread <= 0) return -1;
  mPos += nread;
  while ((size_t)mPos >= sizeof(int)) {
    int size;
    memcpy(&size, &mBuf[0], sizeof(int));
    size = ntohl(size);
    int tsize = size + sizeof(int);
    if (tsize > (int)MAXMSG) return -1;
    if ((size_t)mPos >= size + sizeof(int)) {
      AMessage a;
      if (a.ParseFromArray(&mBuf[sizeof(int)], size)) {
        if (!handler.handleAMessage(a, *this)) return -1;
        size_t overPos = mPos-tsize;
        memmove(&mBuf[0], &mBuf[mPos-overPos], overPos);
        mPos -= tsize;
      } else {
        std::cout << "Invalid message" << std::endl;
        return -1;
      }
    } else {
      break;
    }
  }
  return nread;
}
