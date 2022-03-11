/*
 * Bullet.h
 *
 *  Created on: Dec 5, 2017
 *      Author: tr_dawson
 */

#ifndef BULLET_H_
#define BULLET_H_

enum AmmoType {ammoNull, ammoNormal, ammoRifle, ammoCannon};

#include "Entity.h"
#include "Unit.h"
#include "Utils.h"
#include "Switch.h"

class Unit;
class Item;

class Bullet: public Entity {
public:
 Bullet(Unit* ownerNew, Item* weaponNew);
 Item* weapon;
 Unit* owner;
 Entity* target;
 float range;
 virtual bool hitFrom(Entity* other, Direction dir);
 virtual void advance(float gravity, const std::vector<Entity*>& others, std::vector<Entity*>& toAdd);
};

#endif /* BULLET_H_ */
