/*
 * Bar.h
 *
 *  Created on: Dec 13, 2017
 *      Author: tr_dawson
 */

#ifndef BAR_H_
#define BAR_H_

#include "TextBox.h"

class Bar: public TextBox {
public:
 Bar(int valMaxNew);
 int val;
 int valMax;
 DWORD backColor;
 void refresh();
 virtual void setColor(DWORD colorNew);
};

#endif /* BAR_H_ */
