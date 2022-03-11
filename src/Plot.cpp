/*
 * Plot.cpp
 *
 *  Created on: Nov 27, 2017
 *      Author: tr_dawson
 */

#include "Plot.h"
#include "Entity.h"

std::map<std::string, int> Plot::plots;
std::vector<std::string> Plot::changedKeys;
std::vector<std::pair<std::string, Script*> > Plot::triggers;

void Plot::clear(){
 plots.clear();
}
void Plot::set(const std::string& plotKey, int plotVal){
 plots[plotKey] = plotVal;
 if (!VECTOR_CONTAINS(changedKeys,plotKey)){changedKeys.push_back(plotKey);}
}
int Plot::get(const std::string& plotKey){
 if (!plots.count(plotKey)){set(plotKey,0);}
 return plots[plotKey];
}
void Plot::inc(const std::string& plotKey){
 set(plotKey, get(plotKey) + 1);
}
void Plot::dec(const std::string& plotKey){
 set(plotKey, get(plotKey) - 1);
}
std::vector<std::pair<std::string, int> > Plot::getAll(){
 std::vector<std::pair<std::string, int> > result;
 for(std::map<std::string, int>::iterator it = plots.begin(); it != plots.end(); it++){
  result.push_back(std::make_pair(it->first, it->second));
 }
 return result;
}
bool Plot::evaluate(const std::vector<std::string>& conditional){
 int i = 1; //skip conditional[0], because it must be IF/ELSE/ELSEIF
 bool flip = false;
 if ((conditional.size() > i)&&(!conditional[i].compare(CONDITIONAL_NOT))){flip = !flip; i++;}
 int leftSide = 0;
 if ((conditional.size() > i)&&(isInt(conditional[i]))){leftSide = parseInt(conditional[i++]);} else {leftSide = Plot::get(conditional[i++]);}
 if ((conditional.size() > i)&&(!conditional[i].compare(CONDITIONAL_NOT))){flip = !flip; i++;}
 char op = '>';
 if (conditional.size() > i) {
  if (!conditional[i].compare(CONDITIONAL_EQUALS)){
   op = '='; i++;
  } else if (!conditional[i].compare(CONDITIONAL_GREATER_THAN)){
   op = '>'; i++;
  } else if (!conditional[i].compare(CONDITIONAL_LESS_THAN)){
   op = '<'; i++;
  }
 }
 int rightSide = 0; //needs to eventually compare to other plots
 if (conditional.size() > i) {
  if (isInt(conditional[i])){rightSide = parseInt(conditional[i++]);} else {rightSide = Plot::get(conditional[i++]);}
 }
 bool result;
 switch (op){
 case '=': result = leftSide == rightSide; break;
 case '<': result = leftSide < rightSide; break;
 case '>': result = leftSide > rightSide; break;
 }
 //popUp("evaluated " + toStr(leftSide) + op + toStr(rightSide) + " as " + toStr(result));
 if (flip){result = !result;}
 return result;
}
void Plot::notifyAll(){
 for (unsigned i=0; i < changedKeys.size(); i++){
  for (unsigned j=0; j < triggers.size(); j++){
   if (!changedKeys[i].compare(triggers[j].first)){
    triggers[j].second->trigger(changedKeys[i]);
   }
  }
 }
 changedKeys.clear();
}
void Plot::setTrigger(const std::string& plotKey, Script* toNotify){
 triggers.push_back(std::make_pair(plotKey, toNotify));
}
void Plot::clearTriggers(){
 triggers.clear();
}
