/*
 * TextBox.h
 *
 *  Created on: Nov 28, 2017
 *      Author: tr_dawson
 */

#ifndef TEXTBOX_H_
#define TEXTBOX_H_

#define TEXTBOX_DEFAULT_WIDTH (300)
#define TEXTBOX_DEFAULT_HEIGHT (100)
#define PADDING (20)

#include "DrawObject.h"
#include "Utils.h"
#include "TextSprite.h"

enum ScreenAnchor {anchorNull, anchorNE, anchorSE, anchorSW, anchorNW};

class Entity;

class TextBox: public DrawObject {
protected:
 ScreenAnchor anchor;
 int hOriginal;
 int wOriginal;
public:
 TextBox(const std::string& textNew, int wNew = TEXTBOX_DEFAULT_WIDTH);
 virtual ~TextBox(){};
 std::string text;
 void setParent(TextBox* parentNew);
 void advance();
 virtual void setAnchor(ScreenAnchor anchorNew);
 void forceFinish();
 virtual void finish();
 bool modal;
 Entity* owner;
 int closeAfter;
 void fitSize();
 bool cascade;
 TextBox* parent;
};

#endif /* TEXTBOX_H_ */
