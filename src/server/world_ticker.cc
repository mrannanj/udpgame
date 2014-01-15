#include <iostream>
#include <cstring>
#include <google/protobuf/descriptor.h>

#include "server/world_ticker.h"
#include "common/config.h"
#include "common/proto/udpgame.pb.h"

static constexpr unsigned TIMEOUT = 60;

using namespace std;

WorldTicker::WorldTicker():
  mCurrentTick(0),
  mHashes(),
  mInputMap()
{
}

const FrameInputs& WorldTicker::inputsForFrame(unsigned tick) {
  return mInputMap[tick];
}

void WorldTicker::fillMissingInputs(unsigned tick,
    std::vector<Connection>& connections)
{
  FrameInputs& fis = mInputMap[tick];
  for (auto c = connections.begin(); c != connections.end(); ) {
    bool found = false;
    for (int i = 0; i < fis.frame_inputs_size(); ++i) {
      const FrameInput& fi = fis.frame_inputs(i);
      if (c->mSocket == fi.client()) {
        found = true;
        c->mLastFrameOk = tick;
        break;
      }
    }
    if (found) {
      ++c;
      continue;
    }
    if (tick - c->mLastFrameOk >= TIMEOUT) {
      cout << *c << " timeouted" << endl;
      c = connections.erase(c);
      continue;
    }
    FrameInput* fi = fis.add_frame_inputs();
    fi->set_client(c->mSocket);
    fi->set_actions(0);
    fi->set_horizontal_delta(0.0f);
    fi->set_vertical_delta(0.0f);
    ++c;
  }
}

void WorldTicker::removeOldFrame(unsigned tick) {
  mInputMap.erase(tick);
  if (tick >= TIMEOUT)
    mHashes.erase(tick - TIMEOUT);
}

bool WorldTicker::handleAMessage(const AMessage& a, int clientid) {
  unsigned tick = a.client_input().tick_number();
  if (!compareHashes(tick, a.client_input().hashes()))
      return false;
  if (tick <= mCurrentTick) return true;
  FrameInputs& fis = mInputMap[tick];
  FrameInput* fi = fis.add_frame_inputs();
  fi->CopyFrom(a.client_input().frame_input());
  fi->set_client(clientid);
  return true;
}

bool WorldTicker::compareHashes(unsigned tick,
    const google::protobuf::RepeatedField<uint32_t>& clientHashes)
{
  if (tick < STATIC_FRAME_DELTA) {
    cout << "tick should be more than " << STATIC_FRAME_DELTA << endl;
    return false;
  }
  bool retval = true;
  auto& serverHashes = mHashes[tick-STATIC_FRAME_DELTA];
  for (int i = 0; i < HANDLER_COUNT; ++i) {
    uint32_t ch = clientHashes.Get(i);
    uint32_t sh = serverHashes[i];
    if (sh != ch) {
      const google::protobuf::EnumDescriptor* hd = Handler_descriptor();
      cout << "hash mismatch for frame " << tick << ", handler "
        << hd->value(i)->name() << endl;
      cout << "client: " << ch << endl;
      cout << "server: " << sh << endl;
      retval = false;
    }
  }
  return retval;
}

void WorldTicker::setHashes(unsigned tick, const uint32_t* h) {
  std::array<uint32_t, HANDLER_COUNT> a;
  memcpy(&a[0], h, HANDLER_COUNT*sizeof(uint32_t));
  mHashes[tick] = a;
}

void WorldTicker::setCurrentTick(unsigned tick) {
  mCurrentTick = tick;
}
