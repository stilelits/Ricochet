/*
 * Script.h
 *
 *  Created on: Nov 30, 2017
 *      Author: tr_dawson
 */

#ifndef SCRIPT_H_
#define SCRIPT_H_

#include <vector>
#include "Utils.h"
#include "Plot.h"

class Map;

class Entity;
class TextBox;
class Script {
public:
 static Script* fromFile(const std::string& path);
 explicit Script(Entity* ownerNew = NULL);
 void append(const std::string& toAdd);
 void appendLine(std::vector<std::string> toAdd);
 std::vector<std::vector<std::string> > lines;
 std::map<std::string, std::vector<int> > triggers;
 unsigned currentLine;
 Map* map;
 std::vector<std::string> nextLine();
 bool execFromStart();
 bool execNext();
 bool execCurrent();
 bool execLine(unsigned newLine);
 Entity* owner;
 void trigger(const std::string& plotKey, bool force=false);
 void removeTrigger(const std::string& plotKey);
 std::string fullText();
private:
 int switchVal(const std::string& str);
};

#endif /* SCRIPT_H_ */
