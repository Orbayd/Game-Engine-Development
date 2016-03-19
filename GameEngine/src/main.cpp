#include <assert.h>

#include "sb6.h"
#include "Game.h"


int CALLBACK WinMain(HINSTANCE , HINSTANCE ,  LPSTR , int)                  
{          
	// create game
	Game *pGame = new Game("Monkey", 800,600);    
	pGame->screenWidth = 800.0f;
	pGame->screenHeight = 600.0f;
	pGame->run();                                  

	return 0;                                       
}

