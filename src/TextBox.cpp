/*
 * TextBox.cpp
 *
 *  Created on: Nov 28, 2017
 *      Author: tr_dawson
 */

#include "TextBox.h"
#include "Game.h"

TextBox::TextBox(const std::string& textNew, int wNew): text(textNew) { //popUp(__FILE__);
 owner = NULL;                                                          //popUp(__LINE__);
 h = TEXTBOX_DEFAULT_HEIGHT;                                            //popUp(__LINE__);
 hOriginal = h;
 w = wNew;                                                              //popUp(__LINE__);
 wOriginal = w;
 x = PADDING;                                                           //popUp(__LINE__);
 parent = NULL;                                                         //popUp(__LINE__);
 closeAfter = FRAMERATE * 2;                                            //popUp(__LINE__);
 modal = true;                                                          //popUp(__LINE__);
 cascade = false;                                                       //popUp(__LINE__);
 anchor = anchorNW;                                                     //popUp(__LINE__);
 fitSize();                                                             //popUp(__LINE__);
}
void TextBox::setParent(TextBox* parentNew){
 if (parent){
  y -= (parent->y - parent->h);
  x -= parent->x;
  z -= parent->z;
 }
 parent = parentNew;
 if (parent){
  y += (parent->y - parent->h);
  x += parent->x;
  z += parent->z;
 }
}
void TextBox::setAnchor(ScreenAnchor anchorNew){
 anchor = anchorNew;
 switch (anchor){
 case anchorNull: break;
 case anchorNW:
  if (parent){
   x = parent->x;
   y = (parent->y - parent->h) + h;
  } else {
   x = 0;
   y = h;
  }
  x += PADDING;
  y += PADDING;
  break;
 case anchorNE:
  if (parent){
   x = parent->x + parent->w - w;
   y = (parent->y - parent->h) + h;
  } else {
   x = SCREEN_PIXEL_WIDTH - w;
   y = h;
  }
  x -= PADDING;
  y += PADDING;
  break;
 case anchorSW:
  if (parent){
   x = parent->x;
   y = parent->y;
  } else {
   x = 0;
   y = SCREEN_PIXEL_HEIGHT;
  }
  x += PADDING;
  y -= PADDING;
  break;
 case anchorSE:
  if (parent){
   x = parent->x + parent->w - w;
   y = parent->y;
  } else {
   x = SCREEN_PIXEL_WIDTH - w;
   y = SCREEN_PIXEL_HEIGHT;
  }
  x -= PADDING;
  y -= PADDING;
  break;
 }
}
void TextBox::fitSize(){                               //popUp(__FILE__);
 if (text.size()){                                     //popUp(__LINE__);
  sprite = new TextSprite(text, hOriginal, wOriginal); //popUp(__LINE__);
  forceFinish();                                       //popUp(__LINE__);
  TextMap* map = static_cast<TextMap*>((sprite)->map); //popUp(__LINE__);
  h = map->maxHeight();                                //popUp(__LINE__);
  w = map->maxWidth();                                 //popUp(__LINE__);
 }                                                     //popUp(__LINE__);
 sprite = new TextSprite(text, h, w);                  //popUp(__LINE__);
 setAnchor(anchor);                                    //popUp(__LINE__);
}
void TextBox::advance(){
 if (sprite->done){
  if (closeAfter > 0){
   closeAfter--;
  } else if (closeAfter == 0){
   finish();
  }
 } else {
  sprite->advance();
 }
}
void TextBox::forceFinish(){
 do {advance();} while (!sprite->done); //if sprite is already done, this will finish() the box
}
void TextBox::finish(){
 this->toDelete = true;
 if (script){script->execNext();}
}
