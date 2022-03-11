/*
 * Audio.h
 *
 *  Created on: Nov 27, 2017
 *      Author: tr_dawson
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#define MAX_SAME_SOUND 5

#include <iostream>
#include <windows.h>
#include <mmsystem.h>  // mciSendString()
#include <conio.h>
#include <algorithm>
#include <string>
#include <map>
#include "Utils.h"

class Audio {
public:
 static std::string BGM;
 static void playBGM(const std::string& file);
 static void pauseBGM();
 static void resumeBGM();
 static void stopBGM();
 static void openSFX(const std::string& file);
 static bool isSFXOpen(const std::string& file);
 static void doSFX(const std::string& file);
 static std::map<std::string, int> openedSFX;
 static int volBGM;
 static int volSFX;
 static std::string currentBGM;
 static void mci(const std::string& cmd, const std::string& alias, const std::string& extra=std::string(""));
};

#endif /* AUDIO_H_ */
