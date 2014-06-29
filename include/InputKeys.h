#ifndef INCLUDE_INPUTKEYS_H
#define INCLUDE_INPUTKEYS_H

#include <cstdint>

enum GameKeys : uint8_t { 
	UP = 0,
	LEFT,
	RIGHT,
	DOWN,
	ROLL,
	
	SPACE,

	ACTION,
	LATTACK,
	NLATTACK,
	
	ESCAPE,
	MAX
};

#endif //INCLUDE_INPUTKEYS_H
