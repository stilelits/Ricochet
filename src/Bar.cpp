/*
 * Bar.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: tr_dawson
 */

#include "Bar.h"

Bar::Bar(int valMaxNew): TextBox("", 150) {
 valMax = valMaxNew;
 val = valMax;
 h = 10;
 TextSprite* ts = new TextSprite("", h, w);
 sprite = ts;
 TextMap* tm = static_cast<TextMap*>(ts->map);
 tm->setFont(13);
 tm->padding = 4;
 setAnchor(anchorNE);
 setColor(PIXEL_RED | PIXEL_ALPHA);
}
void Bar::setColor(DWORD colorNew){
 color = colorNew;
 backColor = PIXEL_LIGHTEN(colorNew, 1, 2);
 refresh();
}
void Bar::refresh(){
 sprite->map->clearPixels();
 sprite->map->addBorder();
 int width = w;
 int breakPoint = 1 + width - (width * val / valMax);
 int currentColor;
 int j;
 for (int i = (h-1) * width - 1; i >= width; i--){
  if (!((i + 1) % width)){
   currentColor = backColor;
   j = breakPoint;
  }
  if (!--j){currentColor = color;}
  sprite->map->pixels[i] = currentColor;
 }
}
