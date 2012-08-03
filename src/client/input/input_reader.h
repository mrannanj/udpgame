#ifndef CLIENT_INPUT_READER_H
#define CLIENT_INPUT_READER_H

#include <SDL.h>

#include "common/google.h"

struct Input;

//! InputReader translates input from keyboard and mouse to in-game commands.
class InputReader
{
	public:
	InputReader();
	void Init();
  void Destroy();

	bool ReadInput(Input&);

	private:
	DISALLOW_COPY_AND_ASSIGN(InputReader);

	unsigned CheckKeyboard(unsigned);
	void CheckMouseState(Input&);

	int num_keys_;
	Uint8* key_state_;
  unsigned* actions_;
};

#endif
