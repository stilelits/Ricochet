/*
 * Sprite.cpp
 *
 *  Created on: Nov 27, 2017
 *      Author: tr_dawson
 */

#include "Sprite.h"

Sprite::Sprite(int hNew, int wNew, DWORD greenScreenNew): pose(POSE_NULL){
 greenScreen = greenScreenNew;
 h = hNew;
 w = wNew;
 map = NULL;
 frame = NULL;
 mask = false;
 speed = .25;
 coolDown = 0;
 frameNum = -1;
 facing = dirNull;
 poses = NULL;
 silhouette = false;
 done = false;
}

Sprite* Sprite::load(std::string file, bool mask){ //popUp(__FILE__); popUp(__LINE__);
 Sprite* result = new Sprite();                    //popUp(__LINE__);
 result->poses = Poses::getAll(file, mask);        //popUp(__LINE__);
 if (result->poses){                               //popUp(__LINE__);
  result->mask = mask;                             //popUp(__LINE__);
  result->setPose(POSE_NONE);                      //popUp(__LINE__);
  result->h = result->map->h;                      //popUp(__LINE__);
  result->w = result->map->w;                      //popUp(__LINE__);
 } else {                                          //popUp(__LINE__);
  result = NULL;                                   //popUp(__LINE__);
 }                                                 //popUp(__LINE__);
 return result;
}

void Sprite::setFacing(Direction facingNew){
 if (facing != facingNew){
  facing = facingNew;
  map = poses->getPose(pose, facing);
  setFrame(0, true);
 }
}
void Sprite::setSpeed(float speedNew){
 speed = speedNew;
 resetCooldown();
}
void Sprite::resetCooldown(){
 coolDown = FRAMERATE * speed;
 if (!coolDown){coolDown = 1;}
}
void Sprite::setPose(std::string poseNew){         //popUp(__FILE__); popUp(__LINE__);
 if (pose.compare(poseNew)){                       //popUp(__LINE__);
  pose = poseNew;                                  //popUp(__LINE__);
  map = poses->getPose(pose, facing);              //popUp(__LINE__);
  setFrame(0, true);                               //popUp(__LINE__);
 }                                                 //popUp(__LINE__);
}
void Sprite::setWidth(int wNew){
 if (wNew <= map->w){w = wNew;}
}
void Sprite::setFrame(int frameNumNew, bool force){   //if (!force){popUp(__FILE__);}
 if (frameNumNew){                                    //if (!force){popUp(__LINE__);popUp(frameNumNew);popUp(map->w);popUp(this->w);}
  frameNumNew %= (map->w / this->w);                  //if (!force){popUp(__LINE__);}
 }                                                    //if (!force){popUp(__LINE__);}
 if ((force) || frameNum != frameNumNew){             //if (!force){popUp(__LINE__);}
  frameNum = frameNumNew;                             //if (!force){popUp(__LINE__);}
  frame = map->pixels + (this->w * frameNum);         //if (!force){popUp(__LINE__);}
  //frame = map->pixels;                              //if (!force){popUp(__LINE__);}
  resetCooldown();
 }                                                    //if (!force){popUp(__LINE__);}
}

void Sprite::advance(){
 if (coolDown &&  !--coolDown){                       //popUp(__FILE__); popUp(__LINE__); popUp(frameNum + 1);
  setFrame(frameNum + 1, false);                      //popUp(__LINE__);
 }
}
