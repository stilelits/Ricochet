/*
 * Switch.cpp
 *
 *  Created on: Nov 27, 2017
 *      Author: tr_dawson
 */

#include "Switch.h"

Switch::Switch() {
 name = "GENERIC_SWITCH";
 h = 40;
 sprite = Sprite::load("switchOff", true);
 setColor(0x00FF0000);
 isOn = false;
 shootable = true;
 solid = false;
 interact = INTERACT_TOUCH;
 z = Z_DOORGROUND;
}
void Switch::interactWith(Entity* other){
 this->toggle();
}
void Switch::toggle(){
 isOn = !isOn;
 if (isOn){
  color = 0x0000FF00; //green
  sprite = Sprite::load("switchOn", true);
  Plot::set(this->name, 1);
 } else {
  color = 0x00FF0000; //red
  sprite = Sprite::load("switchOff", true);
  Plot::set(this->name, 0);
 }
}

