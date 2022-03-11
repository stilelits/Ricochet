/*
 * Entity.h
 *
 *  Created on: Nov 21, 2017
 *      Author: tr_dawson
 */

//GOOD FOR POSITIVE

#ifndef ENTITY_H_
#define ENTITY_H_

#define FRONT(e)        (e->z + e->d)
#define BACK(e)         (e->z)
#define LEFT(e)         (e->x)
#define RIGHT(e)        (e->x + e->w)
#define BOTTOM(e)       (e->y)
#define TOP(e)          (e->y + e->h)
#define MOVINGRIGHT(e)  FLOATGREATER(e->dx, 0)
#define MOVINGLEFT(e)   FLOATLESS(e->dx, 0)
#define MOVINGUP(e)     FLOATGREATER(e->dx, 0)
#define MOVINGDOWN(e)   FLOATLESS(e->dx, 0)
#define INTERACT_NONE   (-2)
#define INTERACT_INSIDE (-1)
#define INTERACT_TOUCH  (0)

#include <cmath>
#include <vector>
#include <map>
#include <limits>
#include "Utils.h"
#include "DrawObject.h"
#include "Vector.h"
#include "TextBox.h"

class Entity : public DrawObject {
public:
 Entity(float xNew=0, float yNew=0, int zNew=Z_ACTIONGROUND, float wNew=TILE, float hNew=TILE);
 virtual ~Entity(){};
 int d;
 bool canInteractWith(Entity* other);
 bool isTouching(Entity* other);
 bool isInside(Entity* other);
 bool isWithinDistance(Entity* other, int distance);
 bool immobile;
 bool solid;
 std::string sfx;
 void setSFX(const std::string& sfxNew);
 bool weightless;
 int interact;
 float weight;
 Direction facing;
 float bounciness;
 float radius();
 float minorAxis();
 float majorAxis();
 void patrolTo(Direction patrolNew);
 Direction patrol;
 float speed;
 void setMaxDx(float maxDxNew);
 void setMaxDy(float maxDyNew);
 void stop();
 void stopX();
 void stopY();
 virtual void updateSprite();
 virtual void advance(float gravity, const std::vector<Entity*>& others, std::vector<Entity*>& toAdd);
 void accelX(float toAdd);
 void accelY(float toAdd);
 float dx;
 float dy;
 virtual void setName(const std::string& nameNew);
 virtual void interactWith(Entity* other);
protected:
 Direction impetusX;
 Direction impetusY;
 virtual bool hitFrom(Entity* other, Direction dir);
 float maxDx;
 float minDx;
 float maxDy;
 float minDy;
};

#endif /* ENTITY_H_ */
