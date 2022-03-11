/*
 * Game.h
 *
 *  Created on: Nov 21, 2017
 *      Author: tr_dawson
 */

#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#define DEFAULT_GRAVITY (.40)
#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A

#include <windows.h>
#include <vector>
#include <string>
#include <time.h>
#include <windef.h>
#include <winuser.h>

#include "Screen.h"
#include "Entity.h"
#include "DrawObject.h"
#include "Map.h"
#include "Unit.h"
#include "Background.h"
#include "Door.h"
#include "Audio.h"
#include "OptionBox.h"
#include "Script.h"

#define ISKEYDOWN(KEY) VECTOR_CONTAINS(keysDown,KEY)

enum GameMode {modeNull, modeInit, modeActive, modeOver,modePaused,modeDialog};
enum ActionMode {actionNull, actionStandby,actionAttack,actionDefend};

class Game {
public:
 void heal(const std::string& uid, const std::string& healBy="FULL");
 Game(const Game&); //undefined, so not allowed
 Game& operator=(const Game&); //undefined, so not allowed
 static int playGame(HWND hWndNew);
 void processMessages(UINT msg, WPARAM wParam, LPARAM lParam);
 static Game* engine;
 void makeItemScreen(bool cascade = false);
 void makeStatScreen();
 void addBox(TextBox* toAdd = NULL);
 void updateCursor();
 void setMode(GameMode modeNew);
 void checkCursorVisible();
 void load(int fileNum = 1);
 void save(int fileNum = 1);
private:
 void startMenu();
 float entryX;
 float entryY;
 float entryZ;
 std::vector<TextBox*> modelessBoxes;
 void finishCurrentBox();
 TextBox* currentBox;
 explicit Game(HWND hWndNew);
 int run();
 Map* map;
 float gravity;
 Unit* player;
 Entity* cursor;
 bool sysKeyDown;
 void processInput();
 void hideCursor();
 void showCursor();
 void gameOver();
 void enterDoor(Door* toEnter);
 Screen* screen;
 std::vector<int> keysDown;
 std::vector<int> keysJustPressed;
 std::vector<int> keysJustReleased;
 POINTS cursorLoc;
 void pressKey(int key);
 void releaseKey(int key);
 void holdKey(int key);
 HWND hWnd;
 GameMode mode;
 GameMode modeOld;
 ActionMode actionMode;
 int droppedFrames;
 std::string savePath;
 bool cursorHidden;
};

#endif /* GAMEENGINE_H_ */
