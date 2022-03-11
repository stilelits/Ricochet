/*
 * Item.h
 *
 *  Created on: Nov 27, 2017
 *      Author: tr_dawson
 */

#ifndef ITEM_H_
#define ITEM_H_

#include "Entity.h"
#include "Bullet.h"

class Unit;
class Bullet;

class Item: public Entity {
public:
 Item();
 Item(const std::string& nameNew);
 std::string description;
 bool canR;
 bool canL;
 bool canA;
 bool canB;
 int coolDown;
 int fireRate;
 int dam;
 float stunTime;
 void cool();
 float def;
 int hp;
 Unit* owner;
 Bullet* fire();
 AmmoType type;
 int usesLeft;
 std::string currentUse;
 void setName(const std::string& nameNew);
 void setAmmoType(AmmoType typeNew);
};

#endif /* ITEM_H_ */
