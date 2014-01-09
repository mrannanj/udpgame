#pragma once

#include "common/proto/udpgame.pb.h"

#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>

constexpr ssize_t MAXMSG = 1000000;

using std::cout;
using std::endl;

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
  unsigned mLastFrameOk;
  char* mBuf;
};

template <class T>
ssize_t Connection::checkMessages(T& handler) {
  if (mPos >= MAXMSG) return -1;
  size_t count = MAXMSG-mPos;
  ssize_t nread = read(mSocket, &mBuf[mPos], count);
  if (nread <= 0) return -1;
  mPos += nread;
  while ((size_t)mPos >= sizeof(int)) {
    int size;
    memcpy(&size, mBuf, sizeof(int));
    size = ntohl(size);
    int tsize = size + sizeof(int);
    if (tsize > MAXMSG) return -1;
    if ((size_t)mPos >= size + sizeof(int)) {
      AMessage a;
      if (a.ParseFromArray(&mBuf[sizeof(int)], size)) {
        if (!handler.handleAMessage(a, mSocket)) return -1;
        size_t overPos = mPos-tsize;
        memmove(mBuf, &mBuf[mPos-overPos], overPos);
        mPos -= tsize;
      } else {
        cout << "Invalid message" << endl;
        return -1;
      }
    } else {
      break;
    }
  }
  return nread;
}

std::ostream& operator<<(std::ostream& os, const Connection&);

