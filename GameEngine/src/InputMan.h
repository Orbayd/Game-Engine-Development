#ifndef INPUT_MAN_H
#define INPUT_MAN_H

#include "Keyboard.h"

class InputMan
{
public:
	static void Create();
	static Keyboard *GetKeyboard();
	static void Event( Keyboard * key);
	~InputMan();

private:
	static InputMan *privInstance();
	static void privCreate();
	InputMan();
	
	// Data
	static InputMan *pInputMan;
	Keyboard		*pKeyboard;

};
#endif