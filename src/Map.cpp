/*
 * Map.cpp
 *
 *  Created on: Nov 21, 2017
 *      Author: tr_dawson
 */

#include "Map.h"

Map::Map(int topNew, int rightNew, int leftNew, int bottomNew) {
 top    = topNew;
 left   = leftNew;
 bottom = bottomNew;
 right  = rightNew;
}
Map::Map(const std::string& pathNew){
 top    =  5000;
 left   = -100;
 bottom = -100;
 right  =  5000;
 loadMap(pathNew);
}

bool Map::loadMap(const std::string& pathNew){         //popUp(__FILE__);
 path = pathNew;
 delAll();                                          //popUp(__LINE__);
 Script* script = Script::fromFile("maps/" + path);
 if (script){
  script->map = this;
  script->execFromStart(); //popUp(__LINE__);
  return true;
 } else {
  return false;
 }
}
Entity* Map::getEntityByUID(const std::string& uid){
 for (unsigned k=0;k<entities.size();k++){if (!entities[k]->uid.compare(uid)){return entities[k];}}
 //popUp("error: could not find " + uid + " in the current map");
 return NULL;
}
Door* Map::advance(float gravity, std::vector<Entity*>& toAdd){
 for (unsigned k=0;k<doors.size();k++){
  if (doors[k]->entered){return doors[k];}
 }
 for (unsigned k=0;k<entities.size();k++){
  Unit* u = dynamic_cast<Unit*>(entities[k]);
  if(u){
   u->advance(gravity, entities, toAdd);
  } else {
   entities[k]->advance(gravity, entities, toAdd);
  }
 }
 for (unsigned k=0;k<entities.size();k++){
  if (entities[k]->toDelete){delEntity(entities[k]);}
 }
 return NULL;
}
void Map::addAll(const std::vector<Entity*>& toAdd){
 for (unsigned k=0;k<toAdd.size();k++){addEntity(toAdd[k]);}
}
void Map::addEntity(Entity* toAdd){
 Door* door = dynamic_cast<Door*>(toAdd);
 if (door){doors.push_back(door);}
 entities.push_back(toAdd);
}
void Map::delEntity(Entity* toErase){
 Door* door = dynamic_cast<Door*>(toErase);
 if (door){VECTOR_REMOVE(doors, door);}
 VECTOR_REMOVE(entities, toErase);
}
void Map::delAll(){
 entities.clear();
 doors.clear();
}
void Map::interact(Entity* toInteract){
 for (unsigned k=0;k<entities.size();k++){
  Entity* other = entities[k];
  if ((toInteract != other)&&(toInteract->canInteractWith(other))){
   other->interactWith(toInteract);
  }
 }
}
