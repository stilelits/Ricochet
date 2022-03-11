/*
 * Entity.cpp
 *
 *  Created on: Nov 21, 2017
 *      Author: tr_dawson
 */

//GOOD FOR POSITIVE

#include "Entity.h"
#include "Game.h"

Entity::Entity(float xNew, float yNew, int zNew, float wNew, float hNew): DrawObject(xNew, yNew, zNew, wNew, hNew) {
 //popUp("new entity being created");
 name = "GENERIC_ENTITY";
 setColor(PIXEL_DARK(PIXEL_GRAY));
 weight = 1;
 setMaxDx(6);
 setMaxDy(10);
 d = 1;      //most entities should have 1 depth (i.e. no ability to affect objects at other distances than their own)
 //pure entities will mostly be obstacles, like walls and floors and ceilings
 absolutePosition=false;
 speed = 0;
 weightless = true;
 solid = true;
 script = new Script(this);
 bounciness = 1; //reflecting objects will not be slowed down at all
 interact = INTERACT_NONE;
 immobile = true;
 stop();
}
void Entity::setMaxDx(float maxDxNew){
 maxDx = maxDxNew;
 minDx = -maxDxNew;
}
void Entity::setMaxDy(float maxDyNew){
 maxDy = maxDyNew;
 minDy = -maxDyNew; //maximum fall speed...should this be separated and based on weight or something instead?
}
void Entity::interactWith(Entity* other){ //popUp(__FILE__);
 if (script){                             //popUp(__LINE__);
  script->execFromStart();                //popUp(__LINE__);
 }
}
void Entity::setSFX(const std::string& sfxNew){
 sfx = sfxNew;
 if (sfx.size()){Audio::openSFX(sfx);}
}
void Entity::patrolTo(Direction patrolNew){
 impetusX = dirNull;
 impetusY = dirNull;
 patrol = patrolNew;
 switch(patrol){
 case dirRight:
 case dirLeft:
  impetusX = patrol;
  sprite->setFacing(impetusX);
  break;
 case dirUp:
 case dirDown:
  impetusY = patrol;
  break;
 }
}
void Entity::advance(float gravity, const std::vector<Entity*>& others, std::vector<Entity*>& toAdd){
 if (!immobile){
  if (!weightless){dy -= weight * gravity;} //gravity is a POSITIVE number indicating a NEGATIVE pull on the weight of the object
  if (dx < minDx) {dx = minDx;}
  if (dx > maxDx) {dx = maxDx;}
  if (dy < minDy) {dy = minDy;}    //terminal velocity limits the speed at which we can fall
  if (dy > maxDy) {dy = maxDy;}
  bool zeroDx = FLOATEQUAL(dx, 0);
  bool zeroDy = FLOATEQUAL(dy, 0);
  if (!zeroDx || !zeroDy){ //if either one of them are non-zero
   float t;
   float tX;
   float tY;
   Entity* other;
   Direction dir;
   Direction dirX;
   Direction dirY;
   std::map<float, std::vector<std::pair<Entity*, Direction> > > othersByDistance;
   for (unsigned i=0;i<others.size();i++){
    other = others[i];
    if (other!=this){
     tX = 4; //t represents the fraction of the frame needed to impact it
     tY = 4; //any value higher than 1 means it will NOT impact during this frame
     if (FLOATGREATEROREQUAL(LEFT(this), RIGHT(other))){             //we are currently to the RIGHT
      if (FLOATLESSOREQUAL(LEFT(this) + this->dx, RIGHT(other))){    //we WILL impact it on this frame
       dirX = dirRight;
       tX = (RIGHT(other) - LEFT(this)) / this->dx;                  //impossible for dx to be near zero in this situation
      }
     } else if (FLOATLESSOREQUAL(RIGHT(this), LEFT(other))){         //we are currently to the LEFT
      if (FLOATGREATEROREQUAL(RIGHT(this) + this->dx, LEFT(other))){ //we WILL impact it on this frame
       dirX = dirLeft;
       tX = (LEFT(other) - RIGHT(this)) / this->dx;                  //impossible for dx to be near zero
      }
     } else { //we are currently within the top/bottom bounds of the object
      dirX = dirNull;
      tX = 2; //we require no time to impact it: 2 means there CAN be an impact, but tX will not be relevant, and there is no directionality
     }
     if (FLOATGREATEROREQUAL(BOTTOM(this), TOP(other))){             //we are currently to the TOP
      if (FLOATLESSOREQUAL(BOTTOM(this) + this->dy, TOP(other))){    //we WILL impact it on this frame
       dirY = dirUp;
       tY = (TOP(other) - BOTTOM(this)) / this->dy;                  //impossible for dy to be near zero in this situation
      }
     } else if (FLOATLESSOREQUAL(TOP(this), BOTTOM(other))){         //we are currently to the BOTTOM
      if (FLOATGREATEROREQUAL(TOP(this) + this->dy, BOTTOM(other))){ //we WILL impact it on this frame
       dirY = dirDown;
       tY = (BOTTOM(other) - TOP(this)) / this->dy;                  //impossible for dy to be near zero
      }
     } else { //we are currently within the top/bottom bounds of the object
      dirY = dirNull;
      tY = 2; //we require no time to impact it: 2 means there CAN be an impact, but tX will not be relevant
     }
     if ((tX < 3)&&(tY < 3)){
      if (FLOATLESS(tX, tY)){
       t = tX;
       dir = dirX;
      } else {
       t = tY;
       dir = dirY;
      }
      if (FLOATLESS(t, 0)){t = 0;} //when touching another entity, it sometimes shows up as a slight negative t
      if (FLOATLESS(t, 2)){othersByDistance[t].push_back(std::make_pair(other, dir));}
     }
    }
   }
   bool LR = true;
   bool UD = true;
   if (othersByDistance.size() > 0){
    for (std::map<float, std::vector<std::pair<Entity*, Direction> > >::iterator it=othersByDistance.begin(); (it!=othersByDistance.end())&&(LR||UD); ++it ){
     t = it->first;
     for (unsigned k=0;k<it->second.size();k++){
      other = it->second[k].first;
      dir = it->second[k].second;
      //if (this->solid && other->solid){
      if (hitFrom(other, dir)){ //this method will process the overlap, and tell us whether or not to bounce off it
       switch (dir){
       case dirLeft:
       case dirRight:
        if (FLOATGREATER(t,0)){x += dx * t;}        //go directly to the LR intersection point
        LR = false;                                //can no longer move in an LR direction during this frame
        dx *= -1 * bounciness * other->bounciness; //bounce...do we need to factor weight into this?
        break;
       case dirUp:
       case dirDown:
        if (FLOATGREATER(t,0)){y += dy * t;}        //go directly to the UD intersection point
        UD = false;                                //can no longer move in a UD direction during this frame
        dy *= -1 * bounciness * other->bounciness; //bounce...do we need to factor weight into this?
        break;
       }
      }
     }
    }
   }
   if (LR){//we were not impeded going left/right
    x += dx;
   } else {
    switch (patrol){
    case dirLeft:  patrolTo(dirRight); break;
    case dirRight: patrolTo(dirLeft); break;
    }
   }
   if (UD){
    y += dy;
   } else {
    switch (patrol){
    case dirUp:  patrolTo(dirDown); break;
    case dirDown: patrolTo(dirUp); break;
    }
   }//we were not impeded going up/down
  }
 }
 updateSprite();
 //if (timer){timer->advance();}
 DrawObject::advance();
}
void Entity::updateSprite(){
 if (sprite){
  if (dy > 0){ //jumping
   sprite->setPose(POSE_JUMP);
  } else if (dy < 0){ //falling
   sprite->setPose(POSE_FALL);
  } else { //on level ground
   if (impetusX == dirNull){
    sprite->setPose(POSE_STAND);
   } else {
    sprite->setPose(POSE_WALK);
   }
  }
 }
}
bool Entity::hitFrom(Entity* other, Direction dir){
 return (this->solid && other->solid && FRONT(this) > BACK(other) && FRONT(other) > BACK(this)); //no other requirements for pure Entities...other classes will override this
}
void Entity::stop(){
 stopX();
 stopY();
 patrol = dirNull;
 facing = dirNull;
}
void Entity::stopX(){
 dx=0;
 impetusX = dirNull;
}
void Entity::stopY(){
 dy=0;
 impetusY = dirNull;
}
void Entity::accelX(float toAdd){
 dx+=toAdd;
 if (dx > maxDx) {dx = maxDx;} else if (dx < minDx) {dx = minDx;}
}
void Entity::accelY(float toAdd){
 dy+=toAdd;
 if (dy > maxDy) {dy = maxDy;} else if (dy < minDy) {dy = minDy;}
}
bool Entity::canInteractWith(Entity* other){
 switch(other->interact){
 case INTERACT_NONE:   return false;
 case INTERACT_INSIDE: return this->isInside(other);
 default:              return this->isWithinDistance(other, this->radius() + other->radius() + other->interact);
 }
}
bool Entity::isInside(Entity* other){
 return (
  FLOATGREATEROREQUAL(LEFT(this),   LEFT(other))   &&
  FLOATLESSOREQUAL   (RIGHT(this),  RIGHT(other))  &&
  FLOATGREATEROREQUAL(BOTTOM(this), BOTTOM(other)) &&
  FLOATLESSOREQUAL   (TOP(this),    TOP(other))
 );
}
bool Entity::isTouching(Entity* other){
 return this->isWithinDistance(other, this->radius() + other->radius());
}
float Entity::radius(){
 return this->minorAxis() / 2; //maybe should be major axis?
}
float Entity::minorAxis(){
 if (h < w){  return h; } else {  return w; }
}
float Entity::majorAxis(){
 if (h > w){  return h; } else {  return w; }
}
bool Entity::isWithinDistance(Entity* other, int distance){
 if (distance < 0){return false;}
 float rise = other->centerY() - this->centerY();
 float run = other->centerX() - this->centerX();
 float mag = (rise*rise) + (run*run);
 return distance * distance >= mag;
}
void Entity::setName(const std::string& nameNew){
 DrawObject::setName(nameNew);
 Script* scriptNew = Script::fromFile("scripts/" + nameNew);
 if (scriptNew){
  scriptNew->owner = this;
  scriptNew->execFromStart();
 }
}
