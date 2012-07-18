#ifndef CLIENT_INPUT_READER_H
#define CLIENT_INPUT_READER_H

#include <SDL.h>

#include "client/input/commands.h"
#include "common/google.h"

//! InputReader translates input from keyboard and mouse to in-game commands.
class InputReader
{
	public:
	InputReader();
	void Init();

	bool ReadInput(Actions&);

	private:
	DISALLOW_COPY_AND_ASSIGN(InputReader);

	void CheckKeyboard(Actions&);

	int num_keys_;
	Uint8* key_state_;
};

#endif
