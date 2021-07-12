#include <iostream>
#include <chrono>

#include "common/config.h"
#include "common/net/dns.h"
#include "client/controller/game_session.h"
#include "client/controller/input/input.h"
#include "client/view/world_renderer.h"

using namespace std;
using namespace std::chrono;

GameSession::GameSession():
	mClientId(-1),
	mInit(false),
	mRedraw(false),
	mConnection(),
	mPerspective(),
	mWorld(false),
	mInput()
{
}

GameSession::GameSession(const std::string& addr):
	mClientId(-1),
	mInit(false),
	mRedraw(false),
	mConnection(resolve_hostname(addr)),
	mPerspective(),
	mWorld(false),
	mInput()
{
	if (addr.size() == 0)
		return;
	cout << "connected to " << mConnection << endl;
	system_clock::time_point t1 = system_clock::now();
	while (!mWorld.mInit) {
		mConnection.checkMessages(*this);
		system_clock::time_point t2 = system_clock::now();

		if (t2 - t1 >= chrono::seconds(1)) {
			cout << "Failed to get initial state from server, exiting"
			     << endl;
			exit(EXIT_FAILURE);
		}
	}
	mInit = true;
	mRedraw = true;
}

void GameSession::tick(Input& input, bool haveFocus)
{
	if (!mInit)
		return;
	mInput = haveFocus ? input : zeroInput();
	mConnection.checkMessages(*this);
	mPerspective.tick(mWorld);
}

Input GameSession::zeroInput()
{
	Input i;
	memset(&i, 0, sizeof(i));
	return i;
}

void GameSession::sendFrameInput(Input& i)
{
}

void GameSession::draw(const Renderer& r)
{
	mRedraw = true;
}
