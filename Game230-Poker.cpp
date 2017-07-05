// Game230-Poker.cpp : Defines the entry point for the console application.
//
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif

#pragma once
#include "GameManager.h"
#include "stdafx.h"
#include <stddef.h>
#include <iostream>
#include <array>
#include <time.h> 

using namespace std; 

	int main()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |
			_CRTDBG_LEAK_CHECK_DF);
		GameManager* gm = new GameManager();
		
		srand(time(NULL));
		gm->play();
		delete gm;
		return 0;
	}
