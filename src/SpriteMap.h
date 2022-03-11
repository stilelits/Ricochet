/*
 * SpriteMap.h
 *
 *  Created on: Nov 27, 2017
 *      Author: tr_dawson
 */

#ifndef SPRITEMAP_H_
#define SPRITEMAP_H_

#include <Windows.h>
#include <map>
#include <string>
#include <fstream>
#include "Colors.h"
#include "Utils.h"

class SpriteMap {
public:
 SpriteMap(const std::string& file, bool mask = DEFAULT_MASK);
 SpriteMap(int hNew, int wNew);
 SpriteMap(const SpriteMap&); //undefined, so not allowed
 SpriteMap& operator=(const SpriteMap&); //undefined, so not allowed
 int w;
 int h;
 DWORD borderColor;
 DWORD* pixels;
 static std::map<std::string, SpriteMap*> maps;
 static SpriteMap* load(std::string file, bool mask = DEFAULT_MASK);
 void clearPixels();
 void addBorder();
private:
 bool fileFound;
};

#endif /* SPRITEMAP_H_ */
