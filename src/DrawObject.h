/*
 * DrawObject.h
 *
 *  Created on: Nov 21, 2017
 *      Author: tr_dawson
 */

//GOOD FOR POSITIVE

#ifndef DRAWOBJECT_H_
#define DRAWOBJECT_H_

#ifndef TILE
#define TILE (20)
#endif

#define Z_BACKGROUND   -3
#define Z_TEXTURE      -2
#define Z_DOORGROUND   -1
#define Z_ACTIONGROUND  0
#define Z_FOREGROUND    10
#include <windef.h>
#include <string>
#include "Colors.h"
#include "Sprite.h"
#include "Script.h"

enum SlopeType{slopeNull, slopeD, slopeU, slopeID, slopeIU};

class DrawObject {
public:
 DrawObject(float xNew=0, float yNew=0, int zNew=Z_FOREGROUND, float wNew=TILE, float h=TILE, DWORD colorNew=0x80808080);
 virtual ~DrawObject(){};
 float x; // right edge
 float y; // bottom edge
 int z; // depth in frame...small/negative numbers are FURTHER from the camera
 float w; // width
 float h; // height
 bool absolutePosition;
 DWORD color;
 virtual void setName(const std::string& nameNew);
 Sprite* sprite;
 bool toDelete;
 SlopeType slope;
 bool invisible;
 int flicker;
 Script* script;
 int centerX();
 void setWidth(float wNew);
 int centerY();
 std::string uid;
 std::string name;
 virtual void setColor(DWORD colorNew);
 void advance();
};
struct DrawObjectComparer{
 bool operator()(const DrawObject* d1, const DrawObject* d2){
  if (d1->z != d2->z){
   return d1->z < d2->z; //need to prioritize objects with HIGHER z by drawing them LAST
  } else {
   return (d1->y > d2->y); //if at the same distance, draw the HIGHEST objects LAST
  }
 }
};
#endif /* DRAWOBJECT_H_ */

