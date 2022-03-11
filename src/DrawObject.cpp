/*
 * DrawObject.cpp
 *
 *  Created on: Nov 21, 2017
 *      Author: tr_dawson
 */

//GOOD FOR POSITIVE

#include "DrawObject.h"

DrawObject::DrawObject(float xNew, float yNew, int zNew, float wNew, float hNew, DWORD colorNew): name("GENERIC_DRAWOBJECT"), uid(""){
 //popUp("new drawobject being created");
 x = xNew;
 y = yNew;
 z = zNew;
 w = wNew;
 h = hNew;
 slope = slopeNull;
 flicker = 0;
 sprite = NULL;
 script = NULL;
 color = colorNew;
 invisible = false;
 toDelete = false;
 absolutePosition = true; //all plain drawobjects are absolutely positioned by default
}
int DrawObject::centerX(){
 return x + (w / 2);
}
int DrawObject::centerY(){
 return y + (h / 2);
}
void DrawObject::setColor(DWORD colorNew){
 color = colorNew;
 if (sprite){sprite->greenScreen = colorNew;}
}
void DrawObject::advance(){
 if (flicker && flicker--){invisible = !invisible;}
 if (sprite){sprite->advance();}
}
void DrawObject::setWidth(float wNew){
 w = wNew;
 if (sprite){sprite->setWidth(w);}
}
void DrawObject::setName(const std::string& nameNew){
 name = nameNew;
 Sprite* spriteNew = Sprite::load(name, true);
 if (spriteNew){
  sprite = spriteNew;
  sprite->w = this->w; //necessary to inform the sprite how wide a single frame needs to be
 }
}
