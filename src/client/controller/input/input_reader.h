#ifndef CLIENT_CONTROLLER_INPUT_READER_H
#define CLIENT_CONTROLLER_INPUT_READER_H

#include <SDL.h>

#include "common/google.h"

struct Input;

//! InputReader translates input from keyboard and mouse to in-game commands.
class InputReader
{
	public:
	InputReader();
	~InputReader();
	DISALLOW_COPY_AND_ASSIGN(InputReader);
  void Destroy();

	void ReadInput(Input&);

	private:

	void init_actions();
	void check_keyboard(Input&);
	void CheckMouseState(Input&);

	int num_keys_;
	Uint8* key_state_;
  unsigned* actions_;
};

#endif
