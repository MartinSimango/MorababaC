// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

//#define __UNIX__ (defined(__APPLE__) || defined(__unix__))   

//#define __WINDOWS__ (defined(_WIN32) || defined(WIN32)) 



#include "targetver.h"



#include "game.h"
#include "coordsList.h"
#include "board.h"
#include "mills.h"
#include "gameStructure.h" 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#if defined(__APPLE__) || defined(__unix__)

#include <unistd.h>
#include <string.h>
#include <termios.h>


#elif defined(_WIN32) || defined(WIN32)

#define _CRT_SECURE_NO_WARNINGS             //so no warnings

#include <tchar.h>
#include <windows.h>
#include <conio.h>

#endif


// TODO: reference additional headers your program requires here
