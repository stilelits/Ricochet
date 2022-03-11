/*
 * Game.cpp
 *
 *  Created on: Nov 21, 2017
 *      Author: tr_dawson
 */

#include "Game.h"

#include <algorithm>
#include <iterator>
Game::Game(HWND hWndNew) {
 hWnd = hWndNew;
 mode = modeNull;
 sysKeyDown = false;
 modeOld = modeNull;
 actionMode = actionNull;
 droppedFrames = 0;
 cursor = new Entity();
 cursor->invisible = true;
 cursor->solid = false;
 cursor->immobile = true; //we don't want it affected by gravity
 cursor->y = -25;
 cursor->x = 850;
 cursor->w = 13;
 cursor->h = 13;
 cursor->z = Z_FOREGROUND;
 cursor->setName("Cursor");
 if (cursor->sprite){cursor->sprite->greenScreen = PIXEL_RED | PIXEL_ALPHA;}
 cursorHidden = true;
 screen = new Screen(hWnd);
 gravity = DEFAULT_GRAVITY;
 player = NULL;
 currentBox = NULL;
 entryX = 0;
 entryY = 0;
 entryZ = 0;
 map = NULL;
}
void Game::heal(const std::string&uid, const std::string& healBy){ //popUp(__FILE__);
 Unit* u = dynamic_cast<Unit*>(map->getEntityByUID(uid));          //popUp(__LINE__);
 if (u){                                                           //popUp(__LINE__); //popUp(healBy);
  if (isInt(healBy)){                                              //popUp(__LINE__);
   u->addHp(parseInt(healBy));                                     //popUp(__LINE__);
  } else {                                                         //popUp(__LINE__);
   u->addHp(u->hpMax - u->hp);                                     //popUp(__LINE__);
  }                                                                //popUp(__LINE__);
 }
}
void Game::startMenu(){                                  //popUp(__FILE__);
 Audio::stopBGM();
 Script::fromFile("scripts/MainMenu")->execFromStart();  //popUp(__LINE__);
 if (fileExists("maps/1")){static_cast<OptionBox*>(currentBox)->selectDown();}
}
void Game::save(int fileNum){
 std::ofstream file(("maps/" + toStr(fileNum)).c_str()); //this will overwrite!
 file << "\nNPC Player: uid Player";
 for (unsigned k=0;k<player->inventory.size();k++){
  Item* item = player->inventory[k];
  file << "\nINV \"" + item->name + "\"";
  if (item->currentUse.size()){
   file << "\n" + item->currentUse + " " + toStr((int)k);
  }
 }
 //need to include inventory and equipped items here somehow
 file << "\nEND Player";
 file << "\nDOOR: uid toSaveRoom";
 file << "\n dest " + map->path;
 file << "\n destX " + toStr((int)player->x);
 file << "\n destY " + toStr((int)player->y);
 file << "\n destZ " + toStr((int)player->z);
 file << "\nEND DOOR";
 std::vector<std::pair<std::string, int> > allPlots = Plot::getAll();
 for (unsigned k=0;k<allPlots.size();k++){
  if (allPlots[k].second){file << "\nSET " + allPlots[k].first + " " + toStr(allPlots[k].second);}
 }
 file.close();
}
void Game::load(int fileNum){
if (!fileExists("maps/" + toStr(fileNum))){fileNum = 0;}
Plot::clear();
if (map){map->delAll();}
if (screen){screen->delAll();}
currentBox = NULL;
map = new Map(toStr(fileNum)); //save files are simply maps with numeric integer file names
player = static_cast<Unit*>(map->getEntityByUID("Player"));
player->setColor(PIXEL_LIGHTEN(PIXEL_BLUE, 3, 4) | PIXEL_ALPHA);
player->canPickUp = true;
player->target = cursor;
player->stunMove = true;
player->name = "Player";
player->weaponSpeed = 1;
player->setFaction(factionPlayer);
Door* d = static_cast<Door*>(map->getEntityByUID("toSaveRoom"));
enterDoor(d);
screen->focusOn(player);
setMode(modeActive);
}
void Game::enterDoor(Door* toEnter) {
 screen->delAll();
 map = new Map(toEnter->dest);
 Door* destDoor = dynamic_cast<Door*>(map->getEntityByUID(toEnter->destDoor));
 if (destDoor){
  player->x = destDoor->x    + (destDoor->w / 2) - (player->w / 2);
  player->y = destDoor->y;
  player->z = toEnter->destZ; //do NOT go to the same z as the door itself, or we will phase through the walls
 } else {
  player->x = toEnter->destX + (toEnter->w / 2)  - (player->w / 2);
  player->y = toEnter->destY;
  player->z = toEnter->destZ;
 }
 entryX = player->x;
 entryY = player->y;
 entryZ = player->z;
 map->addEntity(cursor);
 map->addEntity(player);
 screen->addObject(player->hpBar);
 screen->addObject(player->mpBar);
 screen->addAll(map->entities);
 screen->setBounds(map);
 //popUp("finished entering " + toEnter->name);
}
void Game::gameOver() {
 screen->delAll();
 map->delAll();
 player = NULL;
 startMenu();
 //setMode(modeInit); //this will allow the player to load a saved game eventually
}
void Game::setMode(GameMode modeNew) {
 if (modeNew != mode) {
  modeOld = mode;
  switch (modeOld) {
  //do handling for getting OUT of the old mode here, if needed
  }
  mode = modeNew;
  switch (mode) {
  case modeInit: load(0);    break;
  case modeOver: gameOver(); break;
  }
 }
}
int Game::playGame(HWND hWndNew) {
 engine = new Game(hWndNew);
 engine->startMenu(); //start menu for new game or load
 return engine->run();
}
int Game::run() {                                         //popUp(__FILE__); popUp(__LINE__);
 MSG Msg;                                                 //popUp(__LINE__);
 clock_t frameStart = clock();                            //popUp(__LINE__);
 droppedFrames = 0;                                       //popUp(__LINE__);
 std::vector<Entity*> toAdd;                              //popUp(__LINE__);
 Door* toEnter = NULL;                                    //popUp(__LINE__);
 while (Msg.message != WM_QUIT) {                         //popUp(__LINE__);
  if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)) {         //popUp(__LINE__);
   TranslateMessage(&Msg);                                //popUp(__LINE__);
   DispatchMessage(&Msg);                                 //popUp(__LINE__);
  }                                                       //popUp(__LINE__);
  if (mode == modePaused) {                               //popUp(__LINE__);
   frameStart = clock();                                  //popUp(__LINE__);
  } else if (frameStart + FRAMELENGTHCLOCKS <= clock()) { //popUp(__LINE__);
   processInput();                                        //popUp(__LINE__);
   while (frameStart + FRAMELENGTHCLOCKS <= clock()) {    //popUp(__LINE__);
    if (currentBox) {                                     //popUp(__LINE__);
     currentBox->advance();                               //popUp(__LINE__);
     if (currentBox->toDelete) {                          //popUp(__LINE__);
      addBox(NULL);                                       //popUp(__LINE__);
     }                                                    //popUp(__LINE__);
    }                                                     //popUp(__LINE__);
    for (unsigned k = 0; k < modelessBoxes.size(); k++) { //popUp(__LINE__);
     modelessBoxes[k]->advance();                         //popUp(__LINE__);
    }                                                     //popUp(__LINE__);
    if (mode == modeActive) {                             //popUp(__LINE__);
     toAdd.clear();                                       //popUp(__LINE__);
     toEnter = map->advance(gravity, toAdd);              //popUp(__LINE__);
     if (player){                                         //popUp(__LINE__);
      if (player->y < map->bottom) {                      //popUp(__LINE__);
       player->takeDamage(player->hp / 2);                //popUp(__LINE__);
       player->getStunned(ONE_SECOND);                    //popUp(__LINE__);
       player->x = entryX;                                //popUp(__LINE__);
       player->y = entryY;                                //popUp(__LINE__);
       player->z = entryZ;                                //popUp(__LINE__);
      }                                                   //popUp(__LINE__);
      if (player->toDelete){gameOver();}                  //popUp(__LINE__);
     }                                                    //popUp(__LINE__);
     if (toEnter) {                                       //popUp(__LINE__);
      enterDoor(toEnter);                                 //popUp(__LINE__);
     } else {                                             //popUp(__LINE__);
      map->addAll(toAdd);                                 //popUp(__LINE__);
      screen->addAll(toAdd);                              //popUp(__LINE__);
     }                                                    //popUp(__LINE__);
    }                                                     //popUp(__LINE__);
    Plot::notifyAll();                                    //popUp(__LINE__);
    frameStart += FRAMELENGTHCLOCKS;                      //popUp(__LINE__);
    droppedFrames++;                                      //popUp(__LINE__);
   }                                                      //popUp(__LINE__);
   droppedFrames--;                                       //popUp(__LINE__);
   screen->draw();                                        //popUp(__LINE__);
   screen->update();                                      //popUp(__LINE__);
  }                                                       //popUp(__LINE__);
 }                                                        //popUp(__LINE__);
 return Msg.wParam;
}
void Game::pressKey(int key) { //NEW key presses
 if (!ISKEYDOWN(key)) {
  keysDown.push_back(key);
  if (sysKeyDown) {
   switch (key) {
   case VK_RETURN: screen->toggleFull(); break; //add this back in eventually
   }
  } else {
   switch (mode) {
   case modeActive:
    switch (key) {
    case VK_LBUTTON: player->fireL = true;                                         break;
    case VK_RBUTTON: player->fireR = true;                                         break;
    case VK_SPACE: player->jump();                                                 break;
    case VK_W: map->interact(player);                                              break;
    case VK_A: if (ISKEYDOWN(VK_D)){player->stopX();} else {player->moveLeft();}   break;
    case VK_D: if (ISKEYDOWN(VK_A)){player->stopX();} else {player->moveRight();}  break;
    case VK_ESCAPE:
     if (!currentBox || currentBox->sprite->done) {
      Script::fromFile("scripts/GameMenu")->execFromStart();
     } else {
      currentBox->forceFinish();
     }
     break;
    }
    break;
    case modeDialog:
     switch (key) {
     case VK_UP:
     case VK_LEFT:
     case VK_W:
     case VK_A: {OptionBox* option = dynamic_cast<OptionBox*>(currentBox); if (option){option->selectUp();    break;}}
     case VK_DOWN:
     case VK_RIGHT:
     case VK_S:
     case VK_D: {OptionBox* option = dynamic_cast<OptionBox*>(currentBox); if (option){option->selectDown();  break;}}
     case VK_RETURN:
     case VK_SPACE:
     case VK_ESCAPE: if (!currentBox->sprite->done) {currentBox->forceFinish();} else {currentBox->finish();} break;
     }
     break;
   }
  }
 }
}
void Game::addBox(TextBox* toAdd) {                           //popUp(__FILE__); //popUp(__LINE__);
 if (currentBox) {                                            ////popUp(__LINE__);
  if (toAdd) {                                                ////popUp(__LINE__);
   if (toAdd->cascade) {                                      ////popUp(__LINE__);
    currentBox->toDelete = false;                             ////popUp(__LINE__);
    toAdd->setParent(currentBox);                             ////popUp(__LINE__);
   } else {                                                   ////popUp(__LINE__);
    currentBox->toDelete = true;                              ////popUp(__LINE__);
    toAdd->setParent(currentBox->parent);                     ////popUp(__LINE__);
   }                                                          ////popUp(__LINE__);
  } else {                                                    ////popUp(__LINE__);
   currentBox->toDelete = true;                               ////popUp(__LINE__);
  }                                                           ////popUp(__LINE__);
 } else if (toAdd && toAdd->modal) {                          ////popUp(__LINE__);
  setMode(modeDialog);                                        ////popUp(__LINE__);
 }                                                            ////popUp(__LINE__);
 if (toAdd) {                                                 ////popUp(__LINE__);
  screen->addObject(toAdd);                                   ////popUp(__LINE__);
  if (toAdd->modal) {                                         ////popUp(__LINE__);
   currentBox = toAdd;                                        ////popUp(__LINE__);
  } else {                                                    ////popUp(__LINE__);
   modelessBoxes.push_back(toAdd);                            ////popUp(__LINE__);
  }                                                           ////popUp(__LINE__);
 } else if (currentBox) {                                     ////popUp(__LINE__);
  if (!currentBox->parent && currentBox->modal) {
   setMode(modeOld);
  }    ////popUp(__LINE__);
  currentBox = currentBox->parent;                            ////popUp(__LINE__);
 }
}
void Game::releaseKey(int key) { //any special handling when certain keys are released
 if (player){
   switch (key) {
  case VK_A:       if (ISKEYDOWN(VK_D)){player->moveRight();} else {player->stopX();} break;
  case VK_D:       if (ISKEYDOWN(VK_A)){player->moveLeft(); } else {player->stopX();} break;
  case VK_RBUTTON: player->fireR = false;                                             break;
  case VK_LBUTTON: player->fireL = false;                                             break;
  }
 }
 VECTOR_REMOVE(keysDown, key);
}
void Game::holdKey(int key) { //any special handling for keys that continue to be held down
 switch (key) {
 /*
 case VK_UP:
  screen->focusOn(NULL);
  screen->camera.y += 2;
  break;
 case VK_LEFT:
  screen->focusOn(NULL);
  screen->camera.x -= 2;
  break;
 case VK_DOWN:
  screen->focusOn(NULL);
  screen->camera.y -= 2;
  break;
 case VK_RIGHT:
  screen->focusOn(NULL);
  screen->camera.x += 2;
  break;
 */
 }
}
void Game::processInput() {
 for (unsigned i = 0; i < keysDown.size(); i++) { //handle keys that are still pressed from before
  holdKey(keysDown[i]);
 }
}
void Game::processMessages(UINT msg, WPARAM wParam, LPARAM lParam) {
 switch (msg) {
 case WM_SIZE:        screen->rescaleTo(LOWORD(lParam), HIWORD(lParam)); break;
 case WM_LBUTTONDOWN: pressKey(VK_LBUTTON);                              break;
 case WM_LBUTTONUP:   releaseKey(VK_LBUTTON);                            break;
 case WM_RBUTTONDOWN: pressKey(VK_RBUTTON);                              break;
 case WM_RBUTTONUP:   releaseKey(VK_RBUTTON);                            break;
 case WM_MOUSEMOVE:   cursorLoc = MAKEPOINTS(lParam); updateCursor();    break;
 case WM_SYSKEYDOWN:  sysKeyDown = true;                                 //NO BREAK
 case WM_KEYDOWN:     pressKey(wParam);                                  break;
 case WM_SYSKEYUP:    sysKeyDown = false;                                //NO BREAK
 case WM_KEYUP:       releaseKey(wParam);                                break;
 case WM_MOVE:        screen->getWindow();                               break;
 case WM_SETCURSOR:   if (LOWORD(lParam) == HTCLIENT) {if (!cursorHidden){hideCursor();}} else {if (cursorHidden){showCursor();}} break;
 }
}
void Game::makeItemScreen(bool cascade) {
 Script* script = new Script(player);
 if (cascade){
  script->append("OPTIONBOX \"\" CASCADE");
 } else {
  script->append("OPTIONBOX \"\"");
 }
 std::vector<Item*> inv = player->inventory;
 std::string line;
 for (unsigned k = 0; k < inv.size(); k++) {
  Item* item = inv[k];
  line = "OPTION \"" + item->name;
  if (item->currentUse.size()){line += " (" + item->currentUse + ")";}
  line += "\"\n";
  script->append(line);
  line = "OPTIONBOX \"" + item->description;
  if (item->canR || item->canL || item->canB){line += "__" + toStr(item->dam) + " damage";}
  if (!item->currentUse.compare(UNIT_RH)){
   line += " __Currently equipped in the right hand.";
  } else if (!item->currentUse.compare(UNIT_LH)){
   line += " __Currently equipped in the left hand.";
  } else if (!item->currentUse.compare(UNIT_BH)){
   line += " __Currently equipped in both hands.";
  } else if (!item->currentUse.compare(UNIT_ACC)){
   line += " __Currently equipped as an accessory.";
  }
  line += "\"";
  script->append(line);
  if (item->usesLeft){
   script->append("OPTION \"Use\": USE " + toStr((int)k) + ": MAKEITEMSCREEN");
  }
  if (item->currentUse.size()){
   script->append("OPTION \"Unequip\": UNEQUIP " + toStr((int)k) + ": MAKEITEMSCREEN");
  } else {
   if (item->canL){script->append("OPTION \"Equip (LH)\": LH "   + toStr((int)k) + ": MAKEITEMSCREEN");}
   if (item->canR){script->append("OPTION \"Equip (RH)\": RH "   + toStr((int)k) + ": MAKEITEMSCREEN");}
   if (item->canB){script->append("OPTION \"Equip (BH)\": BH "   + toStr((int)k) + ": MAKEITEMSCREEN");}
   if (item->canA){script->append("OPTION \"Equip (ACC)\": ACC " + toStr((int)k) + ": MAKEITEMSCREEN");}
  }
  script->append("OPTION \"Return\": MAKEITEMSCREEN");
  script->append("ENDOPTIONBOX");
 }
 script->append("OPTION Return");
 script->append("ENDOPTIONBOX");
 script->execFromStart();
}
void Game::makeStatScreen() {
 Script* script = new Script(player);
 script->append("OPTIONBOX \"\" CASCADE");
 script->append("OPTION \"ATK: " + toStr((int)(100 * player->atk)) + "%\"");
 script->append("\"The amount of damage done by each of your weapons.\" CASCADE");
 script->append("OPTION \"DEF: " + toStr((int)(100 * player->def)) + "%\"");
 script->append("\"The amount of damage you will take from attacks.\" CASCADE");
 script->append("\"(A smaller number is better for this one.)\"");
 script->append("OPTION \"HP: " + toStr(player->hp) + " / " + toStr(player->hpMax) + "\"");
 script->append("\"The amount of damage you can take before the game is over.\" CASCADE");
 script->append("OPTION \"Return\"");
 script->append("ENDOPTIONBOX");
 script->execFromStart();
}
void Game::hideCursor() {
 ShowCursor(false);
 cursorHidden = true;
 checkCursorVisible();
}
void Game::showCursor() {
 ShowCursor(true);
 cursorHidden = false;
 cursor->invisible = true;
}
void Game::updateCursor(){
 cursor->x = screen->xScreenToMap(cursorLoc.x);
 cursor->y = screen->yScreenToMap(cursorLoc.y);
}
void Game::checkCursorVisible(){
 if (player && player->bh.size() && cursorHidden){
  if (cursor->invisible){
   screen->pullMouseTo(player->x, player->y);
   cursor->invisible = false;
  }
 } else {
  cursor->invisible = true;
 }
}

Game* Game::engine = NULL;

