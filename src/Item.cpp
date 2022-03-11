/*
 * Item.cpp

 *
 *  Created on: Nov 27, 2017
 *      Author: tr_dawson
 */
#include "Game.h"
#include "Item.h"

Item::Item() {
 name = "GENERIC_ITEM";
 h = 20;
 w = 20;
 dam = 0;
 def = 0;
 hp = 0;
 coolDown = 0;
 setAmmoType(ammoNull);
 sprite = NULL;
 setColor(PIXEL_PURPLE);
 usesLeft = 0;
 owner = NULL;
 canR = false;
 canL = false;
 canB = false;
 canA = false;
 solid = false;
 stunTime = ONE_SECOND;
 description = "NO DESCRIPTION AVAILABLE";
}
void Item::setAmmoType(AmmoType typeNew){
 type = typeNew;
 switch (type){
 case ammoNormal:
  setSFX("bullet");
  fireRate = 20;
  break;
 case ammoRifle:
  setSFX("bullet");
  fireRate = 30;
  break;
 case ammoCannon:
  setSFX("cannon");
  fireRate = 50;
  break;
 default:
  color = PIXEL_GREEN;
  fireRate = 1;
  break;
 }
}
void Item::cool(){
 if (coolDown > 0){coolDown -= 1;}
}
Bullet* Item::fire(){                       //popUp(__FILE__);
 if (coolDown < 1){                         //popUp(__LINE__);
  coolDown = fireRate / owner->weaponSpeed; //popUp(__LINE__);
  Audio::doSFX(sfx);                        //popUp(__LINE__);
  return new Bullet(owner, this);
 } else {
  return NULL;
 }
}
void Item::setName(const std::string& nameNew){
 DrawObject::setName(nameNew);
 Script* script = Script::fromFile("items/" + name);
 if (script){ //ignore failure
  for (std::vector<std::string> line=script->nextLine();line.size();line=script->nextLine()){
   if (!line[0].compare("description")){
    description = line[1];
   } else if (!line[0].compare("RH")){
    canR = true;
   } else if (!line[0].compare("LH")){
    canL = true;
   } else if (!line[0].compare("BH")){
    canB = true;
   } else if (!line[0].compare("ACC")){
    canA = true;
   } else if (!line[0].compare("DAM")){
    dam = parseInt(line[1]);
   } else if (!line[0].compare("DEF")){
    def = parseFloat(line[1]);
   } else if (!line[0].compare("HP")){
    hp = parseInt(line[1]);
   } else if (!line[0].compare("AMMO")){
    if (!line[1].compare("NORMAL")){
     setAmmoType(ammoNormal);
    } else if (!line[1].compare("RIFLE")){
     setAmmoType(ammoRifle);
    } else if (!line[1].compare("CANNON")){
     setAmmoType(ammoCannon);
    }
   } else if (!line[0].compare("USE")){
    if (line.size() == 1){
     usesLeft = parseInt(line[1]);
    } else {
     usesLeft = 1;
    }
   }
  }
 }
}
