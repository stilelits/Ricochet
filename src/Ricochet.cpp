//============================================================================
// Name  : Ricochet.cpp
// Author   : Travis Dawson
// Version  :
// Copyright   : Copyright 2017
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <windows.h>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <map>
#include <math.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <algorithm>

#define WINDOW_TITLE         "Ricochet"
#define LEFT_PADDING         (8)
#define RIGHT_PADDING        (8)
#define BOTTOM_PADDING       (8)
#define TOP_PADDING          (30)
#define TILE                 (20)

#include "Game.h"
#include "Utils.h"

const char className[] = "ricochetWindowClass";

//windows stuff
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
 switch(msg) {
  case WM_CLOSE:   DestroyWindow(hWnd); break;
  case WM_DESTROY: PostQuitMessage(0);  break;
  default:         if (Game::engine){Game::engine->processMessages(msg,wParam,lParam);}
 }
 return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow) {
 char buffer[MAX_PATH];
 GetModuleFileName(NULL, buffer, MAX_PATH);
 g_folder = std::string(buffer).substr(0,std::string(buffer).find_last_of( "\\/" ));

 //Set up window class
 WNDCLASS wnd = {};
 wnd.cbClsExtra = 0;
 wnd.cbWndExtra = 0;
 wnd.hCursor = LoadCursor(0, IDC_ARROW);
 wnd.hIcon = LoadIcon(0, IDI_WINLOGO);
 wnd.lpszMenuName = 0;
 wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
 wnd.hbrBackground = 0;
 wnd.lpfnWndProc = WndProc;
 wnd.hInstance = hInstance;
 wnd.lpszClassName = className;
 if(!RegisterClass(&wnd))  {
  MessageBox(NULL, "Window Registration Failed!", "Error!",MB_ICONEXCLAMATION | MB_OK);  return 0;
 }

 //Create window
 //! This returns NULL
 HWND hWnd = CreateWindowEx(
  0,
  className,
  WINDOW_TITLE,
  WS_OVERLAPPEDWINDOW,
  CW_USEDEFAULT,
  CW_USEDEFAULT,
  SCREEN_PIXEL_WIDTH + LEFT_PADDING + RIGHT_PADDING,
  SCREEN_PIXEL_HEIGHT + TOP_PADDING + BOTTOM_PADDING,
  NULL,
  NULL,
  hInstance,
  NULL
 );

 //Simple check to see if window creation failed
 if(hWnd == NULL) {
  return GetLastError();
 } else {
  ShowWindow(hWnd, nCmdShow);
  return Game::playGame(hWnd);
 }
}

