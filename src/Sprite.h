/*
 * Sprite.h
 *
 *  Created on: Nov 27, 2017
 *      Author: tr_dawson
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include <algorithm>
#include <windows.h>
#include <string>
#include "Colors.h"
#include "SpriteMap.h"
#include "Poses.h"

class Sprite {
protected:
 Sprite(int hNew=20, int wNew=20, DWORD greenScreenNew = PIXEL_GREEN);
 int coolDown;
 void setFrame(int frameNumNew, bool force = true);
 Direction facing;
 float speed;
public:
 void setSpeed(float speedNew);
 virtual ~Sprite(){};
 bool done;
 std::string pose;
 void setPose(std::string poseNew);
 Poses* poses;
 DWORD greenScreen;
 SpriteMap* map;
 DWORD* frame;
 void setWidth(int wNew);
 void resetCooldown();
 bool silhouette;
 void setFacing(Direction facingNew);
 int frameNum;
 int w;
 int h;
 bool mask;
 static Sprite* load(std::string file, bool mask = DEFAULT_MASK);
 virtual void advance();
};

#endif /* SPRITE_H_ */
