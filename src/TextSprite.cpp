/*
 * TextSprite.cpp
 *
 *  Created on: Nov 28, 2017
 *      Author: tr_dawson
 */

#include "TextSprite.h"

TextSprite::TextSprite(const std::string& text, int hNew, int wNew): Sprite(hNew, wNew, PIXEL_GREEN){ //popUp(__FILE__);
 h = hNew;
 w = wNew;
 word = 0;                                                                                            //popUp(__LINE__);
 character = 0;                                                                                       //popUp(__LINE__);
 autoLineBreak = true;                                                                                //popUp(__LINE__);
 map = new TextMap(h, w);                                                                             //popUp(__LINE__);
 frame = map->pixels;                                                                                 //popUp(__LINE__);
 parseWords(text);
}
void TextSprite::parseWords(std::string text){
 words.clear();
 DWORD color = PIXEL_WHITE;
 text = replaceAll(text, "[", " [");
 text = replaceAll(text, "]", "] ");
 std::vector<std::string> tempWords = splitString(text);
 for (unsigned k = 0; k < tempWords.size();k++){
  if (!tempWords[k].compare("[RED]")){
   color = PIXEL_RED;
  } else if (!tempWords[k].compare("[BLUE]")){
   color = PIXEL_BLUE;
  } else if (!tempWords[k].compare("[GREEN]")){
   color = PIXEL_GREEN;
  } else if (!tempWords[k].compare("[WHITE]")){
   color = PIXEL_WHITE;
  } else {
   words.push_back(std::make_pair(removeAll(tempWords[k]," "), color));
  }
 }
 if (words.size()){
  static_cast<TextMap*>(map)->setColor(words[0].second);
 }
 //std::string temp; for (unsigned k=0;k<words.size();k++){temp += words[k].first + "_";} popUp(temp);
}
void TextSprite::advance(){
 if (word < words.size()){
  TextMap* textMap = static_cast<TextMap*>(map);
  if (character < words[word].first.size()){             //popUp(toStr((int)word) + ":" + toStr((int)character) + ": " + toStr((char)words[word].first.at(character)) + "(" + toStr((int)words[word].first.at(character)) + ")");
   textMap->writeChar(words[word].first.at(character++));
  } else {
   if (++word < words.size()){                           //popUp(__LINE__); popUp(words[word].first);
    textMap->setColor(words[word].second);               //popUp(__LINE__);
    character=0;                                         //popUp(__LINE__);
    if (textMap->spaceFor(words[word].first)){           //popUp(__LINE__);
     if (textMap->xWrite > textMap->padding) {           //popUp(__LINE__);
      textMap->writeChar(' ');                           //popUp(__LINE__);
     }                                                   //popUp(__LINE__);
    } else {                                             //popUp(__LINE__);
     textMap->nextLine();                                //popUp(__LINE__);
    }
   } else {
    done = true;
   }
  }
 }
}
