/*
 * SpriteMap.cpp
 *
 *  Created on: Nov 27, 2017
 *      Author: tr_dawson
 */

#include "SpriteMap.h"

SpriteMap::SpriteMap(int hNew, int wNew) {
 borderColor = PIXEL_WHITE;
 h = hNew;
 w = wNew;
 pixels = new DWORD[h * w];
 clearPixels();
 fileFound = false;
}
void SpriteMap::clearPixels(){
 std::fill(pixels, pixels + (h * w), PIXEL_BLANK);
}
void SpriteMap::addBorder(){
 for (int i = 0; i < w; i++){
  pixels[i] = borderColor; //top edge
  pixels[i + ((h-1) * w)] = borderColor; //bottom edge
 }
 for (int j = 0; j < h; j++){
  pixels[j * w] = borderColor; //left edge
  pixels[(w-1) + (j * w)] = borderColor; //left edge
 }
}
SpriteMap::SpriteMap(const std::string &file, bool mask) {
 borderColor = PIXEL_GREEN;
 std::ifstream f;
 f.open((g_folder + "/images/" + file + ".bmp").c_str(), std::ios::in | std::ios::binary);
 fileFound = f.is_open();
 if(fileFound){
  unsigned char* datBuff[2];
  datBuff[0] = new unsigned char[sizeof(BITMAPFILEHEADER)];
  f.read((char*)datBuff[0], sizeof(BITMAPFILEHEADER));
  BITMAPFILEHEADER* bmpHeader = (BITMAPFILEHEADER*) datBuff[0];
  datBuff[1] = new unsigned char[sizeof(BITMAPINFOHEADER)];
  f.read((char*)datBuff[1], sizeof(BITMAPINFOHEADER));
  BITMAPINFOHEADER* bmpInfo   = (BITMAPINFOHEADER*) datBuff[1];
  char* pixelsRGB = new char[bmpInfo->biSizeImage];
  f.seekg(bmpHeader->bfOffBits);
  f.read(pixelsRGB, bmpInfo->biSizeImage);
  h=bmpInfo->biHeight; if (mask) {h /= 2;}                              //popUp(h);
  w=bmpInfo->biWidth;                                                   //popUp(w);
  int rowPadding; if (w%4==0){rowPadding=0;} else {rowPadding=(w%4);}   //popUp(rowPadding);
  int rowMult=(w*3)+rowPadding;                                         //popUp(rowMult);
  int loc;
  pixels = new DWORD[h * w];
  DWORD alpha = 0xFF000000;
  for(int i=0;i<h;i++){
   for(int j=0;j<w;j++){
    loc = ((h-(i+1))*rowMult) + (j*3);
    if (mask){alpha = (0x000000FF&pixelsRGB[loc + (h * rowMult)]) << 24;}
    pixels[(i*w)+j]= alpha | (0x000000FF&pixelsRGB[loc])|((0x000000FF&pixelsRGB[loc+1])<<8)|((0x000000FF&pixelsRGB[loc+2])<<16);
   }
  }
  delete[] datBuff[0];
  delete[] datBuff[1];
  delete[] pixelsRGB;
  //popUp("finished with " + file);
 }
}

std::map<std::string, SpriteMap*> SpriteMap::maps;

SpriteMap* SpriteMap::load(std::string file, bool mask){
 if (!maps.count(file)){
  SpriteMap* result = new SpriteMap(file, mask);
  if (result->fileFound){
   maps[file] = result;
  } else {
   return NULL;
  }
 }
 return maps[file];
}
