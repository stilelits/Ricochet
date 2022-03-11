/*
 * Poses.cpp
 *
 *  Created on: Nov 28, 2017
 *      Author: tr_dawson
 */

#include "Poses.h"

Poses::Poses(const std::string& name, bool mask): spriteName(name) {//must guarantee that at least poseMap[POSE_NONE] exists
 if (!poseStrings.size()){
  poseStrings.push_back(POSE_STAND);
  poseStrings.push_back(POSE_WALK);
  poseStrings.push_back(POSE_JUMP);
  poseStrings.push_back(POSE_FALL);
  poseStrings.push_back(POSE_OPEN);
  poseStrings.push_back(POSE_CLOSED);
 }
 poseMap[POSE_NONE][dirNull] = SpriteMap::load(name, mask); //first, load it with no trailing string. guarantees that poseMap[POSE_NONE][dirNull] exists!
 fileFound = poseMap[POSE_NONE][dirNull];
 if (fileFound){
  for (unsigned k=0; k< poseStrings.size();k++){ //then, load everything possible
   loadPose(name, poseStrings[k], mask, dirNull);
   loadPose(name, poseStrings[k], mask, dirLeft);
   loadPose(name, poseStrings[k], mask, dirRight);
  }
 }
}
void Poses::loadPose(const std::string &name, const std::string& pose, bool mask, Direction facing){
 SpriteMap* result = NULL;
 switch (facing){
 case dirNull:  result = SpriteMap::load(name + pose,              mask); break;
 case dirRight: result = SpriteMap::load(name + pose + POSE_RIGHT, mask); break;
 case dirLeft:  result = SpriteMap::load(name + pose + POSE_LEFT,  mask); break;
 }
 if (result){poseMap[pose][facing] = result;} //if it exists, put it in the map, otherwise ignore
}

Poses* Poses::getAll(const std::string& name, bool mask){
 if (!allPoses.count(name)){
  Poses* result = new Poses(name, mask);
  if (result->fileFound){
   allPoses[name] = result;
  } else {
   allPoses[name] = NULL;
  }
 }
 return allPoses[name];
}

SpriteMap* Poses::getPose(const std::string& pose, Direction facing){ //non-static: the constructor guarantees that poseMap[POSE_NONE] exists
 std::map<Direction, SpriteMap*>* directions;
 if (poseMap.count(pose)){directions = &poseMap[pose];} else {directions = &poseMap[POSE_NONE];}
 SpriteMap* result;
 if (directions->count(facing)){result = (*directions)[facing];} else {result = (*directions)[dirNull];}
 return result;
}

std::map<std::string, Poses*> Poses::allPoses;
