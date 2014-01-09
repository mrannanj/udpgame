#include <iostream>

#include "server/world_ticker.h"
#include "common/config.h"

using namespace std;

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
    if (tick - c->mLastFrameOk >= 10) {
      c = connections.erase(c);
      continue;
    }
    cout << "client " << c->mSocket << " was late for frame " << tick << endl;
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
}

bool WorldTicker::handleAMessage(const AMessage& a, int clientid) {
  unsigned tick = a.client_input().tick_number();
#if 0
  if (getHash(tick) != a.client_input().previous_hash()) {
    cout << "hash expected: " << getHash(tick) << endl;
    cout << "hash was: " << a.client_input().previous_hash() << endl;
    return false;
  }
#endif
  // FIXME: dont add late inputs
  FrameInputs& fis = mInputMap[tick];
  FrameInput* fi = fis.add_frame_inputs();
  fi->CopyFrom(a.client_input().frame_input());
  fi->set_client(clientid);
  return true;
}

unsigned WorldTicker::getHash(unsigned tick) {
  return mHashes[(tick-STATIC_FRAME_DELTA)%HASH_MAX];
}

void WorldTicker::setHash(unsigned tick, unsigned h) {
  mHashes[tick%HASH_MAX] = h;
}

void WorldTicker::setCurrentTick(unsigned tick) {
  mCurrentTick = tick;
}
