/*
 * TextSprite.h
 *
 *  Created on: Nov 28, 2017
 *      Author: tr_dawson
 */

#ifndef TEXTSPRITE_H_
#define TEXTSPRITE_H_

#include "Sprite.h"
#include "TextMap.h"

class TextSprite: public Sprite {
public:
 TextSprite(const std::string& fullTextNew, int hNew, int wNew);
 virtual ~TextSprite(){};
 unsigned word;
 unsigned character;
 bool autoLineBreak;
 void parseWords(std::string text);
 std::vector<std::pair<std::string, DWORD> > words;
 virtual void advance();
};

#endif /* TEXTSPRITE_H_ */
