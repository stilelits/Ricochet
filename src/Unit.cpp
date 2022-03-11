/*
 * Unit.cpp
 *
 *  Created on: Nov 21, 2017
 *      Author: tr_dawson
 */

//GOOD FOR POSITIVE

#include "Unit.h"
#include "Game.h"
#include "Bullet.h"

Unit::Unit() {
 //popUp("new unit being created");
 name = "GENERIC_UNIT";
 h = TILE * 2; //units default to two tiles high
 sprite = Sprite::load("Unit", true);
 setColor(PIXEL_DARK(PIXEL_PURPLE) | PIXEL_ALPHA);
 agi = .2;   //ability to accelerate
 weightless = false;
 wallJump = false;
 maxJumps = 2;
 atk = 1;
 //mpBar = new Bar(mpMax);
 weaponSpeed = .5;
 ai = aiNull;
 visualRange = 200;
 faction = factionNull;
 def = 1;
 hurtOnTouch = false;
 target = NULL;
 dead = 0;
 stunShoot = false;
 hpMax = 20;
 hp = hpMax;
 hpBar = new Bar(hpMax);
 hpBar->setColor(PIXEL_RED | PIXEL_ALPHA);
 mpMax = 20;
 mp = mpMax;
 mpBar = new Bar(mpMax);
 mpBar->setColor(PIXEL_BLUE | PIXEL_ALPHA);
 mpBar->y += mpBar->h;
 stunMove = false;
 fireR = false;
 fireL = false;
 rhCap = 1;
 lhCap = 1;
 accCap = 1;
 bounciness = 0; //most units should NOT bounce off things!
 jumpsLeft = maxJumps;
 interact = 40;
 immobile = false;
 canPickUp = false;
 inventoryMax = 8;
 stunned = 0;
 patrol = dirNull;
}
void Unit::takeDamage(int damage){
 addHp(damage * -def);
}
void Unit::die(){
 stop();
 dead = ONE_SECOND / 2;
 solid = false;
 immobile = true;
 if (sprite){
  sprite->silhouette = true;
  sprite->greenScreen = 0x80000000 | PIXEL_RED; //see-through solid red
 }
}
void Unit::addHp(int toAdd){
 hp += toAdd;
 if (hp > hpMax){hp = hpMax;} //maybe can change this through accessory effects...?
 if (hp < 1){hp = 0; die();}
 if (hpBar){hpBar->val = hp; hpBar->refresh();}
}
void Unit::getStunned(int stunFrames){
 if (!stunned){dx = 0; dy = 0;} //only stop still with the initial stun, NOT with subsequent stuns
 stunFrames += (stunFrames % 2); //forces it to be an EVEN number
 if (stunFrames > stunned){stunned = stunFrames + (stunned%2);} //the % will preserve the even/odd of our flicker
 if (stunFrames > flicker){flicker = stunFrames + (flicker%2);}
}
void Unit::interactWith(Entity* other){
 if (other->x > this->x){
  sprite->setFacing(dirRight);
 } else {
  sprite->setFacing(dirLeft);
 }
 Entity::interactWith(other);
}
bool Unit::hitFrom(Entity* other, Direction dir){
 Item* item = dynamic_cast<Item*>(other);
 if (canPickUp){ //items do not need to be solid in order to pick up
  if (item && inventory.size() < inventoryMax)  {
   inventory.push_back(item);
   Plot::set(PLOT_DESTROYED(item));
   Plot::inc(PLOT_HAS(item));
   item->toDelete = true;
   item->owner = this;
   TextBox* toAdd = new TextBox(item->name);
   toAdd->forceFinish();
   toAdd->setAnchor(anchorSW);
   toAdd->modal = false;
   Game::engine->addBox(toAdd);
  }
 }
 bool result = Entity::hitFrom(other,dir);
 if (result){
  Bullet* b = dynamic_cast<Bullet*>(other);
  if (b){
   result = (this != b->owner);
  } else {
   switch (dir){
   case dirLeft:
   case dirRight:
    if (wallJump){resetJumps();}
    break;
   case dirUp: //hitting FROM above
    resetJumps();
    break;
   }
   //also handle Unit-to-Unit collision damage
   Unit* toHit = dynamic_cast<Unit*>(other);
   if (toHit){
    if (hurtOnTouch)  {
     if (!toHit->stunned){toHit->takeDamage(2);}
     toHit->getStunned(FRAMERATE);
    } else if (toHit->hurtOnTouch){
     if (!stunned){takeDamage(2);}
     getStunned(FRAMERATE);
    }
   }
  }
 }
 return result;
}
void Unit::getShotBy(Bullet* bullet){ //popUp(name + " has just been shot by " + bullet->owner->name);
 if (!stunned){takeDamage(bullet->weapon->dam * bullet->owner->atk);}
 getStunned(bullet->weapon->stunTime * bullet->owner->atk); //even if we were already stunned, reset the stun duration
 if (script){
  script->trigger("FIRST_HIT", true);
  script->removeTrigger("FIRST_HIT");
 }
}
void Unit::resetJumps(){
 jumpsLeft = maxJumps;
}
void Unit::jump(){
 if((maxJumps == -1) || (jumpsLeft > 0)){ //-1 is infinite jumps
  this->accelY(this->maxDy); //immediately go to full upward speed
  jumpsLeft--;
 }
}
void Unit::moveRight(){
 impetusX = dirRight;
 if (sprite){sprite->setFacing(impetusX);}
}
void Unit::moveLeft(){
 impetusX = dirLeft;
 if (sprite){sprite->setFacing(impetusX);}
}
void Unit::setFaction(Faction factionNew){
 enemyFactions.clear();
 faction = factionNew;
 switch (faction){
 case factionPlayer:
  enemyFactions.push_back(factionEnemy);
  break;
 case factionEnemy:
  enemyFactions.push_back(factionPlayer);
  break;
 case factionChaotic:
  enemyFactions.push_back(factionEnemy);
  enemyFactions.push_back(factionPlayer);
  enemyFactions.push_back(factionChaotic);
  break;
 }
}
void Unit::doAI(const std::vector<Entity*>& others){
 if (ai != aiNull && enemyFactions.size()){ //combat ai only makes sense if we have an ai type, and enemies
  if (!target){
   for (unsigned k=0;k<others.size();k++){                                                                         //popUp(__LINE__);
    Unit* u = dynamic_cast<Unit*>(others[k]);                                                                      //popUp(__LINE__);
    if (u && this != u && VECTOR_CONTAINS(enemyFactions, u->faction) && isWithinDistance(others[k], visualRange)){ //popUp(__LINE__);
     target = u;
     if (ai != aiNeutral){patrolTo(dirNull);}
     break;                                                                                                        //popUp(__LINE__);
    }                                                                                                              //popUp(__LINE__);
   }                                                                                                               //popUp(__LINE__);
  }
  if (target){                                                                                                     //popUp(__LINE__);
   int centerThis   = this->centerX();
   int centerTarget = target->centerX();
   if (centerThis + 1 < centerTarget){sprite->setFacing(dirRight);} else {sprite->setFacing(dirLeft);}
   if (!isWithinDistance(target, visualRange)){                                                                     //popUp(__LINE__);
    fireR = false;                                                                                                  //popUp(__LINE__);
    fireL = false;                                                                                                  //popUp(__LINE__);
   } else {
    fireR = true;                                                                                                  //popUp(__LINE__);
    fireL = true;                                                                                                  //popUp(__LINE__);
    switch (ai){
    case aiDefensive:
     if (centerThis + 1 < centerTarget){       //we are to the left
      impetusX = dirLeft;                      //move away
     } else if (centerThis > centerTarget){    //we are to the right
      impetusX = dirRight;                     //move away
     } else {                                  //we are exactly lined up. switch directions
      switch (impetusX){
      case dirLeft: impetusX = dirRight; break;
      case dirRight:
      default:      impetusX = dirLeft;  break;
      }
     }
     break;
    case aiAggressive:
     if (LEFT(this) > RIGHT(target)){ //if we are to the RIGHT
      impetusX = dirLeft;
     } else if (RIGHT(this) < LEFT(target)){ //if we are to the LEFT
      impetusX = dirRight;
     } else {
      impetusX = dirNull;
     }
     break;
    }
   }
  }
 }
}
void Unit::advance(float gravity, const std::vector<Entity*>& others, std::vector<Entity*>& toAdd){
 if (stunned && !--stunned){
  /*handle what, if anything, happens when we come out of stun*/
 }
 if (dead > 0 && !--dead){
  toDelete = true;
 } else {
  doAI(others);
  if (!stunned || stunMove){
   switch (impetusX){
   case dirRight: accelX(this->agi);  break;
   case dirLeft:  accelX(-this->agi); break;
   default:                           break;
   }
   if (weightless){
    switch (impetusY){
    case dirUp:   accelY(this->agi);  break;
    case dirDown: accelY(-this->agi); break;
    default:                          break;
    }
   }
   for (unsigned k=0;k<bh.size();k++){bh[k]->cool();} //cool down all weapons in both hands
   if (!stunned || stunMove){
    if (fireR && fireL){
     fireAll(bh, toAdd);
    } else if (fireR){
     fireAll(rh, toAdd);
    } else if (fireL){
     fireAll(lh, toAdd);
    }
   }
  }
  Entity::advance(gravity, others, toAdd);
 }
}
void Unit::fireAll(const std::vector<Item*>& toFire, std::vector<Entity*>& newBullets){ //popUp(__FILE__);
 for (unsigned k=0;k<toFire.size();k++){                                                //popUp(__LINE__);
  Bullet* bullet = toFire[k]->fire();                                                   //popUp(__LINE__);
  if (bullet){                                                                          //popUp(__LINE__);
   newBullets.push_back(bullet);                                                        //popUp(__LINE__);
   return; //do not allow multiple bullets in a single frame...this won't slow things down much, but will be more visually appealing
  }
 }
}
void Unit::use(const std::string& useType, Item* item){
 if (!useType.compare("USE")){
  //handle specific use effects (e.g. restore health) here
  addHp(item->hp);
  if (item->usesLeft > 0 && !--item->usesLeft){
   Plot::dec(PLOT_HAS(item));
   VECTOR_REMOVE(inventory, item);
  }
 } else {
  if (!useType.compare(UNIT_BH)){
   if (rh.size() >= rhCap){unUse(rh[rh.size()-1]);}
   rh.push_back(item);
   if (lh.size() >= lhCap){unUse(lh[lh.size()-1]);}
   lh.push_back(item);
  } else {
   std::vector<Item*>* vec;
   int cap=0;
   if (!useType.compare(UNIT_RH)){
    vec = &rh;
    cap = rhCap;
   } else if (!useType.compare(UNIT_LH)){
    vec = &lh;
    cap = lhCap;
   } else if (!useType.compare(UNIT_ACC)){
    vec = &acc;
    cap = accCap;
   }
   if (cap){
    if (vec->size() >= cap){unUse(vec->at(vec->size()-1));} //remove the most RECENT item added to that slot
    vec->push_back(item);
   }
  }
  item->currentUse = useType;
  bh.push_back(item);
  //handle specific addition effects (e.g. stat changes) here
  //str += item->str;
  //def += item->def;
  //hpMax += item->hp; addHp(0);
 }
}
void Unit::unUse(Item* item){
 if (item->currentUse.size()){
  if (!item->currentUse.compare(UNIT_BH)){
   VECTOR_REMOVE(rh, item);
   VECTOR_REMOVE(lh, item);
  } else {
   std::vector<Item*>* vec=NULL;
   if (!item->currentUse.compare(UNIT_RH)){
    vec = &rh;
   } else if (!item->currentUse.compare(UNIT_LH)){
    vec = &lh;
   } else if (!item->currentUse.compare(UNIT_ACC)){
    vec = &acc;
   }
   VECTOR_POINTER_REMOVE(vec, item); //this will cause an error if an incorrect currentUse is set
  }
  VECTOR_REMOVE(bh, item);
  item->currentUse.clear();
  //handle specific removal effects (e.g. stat changes) here
  //str -= item->str;
  //def -= item->def;
  //hpMax -= item->hp; addHp(0);
 }
}
