/*
 * Poses.h
 *
 *  Created on: Nov 28, 2017
 *      Author: tr_dawson
 */

#ifndef POSES_H_
#define POSES_H_

#include <string>
#include "SpriteMap.h"

#define POSE_NULL   "NOT_SET"
#define POSE_STAND  "_Stand"
#define POSE_WALK   "_Walk"
#define POSE_JUMP   "_Jump"
#define POSE_FALL   "_Fall"
#define POSE_OPEN   "_Open"
#define POSE_CLOSED "_Closed"
#define POSE_NONE   POSE_STAND
#define POSE_RIGHT  "_Right"
#define POSE_LEFT   "_Left"

class Poses {
private:
 Poses(const std::string& name, bool mask = DEFAULT_MASK);
 static std::map<std::string, Poses*> allPoses;
 std::map<std::string, std::map<Direction, SpriteMap*> > poseMap;
 std::vector<std::string> poseStrings;
 static std::string LEFT;
 static std::string RIGHT;
 bool fileFound;
 void loadPose(const std::string& name, const std::string& pose, bool mask = DEFAULT_MASK, Direction facing = dirNull);
public:
 std::string spriteName;
 static Poses* getAll(const std::string& name, bool mask = DEFAULT_MASK);
 SpriteMap* getPose(const std::string& pose, Direction facing = dirNull);
};

#endif /* POSES_H_ */
