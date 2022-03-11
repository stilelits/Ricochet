/*
 * Screen.cpp
 *
 *  Created on: Nov 21, 2017
 *      Author: tr_dawson
 */

#include "Screen.h"
#include "Game.h"

Screen::Screen(HWND hWndNew){
 hWnd = hWndNew;
 rescaleTo(SCREEN_PIXEL_WIDTH, SCREEN_PIXEL_HEIGHT);
 camera.x = 0;
 camera.y = 0;
 zoom = 0;
 focus = NULL;
 inFullScreen = false;
 getWindow();
 GetWindowRect(GetDesktopWindow(),&desktop);
 ShowCursor(false);
 xCameraMax = 0;
 xCameraMin = 0;
 yCameraMax = 0;
 yCameraMin = 0;
 if (START_FULL_SCREEN){toggleFull();}
}
void Screen::rescaleTo(int width, int height){
 float xScale = (float) width / SCREEN_PIXEL_WIDTH;
 float yScale = (float) height / SCREEN_PIXEL_HEIGHT;
 if (xScale < yScale){
  //width should be determining factor
  scale     = xScale;
  scaledTop  = (height - (SCREEN_PIXEL_HEIGHT * scale)) / 2;
  scaledLeft = 0; //left edge is AT the left of the window
 } else {
  //height should be determining factor
  scale     = yScale;
  scaledTop  = 0; //top edge is AT the top of the window
  scaledLeft = (width - (SCREEN_PIXEL_WIDTH * scale)) / 2;
 }
 inv_scale = 1 / scale;
 scaledHeight = SCREEN_PIXEL_HEIGHT * scale;
 scaledWidth  = SCREEN_PIXEL_WIDTH  * scale;
 bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
 bmi.bmiHeader.biWidth = SCREEN_PIXEL_WIDTH;
 bmi.bmiHeader.biHeight = -SCREEN_PIXEL_HEIGHT;
 bmi.bmiHeader.biPlanes = 1;
 bmi.bmiHeader.biBitCount = 32;
 bmi.bmiHeader.biCompression = BI_RGB;
 //outputDIB.resize(width * height);
 device = GetDC(hWnd);
 clearScreen();
 StretchDIBits(device, 0, 0, width, height, 0, 0, SCREEN_PIXEL_WIDTH, SCREEN_PIXEL_HEIGHT, outputDIB, &bmi, DIB_RGB_COLORS, SRCCOPY);
}
void Screen::toggleFull(){
 fullScreen(!inFullScreen);
}
void Screen::fullScreen(bool fullNew){
 if (fullNew){ //go into it
  if (!inFullScreen){
   GetWindowRect(hWnd,&windowOld);
   SetWindowLongPtr(hWnd, GWL_STYLE, WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE);
   MoveWindow(hWnd, 0, 0, desktop.right, desktop.bottom, true);
   inFullScreen = true;
   getWindow();
   rescaleTo(windowNew.right - windowNew.left, windowNew.bottom - windowNew.top);
  }
 } else { //get out of it
  if (inFullScreen){
   SetWindowLongPtr(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
   MoveWindow(hWnd, windowOld.left, windowOld.top, windowOld.right - windowOld.left, windowOld.bottom - windowOld.top, true);
   inFullScreen = false;
   getWindow();
   rescaleTo(windowNew.right - windowNew.left, windowNew.bottom - windowNew.top);
  }
 }
}
void Screen::getWindow(){
 GetWindowRect(hWnd,&windowNew);
}
void Screen::focusOn(Entity* focusNew){
 focus = focusNew;
}
void Screen::draw(){
 clearScreen();
 if (focus){
  camera.x = focus->centerX();
  if (camera.x < xCameraMin) {camera.x = xCameraMin;}
  if (camera.x > xCameraMax) {camera.x = xCameraMax;}
  camera.x -= SCREEN_HALF_PIXEL_WIDTH; //subtraction to move the focus point to the LEFT edge
  camera.y = focus->centerY();
  if (camera.y < yCameraMin) {camera.y = yCameraMin;}
  if (camera.y > yCameraMax) {camera.y = yCameraMax;}
  camera.y += SCREEN_HALF_PIXEL_HEIGHT; //subtraction to move the focus point to the TOP edge
  Game::engine->updateCursor();
 }
 unsigned draws = drawables.size();
 //sort the sprite and have them draw themselves
 std::sort(drawables.begin(),drawables.end(),DrawObjectComparer());
 for (unsigned k=0;k<draws;k++){drawToScreen(drawables[k]);}
 //intentional to delete extras AFTER drawing to the screen...this will allow us to see bullets impact
 for (unsigned k=0;k<draws;k++){if (drawables[k]->toDelete){delObject(drawables[k]);}}
}
void Screen::drawToScreen(DrawObject* draw){
 if (draw->invisible){return;}
 int x = draw->x;
 int y = draw->y;
 if(!draw->absolutePosition){
  x = x - camera.x; //addition to move the object to the RIGHT
  y = camera.y - y; //addition to move the object DOWN
 }
 //after this point, x and y are absolutely positioned on the screen, with 0,0 being the top left pixel
 if (x >= SCREEN_PIXEL_WIDTH)     {return;} //if the LEFT edge is to the RIGHT of the screen (greater than = to the right for X)
 if (y < 0)                       {return;} //if the BOTTOM edge is too HIGH on the screen (less than = above for Y)
 int w = draw->w;                           //x + w is now the physical RIGHT EDGE column (low numbers LEFT on the screen)
 if (x + w < 0)                   {return;} //if the RIGHT edge is too far LEFT (less than = to the left for X)
 int h = draw->h;                           //y - h is now the physical TOP EDGE row (low numbers HIGH on the screen)
 if (y - h >= SCREEN_PIXEL_HEIGHT){return;} //if the TOP edge is too LOW (greater than = below for Y)
 //at this point, we know that at least SOME of the object is in view
 Sprite* sprite=NULL;
 if(draw->sprite){sprite=draw->sprite;}
 DWORD color;
 int iOff = y - h;
 int jOff = x;
 int iScreen = y - h;
 int jScreen = x;
 if (!sprite){ //just draw solid color box
  color = draw->color;
  for (int i = 0; i < h; i++, iScreen++){
   if (iScreen < 0){i -= iScreen; iScreen = 0;}
   if (iScreen >= SCREEN_PIXEL_HEIGHT){break;}
   for (int j = 0, jScreen = x; j < w; j++, jScreen++){
    if (jScreen < 0){j -= jScreen; jScreen = 0;}
    if (jScreen >= SCREEN_PIXEL_WIDTH){break;}
    setPixel(iScreen, jScreen, color);
   }
  }
 } else { //draw the sprite
  int row=0;
  int col=0;
  DWORD* frame = sprite->frame;
  int hFrame=sprite->h;
  int wMap=sprite->map->w;
  DWORD greenScreen=sprite->greenScreen;
  if (!sprite->mask){
   for (int i = 0; i < h; i++, iScreen++){
    if (iScreen < 0){i -= iScreen; iScreen = 0;}
    if (iScreen >= SCREEN_PIXEL_HEIGHT){break;}
    for (int j = 0, jScreen = x; j < w; j++, jScreen++){
     if (jScreen < 0){j -= jScreen; jScreen = 0;}
     if (jScreen >= SCREEN_PIXEL_WIDTH){break;}
     color = frame[((i%hFrame) * wMap) + (j%wMap)];
     if (greenScreen!=PIXEL_GREEN && color == PIXEL_GREEN){color = greenScreen;}
     setPixel(iScreen,jScreen,color);
    }
   }
  } else {
   for (int i = 0; i < h; i++, iScreen++){
    if (iScreen < 0){i -= iScreen; iScreen = 0;}
    if (iScreen >= SCREEN_PIXEL_HEIGHT){break;}
    for (int j = 0, jScreen = x; j < w; j++, jScreen++){
     if (jScreen < 0){j -= jScreen; jScreen = 0;}
     if (jScreen >= SCREEN_PIXEL_WIDTH){break;}
     color = frame[((i%hFrame) * wMap) + (j%wMap)];
     DWORD alpha = color & PIXEL_ALPHA;
     if (color & PIXEL_ALPHA){
      if (sprite->silhouette || ((greenScreen != PIXEL_GREEN) && ((color & PIXEL_WHITE)==PIXEL_GREEN))){color = greenScreen;} //this will get rid of any subtle gradations
      if ((color & PIXEL_ALPHA) == PIXEL_ALPHA){setPixel(iScreen,jScreen,color);} else {setPixelTransparent(iScreen,jScreen,color);}
     }
    }
   }
  }
 }
}
void Screen::setBounds(Map* map){
 xCameraMin = map->left   + SCREEN_HALF_PIXEL_WIDTH;
 xCameraMax = map->right  - SCREEN_HALF_PIXEL_WIDTH;
 if (xCameraMin > xCameraMax){
  xCameraMin = (xCameraMin + xCameraMax) / 2; //take the average of both
  xCameraMax = xCameraMin;
 }
 yCameraMax = map->top    - SCREEN_HALF_PIXEL_HEIGHT;
 yCameraMin = map->bottom + SCREEN_HALF_PIXEL_HEIGHT;
 if (yCameraMin > yCameraMax){
  yCameraMin = (yCameraMin + yCameraMax) / 2; //take the average of both
  yCameraMax = yCameraMin;
 }
}
void Screen::update(){ //sends whatever is currently in the bitmap
 StretchDIBits(device, scaledLeft, scaledTop, scaledWidth, scaledHeight, 0, 0, SCREEN_PIXEL_WIDTH, SCREEN_PIXEL_HEIGHT, outputDIB, &bmi, DIB_RGB_COLORS, SRCCOPY);
}

void Screen::clearScreen(){ //resets entire screen to black
 std::fill(outputDIB, outputDIB + (SCREEN_PIXEL_HEIGHT * SCREEN_PIXEL_WIDTH), PIXEL_BLANK);
}
void Screen::addObject(DrawObject* toInsert){ drawables.push_back(toInsert);}
void Screen::delObject(DrawObject* toErase){ VECTOR_REMOVE(drawables,toErase);}
void Screen::delAll(){ drawables.clear();}
void Screen::addAll(std::vector<Entity*> toAdd){
 for (unsigned k=0;k<toAdd.size();k++){  addObject(static_cast<Entity*>(toAdd[k])); }
}
int Screen::xScreenToMap(int x){ return camera.x - scaledLeft + (x * inv_scale);}
int Screen::xMapToScreen(int x){ return (x + (scaledLeft - camera.x)) * scale;}
int Screen::yScreenToMap(int y){ return camera.y + scaledTop  - (y * inv_scale);}
int Screen::yMapToScreen(int y){ return (-y + (scaledTop  + camera.y)) * scale;}
void Screen::pullMouseTo(int x, int y){SetCursorPos(xMapToScreen(x) + windowNew.left, yMapToScreen(y) + windowNew.top);}
