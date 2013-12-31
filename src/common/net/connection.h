#pragma once

#include "common/proto/udpgame.pb.h"
#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>

#define MAXMSG 2048

struct Connection {
  Connection(int, const sockaddr_in&);
  Connection(const std::string&);
  Connection(Connection&&) = default;
  Connection& operator=(Connection&&) = default;
  Connection& operator=(const Connection&) = delete;
  Connection(const Connection&) = delete;
  ~Connection();

  void sendMessage(const AMessage&);
  template <class T> void checkMessages(T&);

  ssize_t mPos;
  int mSocket;
  std::string mAddress;
  sockaddr_in mSockaddr;
  char mBuf[MAXMSG];
};

template <class T>
void Connection::checkMessages(T& handler) {
  ssize_t nread = read(mSocket, &mBuf[mPos], MAXMSG-mPos);
  if (nread < 0) return;
  mPos += nread;
  if (mPos >= 2) {
    uint16_t size;
    memcpy(&size, mBuf, sizeof(uint16_t));
    size = ntohs(size);
    if (mPos >= size+2) {
      AMessage a;
      if (a.ParseFromArray(&mBuf[sizeof(uint16_t)], size)) {
        const WorldState& w = a.world_state();
        handler.setState(w);
        mPos -= size+2;
      }
    }
  }
}

