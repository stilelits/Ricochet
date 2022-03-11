/*
 * Map.h
 *
 *  Created on: Nov 21, 2017
 *      Author: tr_dawson
 */

#ifndef MAP_H_
#define MAP_H_

#include <algorithm>
#include <vector>
#include <fstream>
#include "Entity.h"
#include "Unit.h"
#include "Utils.h"
#include "Switch.h"
#include "Audio.h"
#include "Item.h"

class Map {
public:
 explicit Map(int topNew, int rightNew, int leftNew = -100, int bottomNew = -100);
 explicit Map(const std::string& pathNew);
 int top;
 int left;
 int bottom;
 int right;
 std::string path;
 bool loadMap(const std::string& pathNew);
 void addEntity(Entity* toAdd);
 void delEntity(Entity* toErase);
 void delAll();
 Entity* getEntityByUID(const std::string& uid);
 void addAll(const std::vector<Entity*>& toAdd);
 Door* advance(float gravity, std::vector<Entity*>& toAdd);
 void interact(Entity* toInteract);
 std::vector<Entity*> entities;
 std::vector<Door*> doors;
};

#endif /* MAP_H_ */
