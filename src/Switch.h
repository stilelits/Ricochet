/*
 * Switch.h
 *
 *  Created on: Nov 27, 2017
 *      Author: tr_dawson
 */

#ifndef SWITCH_H_
#define SWITCH_H_

#include "Entity.h"
#include "Plot.h"

class Switch: public Entity {
public:
 Switch();
 virtual ~Switch(){};
 bool isOn;
 void toggle();
 bool shootable;
 virtual void interactWith(Entity* other);
};

#endif /* SWITCH_H_ */
