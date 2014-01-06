#pragma once

#include "common/proto/udpgame.pb.h"

#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>

#define MAXMSG 2048

struct Connection {
  Connection();
  Connection(int, const sockaddr_in&);
  Connection(const std::string&);

  Connection(Connection&&);
  Connection& operator=(Connection&&);

  Connection& operator=(const Connection&) = delete;
  Connection(const Connection&) = delete;
  ~Connection();

  void sendMessage(const AMessage&);
  template <class T> ssize_t checkMessages(T&);

  ssize_t mPos;
  int mSocket;
  sockaddr_in mSockaddr;
  char mBuf[MAXMSG];
};

template <class T>
ssize_t Connection::checkMessages(T& handler) {
  ssize_t nread = read(mSocket, &mBuf[mPos], MAXMSG-mPos);
  if (nread <= 0) return nread;
  mPos += nread;
  if (mPos >= 2) {
    uint16_t size;
    memcpy(&size, mBuf, sizeof(uint16_t));
    size = ntohs(size);
    if (mPos >= size+2) {
      AMessage a;
      if (a.ParseFromArray(&mBuf[sizeof(uint16_t)], size)) {
        if (!handler.handleAMessage(a, mSocket)) return -1;
        mPos -= size+2;
      }
    }
  }
  return nread;
}

std::ostream& operator<<(std::ostream& os, const Connection&);

