/*
 * Plot.h
 *
 *  Created on: Nov 27, 2017
 *      Author: tr_dawson
 */

#ifndef PLOT_H_
#define PLOT_H_

#include <string>
#include <vector>
#include <map>
#include "Utils.h"
#define PLOT_DESTROYED(e)       (e->uid + "_PLOT_DESTROYED")
#define PLOT_HAS(i)             ("HAS_" + replaceAll(i->name," ","_"))
#define CONDITIONAL_NOT          "NOT"
#define CONDITIONAL_EQUALS       "="
#define CONDITIONAL_GREATER_THAN ">"
#define CONDITIONAL_LESS_THAN    "<"

class Entity;
class Script;

class Plot {
public:
 static void clear();
 static void set(const std::string& plotKey, int plotVal = 1);
 static int get(const std::string& plotKey);
 static bool evaluate(const std::vector<std::string>& conditional);
 static void inc(const std::string& plotKey);
 static void dec(const std::string& plotKey);
 static void notifyAll();
 static void setTrigger(const std::string& plotKey, Script* toNotify);
 static void clearTriggers();
 static std::vector<std::pair<std::string, int> > getAll();
private:
 static std::map<std::string, int> plots;
 static std::vector<std::string> changedKeys;
 static std::vector<std::pair<std::string, Script*> > triggers;
};

#endif /* PLOT_H_ */
