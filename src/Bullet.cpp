/*
 * Bullet.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: tr_dawson
 */

#include "Bullet.h"

Bullet::Bullet(Unit* ownerNew, Item* weaponNew) {
 owner = ownerNew;
 weapon = weaponNew;
 h = 6;
 w = 6;
 range = 800;
 speed = 10;
 weightless = true; //most ammo should not by affected by gravity
 solid = true;
 immobile = false;
 bounciness = 1;
 switch (weapon->type){
 case ammoNormal: //same as the defaults above
  sprite = Sprite::load("Bullet");
  break;
 case ammoRifle:
  range = 1500;
  speed = 20;
  sprite = Sprite::load("Bullet");
  break;
 case ammoCannon:
  range = 1500;
  speed = 8;
  weightless = false;
  weight = .3;
  bounciness = .8;
  h = 12;
  w = 12;
  sprite = Sprite::load("Cannon");
  break;
 }
 if (sprite && owner && owner->sprite){sprite->greenScreen = owner->sprite->greenScreen;}
 target = owner->target;
 //popUp("bullet has been created with a target of " + target->name);
 //i can't think of any situations where we need a bullet faster than 10000px per frame
 maxDx = 10000;
 maxDy = 10000;
 minDx = -10000;
 minDy = -10000;
 x = owner->centerX();
 y = owner->centerY();
 z = owner->z;
 dx = (target->centerX() - x);
 dy = (target->centerY() - y);
 normalize2dVector(&dx, &dy, speed);
}
void Bullet::advance(float gravity, const std::vector<Entity*>& others, std::vector<Entity*>& toAdd){
 if (!FLOATGREATER(speed,0) || ((range -= speed) < speed * 10)){
  if (!flicker){flicker = ONE_SECOND;}
 }
 if (flicker == 1){
  toDelete = true;
 } else {
  Entity::advance(gravity, others, toAdd);
 }
}
bool Bullet::hitFrom(Entity* other, Direction dir){
 if (other == owner){//no matter what, bullets will NEVER interact with their owner
  return false;      //if you need friendly fire, simply change/remove the bullet's owner after it is fired
 } else {
  bool result = Entity::hitFrom(other, dir);
  if (result){
   Unit* toHit = dynamic_cast<Unit*>(other);
   if (toHit){
    toHit->getShotBy(this);
    this->toDelete = true;
   }
  }
  Switch* s = dynamic_cast<Switch*>(other);
  if (s && s->shootable){
   s->toggle();
   this->toDelete = true;
   result = true;
  }
  return result;
 }
}
