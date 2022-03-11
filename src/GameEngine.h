#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#define START_FULL 0
#define DEBUG_DIALOG 1
#define RANDOM_MODE 0
#define NO_FRIENDLY_FIRE 1
#define CROSSARRAY(dest,vec1,vec2) \
         dest[0] = vec1[1]*vec2[2]-vec1[2]*vec2[1]; \
         dest[1] = vec1[2]*vec2[0]-vec1[0]*vec2[2]; \
         dest[2] = vec1[0]*vec2[1]-vec1[1]*vec2[0];         
#define DOTARRAY(vec1,vec2) (vec1[0]*vec2[0]+vec1[1]*vec2[1]+vec1[2]*vec2[2])
#define NEGARRAY(vec1) \
         vec1[0] = -vec1[0]; \
         vec1[1] = -vec1[1]; \
         vec1[2] = -vec1[2];         
#define SUBARRAY(dest,vec1,vec2) \
          dest[0]=vec1[0]-vec2[0]; \
          dest[1]=vec1[1]-vec2[1]; \
          dest[2]=vec1[2]-vec2[2];          
#define ADDARRAY(dest,vec1,vec2) \
          dest[0]=vec1[0]+vec2[0]; \
          dest[1]=vec1[1]+vec2[1]; \
          dest[2]=vec1[2]+vec2[2];       
#define MULTARRAY(dest,vec1,scalar) \
          dest[0]=vec1[0]*scalar; \
          dest[1]=vec1[1]*scalar; \
          dest[2]=vec1[2]*scalar;       
#define DIVARRAY(dest,vec1,scalar) \
          dest[0]=vec1[0]/scalar; \
          dest[1]=vec1[1]/scalar; \
          dest[2]=vec1[2]/scalar;       
#define ARRTRIPLET(dest,x,y,z) \
          dest[0] = x; \
          dest[1] = y; \
          dest[2] = z;       
#define FLOATWITHIN(x,y,z) (((x)-(y)>-(z))&&((x)-(y)<(z)))
#define FLOATEQUAL(x,y) (FLOATWITHIN(x,y,EPSILON))
#define FLOATLESS(x,y) (x+EPSILON<y)
#define FLOATGREATER(x,y) (x-EPSILON>y)
#define INF (1000000000)
#define EPSILON             0.00001
#define PI (3.14159)
#define FRAMERATE (60)
#define FRAMELENGTHCLOCKS (CLOCKS_PER_SEC / FRAMERATE)
#define FRAMELENGTHMILLIS (1000 / FRAMERATE)
#define DIALOG_CASCADE (20)
#define MAX_INVENTORY (8)
#define INVENTORY_MSG ("ITEMS")
#define STATUS_MSG ("STATUS")
#define DROP_MSG ("DROP")
#define RETURN_MSG ("RETURN")
#define QUIT_MSG ("QUIT")
#define EXAMINE_MSG ("EXAMINE")
#define USE_MSG ("USE")
#define CURSOR_SENSITIVITY (5)
#define GAMEOVER_MSG ("(Game Over. Press any key to return to title.)")
#define NEWGAME_MSG ("NEW GAME")
#define CONTINUE_MSG ("CONTINUE")
#define MENU_MSG ("")
#define CONFIRM_MSG ("(Are you sure?)")
#define INSTRUCTIONS_MSG ("(Esc: Menu)\n(W: Up)\n(A: Left)\n(S: Down)\n(D: Right)\n(Spacebar: Interact)")
#define SAVE_MSG ("(Save your progress?)")
#define CONFIRM_QUIT_MSG ("(Are you sure you want to quit?)")
#define CONFIRM_DROP_MSG ("(Are you sure you want to drop the " + currentItem->name + "?)")
#define CANNOT_DROP_MSG ("(You cannot drop the " + currentItem->name + ".)")
#define CONFIRM_EQUIP_MSG (PICKUP_MSG + ("\n(Would you like to equip it now?)"))
#define CONFIRM_CONSUME_MSG (PICKUP_MSG + ("\n(Would you like to use it now?)"))
#define PICKUP_MSG ("(You got a " + currentItem->name + "!)")
#define CANNOT_PICKUP_MSG ("(You are carrying too much to get the " + currentItem->name + ".)")
#define CANNOT_PICKUP_CONSUMABLE_MSG (CANNOT_PICKUP_MSG + ("\n(Would you like to use it now instead?)"))
#define ALREADY_EQUIPPED_MSG ("(The " + currentItem->name + " is already equipped.)")
#define CONFIRM_YES ("Yes")
#define CONFIRM_NO ("No")
#define PAUSED_MSG ("PAUSED")
#define CURSOR_COLOR_STANDBY (PIXEL_RED)
#define CURSOR_COLOR_ATTACK (PIXEL_RED)
#define CURSOR_COLOR_DEFEND (PIXEL_BLUE)
enum GameMode {modeInit, modeMenu,modeActive, modeOver,modePaused,modeDialog};
enum ActionMode {actionStandby,actionAttack,actionDefend};
/*
#include "Audio.h"
#include "Plot.h"
#include "GameScreen.h"
#include "DrawObject.h"
#include "MenuBox.h"
#include "Event.h"
#include "Item.h"
#include "Entity.h"
#include "Bullet.h"
#include "Unit.h"
#include "Mouse.h"
#include "Map.h"
*/
class GameEngine {
public:
 GameEngine(HWND hwndNew);
 int run();
 void processMessages(UINT msg, WPARAM wParam, LPARAM lParam);
private:
 std::vector<int> keysPressed;
 HWND hwnd;
 GameMode mode;
 GameMode modeOld;
 ActionMode actionMode;
 int droppedFrames;
 std::string savePath;
 bool cursorHidden;
 /*
 std::vector<Item*> inventory;
 Mouse* mouse;
 GameScreen* screen;
 Map* map;
 Unit* player;
 TextBox* dialogActive;
 TextBox* dialogNew;
 Item* currentItem;
 void openBox(TextBox* activeNew);
 void titleMenu();
 void interact();
 void setMode(GameMode modeNew);
 void setCursorFromMouse();
 void newGame();
 void hideCursor();
 void showCursor();
 void pickUp(Item* item);
 void processNewInteractions();
 void keyDown(int key);
 void keyUp(int key);
 void processInput();
 void closeAllDialogs();
 void closeDialog();
 void saveGame();
 void loadGame();
 void openDialog(std::string text="DIALOG",bool enterDialogMode=true);
 void openMenu(std::string prompt="",MenuType menuID=menuNull);
 bool isKeyPressed(int key);
 void setActionMode(ActionMode actionNew);
 void enAttack();
 void enDefend();
 void unAttack();
 void unDefend();
 */
};
#include "GameEngine.cpp"
#endif