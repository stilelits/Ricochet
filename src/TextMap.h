/*
 * TextMap.h
 *
 *  Created on: Nov 28, 2017
 *      Author: tr_dawson
 */

#ifndef TEXTMAP_H_
#define TEXTMAP_H_

#define TEXTMAP_DEFAULT_TEXT    (PIXEL_WHITE)
#define TEXTMAP_DEFAULT_PADDING (10)
#define TEXTMAP_DEFAULT_FONT    ("Courier New")
#define TEXTMAP_DEFAULT_WEIGHT  (FW_BOLD)
#define TEXTMAP_DEFAULT_POINTS  (20)

#include "SpriteMap.h"
#include <stdio.h>
#include <string.h>

class TextMap: public SpriteMap {
private:
 DWORD textColor;
 HDC hDC;
 BITMAPINFO bmpi;
 HFONT fontStock;
 HBITMAP hBmp;
 RECT rectFull;
 int xMax;
 int yMax;
public:
 int xWrite;
 int yWrite;
 int charHeight;
 int padding;
 int charWidth;
 int maxWidth();
 int maxHeight();
 bool spaceFor(std::string word);
 void nextLine();
 void writeChar(char toWrite);
 TextMap(int hNew, int wNew);
 void clear();
 void setColor(DWORD textColorNew);
 void setFont(int height=TEXTMAP_DEFAULT_POINTS, std::string fontName = TEXTMAP_DEFAULT_FONT, int weight=TEXTMAP_DEFAULT_WEIGHT);
};

#endif /* TEXTMAP_H_ */
