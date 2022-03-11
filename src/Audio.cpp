/*
 * Audio.cpp
 *
 *  Created on: Nov 27, 2017
 *      Author: tr_dawson
 */

#include "Audio.h"

void Audio::playBGM(const std::string& file){ //popUp(alias);
 const std::string& alias = file + "BGM";
 if(currentBGM==alias){return;}
 stopBGM();
 if (currentBGM.compare("none")){
  std::string path = g_folder + "/audio/" + file + ".mp3";
  mci("open",      path, "type mpegvideo alias " + alias);
  mci("seek",     alias, "to start");
  mci("setaudio", alias, "volume to " + toStr(volBGM));
  mci("play",     alias, "repeat");
 }
 currentBGM=alias;
}
void Audio::mci(const std::string& cmd, const std::string& alias, const std::string& extra){
 std::string fullcmd=cmd+" "+alias;
 if(extra.size()){fullcmd=fullcmd+" "+extra;}
 mciSendString(fullcmd.c_str(),NULL,0,NULL);
}
void Audio::stopBGM(){
 mci("stop", currentBGM);
 currentBGM = "";
}
void Audio::pauseBGM(){
 mci("pause", currentBGM);
}
void Audio::resumeBGM(){
 mci("resume", currentBGM);
}
void Audio::openSFX(const std::string& file){
 if(isSFXOpen(file)){return;}
 std::string path = g_folder + "/audio/" + file + ".mp3";
 for(int i=0;i<MAX_SAME_SOUND;i++){
  mci("open",  path, "type mpegvideo alias " + file + toStr(i));
 }
 openedSFX[file]=0;
}
bool Audio::isSFXOpen(const std::string& file){
 return (openedSFX.count(file)!=0);
}
void Audio::doSFX(const std::string& file){
 openSFX(file);
 std::string alias = file + toStr(openedSFX[file]);
 mci(    "seek", alias, "to start");
 mci("setaudio", alias, "volume to " + toStr(volSFX));
 mci(    "play", alias);
 openedSFX[file]++;
 if(openedSFX[file]==MAX_SAME_SOUND){openedSFX[file]=0;}
}
std::map<std::string, int> Audio::openedSFX;
int Audio::volSFX=50;
int Audio::volBGM=200;
std::string Audio::currentBGM;
