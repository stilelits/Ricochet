/*
 * OptionBox.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: tr_dawson
 */

#include "OptionBox.h"
#include "Game.h"

OptionBox::OptionBox(const std::string& promptNew, const std::vector<std::pair<std::string, unsigned> >& optionsNew): prompt(promptNew), options(optionsNew), TextBox(promptNew){
 selected = 0;
 closeAfter = -1;
 modal = true;
 refresh();
}

void OptionBox::refresh(){                        //popUp(__FILE__);
 std::vector<std::string> lines;                  //popUp(__LINE__);
 if (prompt.size()){                              //popUp(__LINE__);
  lines.push_back(prompt);                        //popUp(__LINE__);
  lines.push_back("");                            //popUp(__LINE__);
 }                                                //popUp(__LINE__);
 for (unsigned k=0;k<options.size();k++){         //popUp(__LINE__); popUp(options[k].first);
  if (k == selected){                             //popUp(__LINE__);
   lines.push_back("[RED]" + options[k].first);   //popUp(__LINE__);
  } else {                                        //popUp(__LINE__);
   lines.push_back("[WHITE]" + options[k].first); //popUp(__LINE__);
  }                                               //popUp(__LINE__);
 }                                                //popUp(__LINE__);
 text = joinVector(lines,"\n");                   //popUp(__LINE__);
 fitSize();                                       //popUp(__LINE__);
}
void OptionBox::selectUp(){
 if (selected > 0){
  selected--;
  refresh();
  forceFinish();
 }
}
void OptionBox::selectDown(){
 if (selected < options.size() - 1){
  selected++;
  refresh();
  forceFinish();
 }
}
void OptionBox::finish(){
 toDelete = true;
 script->currentLine = options[selected].second;
 script->execNext();
}
