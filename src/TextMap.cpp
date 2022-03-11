/*
 * TextMap.cpp
 *
 *  Created on: Nov 28, 2017
 *      Author: tr_dawson
 */

#include "TextMap.h"

TextMap::TextMap(int hNew, int wNew): SpriteMap(hNew, wNew){ //popUp(__FILE__);
 padding = TEXTMAP_DEFAULT_PADDING;
 xWrite = padding;
 yWrite = padding;
 SetRect(&rectFull,0,0,w,h);
 hDC = CreateCompatibleDC(NULL);
 SetBkMode(hDC,TRANSPARENT);
 bmpi.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
 bmpi.bmiHeader.biWidth         = w;
 bmpi.bmiHeader.biHeight        = -h;
 bmpi.bmiHeader.biPlanes        = 1;
 bmpi.bmiHeader.biBitCount      = 32;
 bmpi.bmiHeader.biCompression   = BI_RGB;
 bmpi.bmiHeader.biSizeImage     = 0;
 bmpi.bmiHeader.biXPelsPerMeter = 0;
 bmpi.bmiHeader.biYPelsPerMeter = 0;
 bmpi.bmiHeader.biClrUsed       = 0;
 bmpi.bmiHeader.biClrImportant  = 0;
 bmpi.bmiColors[0].rgbBlue=0;
 bmpi.bmiColors[0].rgbGreen=0;
 bmpi.bmiColors[0].rgbRed=0;
 bmpi.bmiColors[0].rgbReserved=0;
 clear();
 setColor(TEXTMAP_DEFAULT_TEXT);
 setFont();
}
void TextMap::clear(){
 clearPixels();
 addBorder();
 hBmp = CreateDIBSection(hDC, &bmpi, DIB_RGB_COLORS, (void**)pixels, NULL, 0);
 SelectObject(hDC,hBmp);
 SetDIBits(hDC,hBmp,0,h,pixels,&bmpi,DIB_RGB_COLORS);
 xWrite = padding;
 yWrite = padding;
 xMax = 0;
 yMax = 0;
}
void TextMap::nextLine(){
 xWrite = padding;
 yWrite += charHeight;
}
void TextMap::setFont(int height, std::string fontName, int weight){
 HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
 LOGFONT logfont;
 GetObject(hFont, sizeof(LOGFONT), &logfont);
 logfont.lfWeight=weight;
 logfont.lfHeight=height;
 strcpy(logfont.lfFaceName,fontName.c_str());
 SelectObject(hDC, CreateFontIndirect(&logfont));
 RECT rectToDraw={0,0,0,0};
 DrawText(hDC," ",1,&rectToDraw,DT_CALCRECT);
 charWidth = rectToDraw.right;
 charHeight = rectToDraw.bottom;
}
void TextMap::setColor(DWORD textColorNew){
 textColor = textColorNew;
 borderColor = textColorNew;
 SetTextColor(hDC,(textColorNew&0xFF00FF00)|((textColorNew&0x000000FF)<<16)|((textColorNew&0x00FF0000)>>16));
}
void TextMap::writeChar(char toWrite){
 if (toWrite == '\n'){
  nextLine();
 } else {
  if (xWrite + padding > w){nextLine();}
  SetDIBits(hDC,hBmp,0,h,pixels,&bmpi,DIB_RGB_COLORS);                 //put the pixels into the hdc
  RECT rectToDraw={xWrite,yWrite,0,0};                                 //pointing to where the character should be drawn
  DrawText(hDC, &toWrite, 1, &rectToDraw, DT_CALCRECT);                //needs TWO calls: first to calculate the rectangle,
  DrawText(hDC, &toWrite, 1, &rectToDraw, DT_LEFT|DT_EXTERNALLEADING); //and second to actually draw it
  GetDIBits(hDC, hBmp, 0, h, pixels, &bmpi, DIB_RGB_COLORS);           //get teh pixels back out of the hdc into the array
  if (xWrite > xMax){xMax = xWrite;}
  if (yWrite > yMax){yMax = yWrite;}
  xWrite += charWidth;
 }
}
bool TextMap::spaceFor(std::string word){
 if (xWrite == padding){return true;} //if there's not room now, there never will be
 int len = strlen(word.c_str());
 std::size_t found = word.find("\n");
 if (found != std::string::npos){len = found;} //if the word contains a newline, only need to check the first chunk of it
 return (w - (xWrite + charWidth + padding)) >= len * charWidth;
}
int TextMap::maxWidth(){
 return xMax + charWidth + padding;
}
int TextMap::maxHeight(){
 return yMax + charHeight + padding;
}
