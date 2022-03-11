/*
 * Door.cpp
 *
 *  Created on: Nov 22, 2017
 *      Author: tr_dawson
 */

#include "Door.h"

Door::Door() {
 //popUp("new door being created");
 name = "GENERIC_DOOR";
 h = TILE * 3;
 w = TILE * 2;
 sprite = Sprite::load("Door", true);
 setColor(PIXEL_DARK(PIXEL_RED));
 d = 2; //extend into the foreground so that player can interact
 z = Z_DOORGROUND;
 destX = 0;
 destY = 0;
 destZ = Z_ACTIONGROUND;
 interact = INTERACT_INSIDE;
 setOpen(true);
 entered = false;
}
void Door::setOpen(bool openNew){
 open = openNew;
 if (sprite){
  if (open){
   sprite->setPose(POSE_OPEN);
  } else {
   sprite->setPose(POSE_CLOSED);
  }
 }
}
void Door::interactWith(Entity* other){
 if (open){entered = true;}
}
void Door::setName(const std::string& nameNew){
 name = nameNew;
 dest = nameNew;
}
