/*
 * Door.h
 *
 *  Created on: Nov 22, 2017
 *      Author: tr_dawson
 */

#ifndef DOOR_H_
#define DOOR_H_

#include "Background.h"

class Door: public Background {
public:
 Door();
 void enter();
 std::string dest;
 float destX;
 float destY;
 int destZ;
 std::string destDoor;
 virtual void setName(const std::string& nameNew);
 bool entered;
 bool open;
 void setOpen(bool openNew);
 virtual void updateSprite(){};
 virtual void interactWith(Entity* other);
};

#endif /* DOOR_H_ */
