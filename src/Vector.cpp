/*
 * Vector.cpp
 *
 *  Created on: Nov 22, 2017
 *      Author: tr_dawson
 */

#include "Vector.h"

Vector::Vector(float dxNew, float dyNew) {
 dx = dxNew;
 dy = dyNew;
 magnitude = (dx*dx) + (dy*dy);
}

float Vector::getLength(){
 return sqrt(magnitude);
}
