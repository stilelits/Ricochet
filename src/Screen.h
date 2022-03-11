/*
 * Screen.h
 *
 *  Created on: Nov 21, 2017
 *      Author: tr_dawson
 */

#ifndef GAMESCREEN_H_
#define GAMESCREEN_H_

#include <algorithm>
#include <windows.h>
#include <vector>
#include <iostream>
#include "Colors.h"
#include "DrawObject.h"
#include "Entity.h"
#include "Map.h"
#include "Sprite.h"
#include "Utils.h"

#define START_FULL_SCREEN (0)
#define SCREEN_HALF_PIXEL_WIDTH (SCREEN_PIXEL_WIDTH / 2)
#define SCREEN_HALF_PIXEL_HEIGHT (SCREEN_PIXEL_HEIGHT / 2)
#define SCROLL_FRACTION (6)
#define SCROLL_X_THRESHOLD  (SCREEN_PIXEL_WIDTH / SCROLL_FRACTION)
#define SCROLL_Y_THRESHOLD  (SCREEN_PIXEL_HEIGHT / SCROLL_FRACTION)
#define SCREEN_PIXEL_COUNT  (SCREEN_PIXEL_WIDTH * SCREEN_PIXEL_HEIGHT)

class Screen {
public:
 explicit Screen(HWND hWndNew);
 void draw();
 void addObject(DrawObject* toInsert);
 void delObject(DrawObject* toErase);
 void update();
 POINTS camera;
 int zoom;
 void addAll(std::vector<Entity*> toAdd);
 void rescaleTo(int width, int height);
 void fullScreen(bool fullNew);
 void toggleFull();
 void getWindow();
 void focusOn(Entity* focusNew);
 RECT windowNew;
 int xMapToScreen(int x);
 int xScreenToMap(int x);
 int yMapToScreen(int y);
 int yScreenToMap(int y);
 bool inFullScreen;
 void delAll();
 void setBounds(Map* map);
 void pullMouseTo(int x, int y);
private:
 Entity* focus;
 void drawToScreen(DrawObject* draw);
 RECT windowOld;
 RECT desktop;
 HDC device;
 BITMAPINFO bmi;
 float scale;
 float inv_scale;
 int scaledTop;
 int scaledLeft;
 int scaledWidth;
 int scaledHeight;
 int xCameraMax;
 int xCameraMin;
 int yCameraMax;
 int yCameraMin;
 std::vector<DrawObject*> drawables;
 HDC outputArea;
 HWND hWnd;
 void clearScreen();
 DWORD outputDIB[SCREEN_PIXEL_WIDTH * SCREEN_PIXEL_HEIGHT];
 inline void setPixel(int i, int j, DWORD color){
  //if ((j<0)||(j>=SCREEN_PIXEL_WIDTH)||(i<0)||(i>=SCREEN_PIXEL_HEIGHT)){return;} //range checking...should be done before getting here!
  outputDIB[(i * SCREEN_PIXEL_WIDTH) + j] = color;
 }
 inline void setPixelTransparent(int i, int j, DWORD color){
  //if ((j<0)||(j>=SCREEN_PIXEL_WIDTH)||(i<0)||(i>=SCREEN_PIXEL_HEIGHT)){return;} //range checking...should be done before getting here!
  unsigned char* created = (unsigned char*)&color;
  unsigned char* current = (unsigned char*)&outputDIB[(i * SCREEN_PIXEL_WIDTH) + j];
  float alpha = (float)(created[3])/0xFF;
  current[0]+=(created[0]-current[0])*alpha;
  current[1]+=(created[1]-current[1])*alpha;
  current[2]+=(created[2]-current[2])*alpha;
 }
};

#endif /* GAMESCREEN_H_ */
