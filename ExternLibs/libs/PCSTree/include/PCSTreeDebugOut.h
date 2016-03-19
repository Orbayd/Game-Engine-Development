#ifndef DEBUG_OUT_H
#define DEBUG_OUT_H

	// Needs to be included
	#include <Windows.h>
	#include <stdio.h>
	// Needs a buffer - big enough
	extern char PCSTreeBuff[256];
	// Magic macro
	#define out(A,...) sprintf_s(PCSTreeBuff,A,##__VA_ARGS__); OutputDebugString(PCSTreeBuff);


	
#endif