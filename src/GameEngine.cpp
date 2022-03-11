GameEngine::GameEngine(HWND hwndNew){
 savePath = folder + "saves\\1";
 mode = modeInit;
 modeOld = modeInit;
 hwnd = hwndNew;
 srand(time(NULL));
 //mouse = new Mouse(hwnd);
 actionMode=actionStandby;
 //screen = new GameScreen(hwnd);
 //dialogActive=NULL;
 //dialogNew=NULL;
 //map = new Map(screen,&mode,&dialogNew);
 //dialogActive=NULL;
 //inventory.clear();
 //titleMenu();
}
int GameEngine::run(){
 #if START_FULL
 //screen->fullScreen(true);
 #endif
 MSG Msg;
 clock_t frameStart = clock();
 droppedFrames=0;
 while (Msg.message!=WM_QUIT) {
  if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)){
   TranslateMessage(&Msg);
   DispatchMessage(&Msg);
  }
  if(mode==modePaused){
   frameStart=clock();
  } else if (frameStart + FRAMELENGTHCLOCKS <= clock()){
   //processInput();
   while (frameStart + FRAMELENGTHCLOCKS <= clock()) {
    //map->advance();
	/*
    if(dialogNew){
     openBox(dialogNew);
     dialogNew=NULL;
    }
	*/
    frameStart += FRAMELENGTHCLOCKS;
    droppedFrames++;
   }
   droppedFrames--;
   //screen->draw();
   //screen->update();  
  }
 }
 return Msg.wParam;
}
void GameEngine::processMessages(UINT msg, WPARAM wParam, LPARAM lParam){
 /*
 switch(msg) {
  case WM_SIZE:        {screen->rescaleTo(LOWORD(lParam),HIWORD(lParam)); break;}
  case WM_LBUTTONDOWN: {mouse->newL = true;                               break;}
  case WM_LBUTTONUP:   {mouse->newL = false;                              break;}
  case WM_RBUTTONDOWN: {mouse->newR = true;                               break;}
  case WM_RBUTTONUP:   {mouse->newR = false;                              break;}
  case WM_MOUSEMOVE:   {mouse->newPosition = MAKEPOINTS(lParam);          break;}
  case WM_KEYDOWN:     {keyDown(wParam);                                  break;}
  case WM_KEYUP:       {keyUp(wParam);                                    break;}
  case WM_SYSKEYDOWN:  {keyDown(wParam);                                  break;}
  case WM_SYSKEYUP:    {keyUp(wParam);                                    break;}
  case WM_MOVE:        {screen->getWindow();                              break;}
  case WM_SETCURSOR:   {
   switch (LOWORD(lParam)){
   case HTCLIENT:
    if (!cursorHidden){
     hideCursor();
    }
    break;
   default:
    if (cursorHidden){
     showCursor();
    }
    break;
   }
  }
 }
 */
}
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
 /*
inline void GameEngine::processInput(){
 if(player){
  if((mode!=modeOver)&&(player->dead)){
   setMode(modeOver);
   return;
  } 
 }
 setCursorFromMouse();
 if((dialogActive)&&(dialogActive->toDelete)){closeDialog();}
 switch (mode){
 case modeActive: 
  for (unsigned i=0;i<keysPressed.size();i++){
   switch (keysPressed[i]){ //key hold handling
   case VK_W:
    if (!isKeyPressed(VK_S)){player->moveBack();} else {player->yMove=0;}
    break; 
   case VK_A:
    if (!isKeyPressed(VK_D)){player->moveLeft();} else {player->xMove=0;}
    break; 
   case VK_S:
    if (!isKeyPressed(VK_W)){player->moveFront();} else {player->yMove=0;}
    break; 
   case VK_D:
    if (!isKeyPressed(VK_A)){player->moveRight();} else {player->xMove=0;}
    break; 
#ifdef MOVE_CURSOR_WITH_ARROW_KEYS
   case VK_UP:
    if (!isKeyPressed(VK_DOWN)){
     //map->cursor->y+=CURSOR_SENSITIVITY;
     mouse->newPosition.y-=CURSOR_SENSITIVITY;
     setCursorFromMouse();
     screen->setMouseFromCursor(map->cursor);
    }
    break; 
   case VK_LEFT:
    if (!isKeyPressed(VK_RIGHT)){
     //map->cursor->x-=CURSOR_SENSITIVITY;
     mouse->newPosition.x-=CURSOR_SENSITIVITY;
     setCursorFromMouse();
     screen->setMouseFromCursor(map->cursor);
    }
    break; 
   case VK_DOWN:
    if (!isKeyPressed(VK_UP)){
     //map->cursor->y-=CURSOR_SENSITIVITY;
     mouse->newPosition.y+=CURSOR_SENSITIVITY;
     setCursorFromMouse();
     screen->setMouseFromCursor(map->cursor);
    }
    break; 
   case VK_RIGHT:
    if (!isKeyPressed(VK_LEFT)){
     //map->cursor->x+=CURSOR_SENSITIVITY;
     mouse->newPosition.x+=CURSOR_SENSITIVITY;
     setCursorFromMouse();
     screen->setMouseFromCursor(map->cursor);
    }
    break; 
#endif    
   }
  }
  if (mouse->oldL != mouse->newL){
   if (mouse->newL){ 
    //left button has just been pressed. do click handling
    setActionMode(actionAttack);
   } else { 
    //left button has just been released. do unclick handling
    setActionMode(actionStandby);
   }
   mouse->oldL = mouse->newL;
  } else if (mouse->oldL) { 
   //do left hold handling
  }
  if (mouse->oldR != mouse->newR){
   if (mouse->newR){ 
    //right button has just been pressed. do click handling
    setActionMode(actionDefend);
   } else { 
    //right button has just been released. do unclick handling   
    setActionMode(actionStandby);
   }
   mouse->oldR = mouse->newR;
  } else if (mouse->oldR){ 
   //do right hold handling
  }
  switch(actionMode){
  case actionAttack:
   {
    Entity* bullet = player->fireWeaponAt(map->cursor);
    if (bullet!=NULL){map->addEntity(bullet);}  
   } 
  }
 } 
}
void GameEngine::titleMenu(){
 player=NULL;
 map->load("title");
 TextBox* instructions=new TextBox(INSTRUCTIONS_MSG);
 instructions->xDisp=400;
 instructions->yDisp=450;
 map->screen->addObject((DrawObject*)instructions);
 DrawObject* logo = new DrawObject();
 logo->loadSprite("logo");
 openMenu("",menuTitle);
 mode=modeMenu; 
}
void GameEngine::newGame(){
 if(dialogActive){dialogActive->toDelete=true;}
 dialogActive=NULL;
 dialogNew=NULL;
 player = new Unit(facPlayer);
 map->setControl(player);//needs to happen before load
 map->load("castle");
 cursorHidden = true;
 setMode(modeActive);
}
void GameEngine::setCursorFromMouse(){
 map->setCursor(mouse->newPosition.x, mouse->newPosition.y);
 mouse->oldPosition.x = mouse->newPosition.x;
 mouse->oldPosition.y = mouse->newPosition.y;   
}
bool GameEngine::isKeyPressed(int key){
 return (std::find(keysPressed.begin(), keysPressed.end(), key) != keysPressed.end());
}
void GameEngine::keyDown(int key){
 //key press handling
 if (!isKeyPressed(key)){
  keysPressed.push_back(key); 
  if (isKeyPressed(VK_MENU)){ 
   switch (key){
   case VK_F4:
    PostQuitMessage(0);
    break;
   case VK_RETURN:
    screen->toggleFull();
    screen->setMouseFromCursor(map->cursor);
    break;   
   }
   return;
  } 
  if(key==VK_G){popUp(debugMsg);}
  switch(mode){
  case modePaused:
   if(key==VK_P){
    closeDialog();
   }
   break;  
  case modeActive:
   switch(key){
   case VK_W:
    player->setFacing(back);
    break; 
   case VK_A:
    player->setFacing(left);
    break; 
   case VK_S:
    player->setFacing(front);
    break; 
   case VK_D:
    player->setFacing(right);
    break;    
   case VK_ESCAPE:
    setMode(modeMenu);
    break;
   case VK_SPACE:
    interact();
    break;
   case VK_P:
    setMode(modePaused);
    break;    
   } 
   break;
  case modeOver: 
   closeDialog();
   titleMenu();
   break;
  case modeDialog:
  case modeMenu:
   {
    MenuBox* mb=dynamic_cast<MenuBox*>(dialogActive);
    if(mb){
     switch(key){
     case VK_ESCAPE:
      if (mb->menuID==menuTitle){
       openMenu(CONFIRM_QUIT_MSG,menuConfirmQuit);
      }else if (mb->escapable){
       closeDialog();
      }
      break;
     case VK_W:
     case VK_UP:
      mb->previousOption();
      break; 
     case VK_A:
     case VK_LEFT:
      mb->previousOption();
      break; 
     case VK_S:
     case VK_DOWN:
      mb->nextOption();
      break; 
     case VK_D:
     case VK_RIGHT:
      mb->nextOption();
      break; 
     case VK_RETURN:
     case VK_SPACE:
      MenuSelection* selection=mb->select();
      switch (mb->menuID){   
      case menuNull:
       {
        int x=mb->xDisp+(mb->widthDisp/2);
        int y=mb->yDisp+(mb->depthDisp/2);        
        closeDialog();
        if(selection->next){
         selection->next->centerOn(x,y);
         openBox(selection->next);
        }
        break;      
       }
      case menuConfirmQuit:
       closeDialog();
       if(selection->text==CONFIRM_YES){
        PostQuitMessage(0);  
       }
       break;
      case menuPickupConsumable:
       if(selection->text==CONFIRM_YES){
        if(player){player->use(currentItem);}
       } else {
        inventory.push_back(currentItem);
        if(currentItem->owner){((Entity*)currentItem->owner)->toDelete=true;}
       }
       closeDialog();
       break;
      case menuCannotPickupConsumable:
       if(selection->text==CONFIRM_YES){
        if(player){player->use(currentItem);}
        if(currentItem->owner){((Entity*)currentItem->owner)->toDelete=true;}
       } else {
        currentItem=NULL;
       }
       closeDialog();
       break;
      case menuMain: 
       if(selection->text==INVENTORY_MSG){
        openMenu(INVENTORY_MSG,menuInventory);
       }else if(selection->text==STATUS_MSG){
        openMenu(STATUS_MSG,menuStatus);
       }else if(selection->text==QUIT_MSG){
        openMenu(CONFIRM_QUIT_MSG,menuConfirmQuit);
       } else { 
        closeDialog();
       }
       break;
      case menuInventory:
       if((selection->text==RETURN_MSG)||(inventory.size()==0)){
        closeDialog();
       } else {
        currentItem=inventory[mb->currentOption];
        openMenu(currentItem->name,menuItem);
       }
       break;
      case menuSave:
       if(selection->text==CONFIRM_YES){
        saveGame();
        closeDialog();
        openDialog("Game saved successfully.");
       } else {
        closeDialog();
       } 
       break;
      case menuStatus:
       closeDialog();
       break;       
      case menuConfirmDrop:
       closeDialog();
       if(selection->text==CONFIRM_YES){
        inventory.erase(std::remove(inventory.begin(), inventory.end(), currentItem), inventory.end());
        closeDialog();
        closeDialog();//have to close and reopen inventory to refresh
        openMenu(INVENTORY_MSG,menuInventory);
       }
       break;
      case menuConfirmEquip:
       if(selection->text==CONFIRM_YES){
        if(player){player->use(currentItem);}
       }
       closeDialog();
       break;
      case menuItem:
       if(selection->text==RETURN_MSG){
        closeDialog();
       } else if(selection->text==DROP_MSG){
        if (currentItem->droppable){
         openMenu(CONFIRM_DROP_MSG,menuConfirmDrop);
        } else {
         openDialog(CANNOT_DROP_MSG);
        } 
       }else if(selection->text==EXAMINE_MSG){
        openDialog(currentItem->description);
       }else if(selection->text==USE_MSG){
        if ((currentItem==player->equippedWeapon)||(currentItem==player->equippedArmor)){
         openDialog(ALREADY_EQUIPPED_MSG);
        } else {
         if(player){player->use(currentItem);}
         closeAllDialogs();
         if(currentItem->type==itemConsumable){
          inventory.erase(std::remove(inventory.begin(), inventory.end(), currentItem), inventory.end());
         }
         if(currentItem->onUse!="NULL"){
          openDialog(currentItem->onUse);
         }else{
          openDialog("You used the " + currentItem->name);
         }
        }
       }
       break;
      case menuTitle:
       if (selection->text==NEWGAME_MSG){
        newGame();
       }else if(selection->text==CONTINUE_MSG){
        loadGame();
       }else if(selection->text==QUIT_MSG){
        openMenu(CONFIRM_QUIT_MSG,menuConfirmQuit);
       }
       break;   
      } 
      break; 
     } 
    } else {//must be a plain text box
     switch(key){
     case VK_ESCAPE:
     case VK_RETURN:
     case VK_SPACE:
      closeDialog(); 
     }
    }
   }
  } 
 }
}
void GameEngine::keyUp(int key){
 //key unpress handling
 switch(mode){
 case modeActive: 
  switch (key){
  case VK_W:
  case VK_UP:
   player->yMove=0;
   break; 
  case VK_A:
  case VK_LEFT:
   player->xMove=0;
   break; 
  case VK_S:
  case VK_DOWN:
   player->yMove=0;
   break; 
  case VK_D:
  case VK_RIGHT:
   player->xMove=0;
   break;
  }
 }
 if (isKeyPressed(key)){
  keysPressed.erase(std::remove(keysPressed.begin(), keysPressed.end(), key), keysPressed.end());
 }
}

void GameEngine::openMenu(std::string prompt,MenuType menuID){
 MenuBox* active=active=new MenuBox(prompt);
 active->menuID=menuID;
 switch(menuID){
 case menuPickupConsumable:
  active->addOption(CONFIRM_YES);
  active->addOption(CONFIRM_NO);  
  break;
 case menuCannotPickupConsumable:
  active->addOption(CONFIRM_YES);
  active->addOption(CONFIRM_NO);  
  break;  
 case menuSave:
  active->addOption(CONFIRM_YES);
  active->addOption(CONFIRM_NO);  
  break;  
 case menuConfirmQuit:
  active->setPrompt(CONFIRM_QUIT_MSG);
  active->addOption(CONFIRM_YES);
  active->addOption(CONFIRM_NO);  
  active->forceFinish();
  break; 
 case menuConfirmDrop:
  active->setPrompt(CONFIRM_DROP_MSG);
  active->addOption(CONFIRM_YES);
  active->addOption(CONFIRM_NO);  
  break; 
 case menuMain:
  active->setPrompt("");
  active->addOption(INVENTORY_MSG);
  active->addOption(STATUS_MSG);
  active->addOption(RETURN_MSG);   
  active->addOption(QUIT_MSG); 
  active->escapable=true;  
  active->forceFinish();
  break;
 case menuInventory:
  active->setPrompt("");
  for(int k=0;k<inventory.size();k++){
   if(player&&((player->equippedWeapon==inventory[k])||(player->equippedArmor==inventory[k]))){
    active->addOption(inventory[k]->name + " (E)");
   } else {
    active->addOption(inventory[k]->name);
   }
  } 
  active->addOption(RETURN_MSG); 
  active->escapable=true;
  active->forceFinish();
  break;
 case menuItem:
  active->addOption(USE_MSG);
  active->addOption(EXAMINE_MSG);  
  active->addOption(DROP_MSG);
  active->addOption(RETURN_MSG);
  active->escapable=true;
  active->forceFinish();
  break;  
 case menuConfirmEquip:
  active->addOption(CONFIRM_YES);
  active->addOption(CONFIRM_NO);  
  active->escapable=true;
  break;
 case menuStatus:
  prompt="STATUS\n";
  if(player){
   prompt=prompt+"HP: "+toStr(player->hp)+"\\"+toStr(player->hpMax)+"\n";
   prompt=prompt+"Defense: "+toStr((int)player->defense)+"\n";
   prompt=prompt+"Agility: "+toStr((int)player->agility)+"\n";  
   if(player->weapon){
    prompt=prompt+"Attack: "+toStr((int)(player->weapon->attack))+"\n";  
    prompt=prompt+"Speed: "+toStr((int)10000/player->weapon->fireRate)+"\n";  
    prompt=prompt+"Range: "+toStr((int)player->weapon->fireRange/10)+"\n";  
   }
  }
  active->setPrompt(prompt);
  active->addOption(RETURN_MSG);
  active->escapable=true;
  active->forceFinish();
  break; 
 case menuTitle:
  active->addOption(NEWGAME_MSG);
  if (fileExists(savePath)){
   active->addOption(CONTINUE_MSG);  
   active->currentOption=1;
  }
  active->addOption(QUIT_MSG);
  active->forceFinish();
  break; 
 default:
  break; 
 }
 map->screen->addObject((DrawObject*)active);  
 map->cursor->invisible=true;
 active->setParent(dialogActive);
 dialogActive=active;
 if(mode==modeActive){setMode(modeDialog);}  
}
void GameEngine::openBox(TextBox* activeNew){
 activeNew->setParent(dialogActive);
 map->screen->addObject((DrawObject*)activeNew);
 map->cursor->invisible=true; 
 dialogActive=activeNew;
 if(mode==modeActive){setMode(modeDialog);}
 if(dialogActive->textFull.length()==0){closeDialog();}
}
void GameEngine::openDialog(std::string text,bool enterDialogMode){
 TextBox* active=new TextBox(text);
 map->screen->addObject((DrawObject*)active);
 map->cursor->invisible=true; 
 active->setParent(dialogActive);
 dialogActive=active;
 if(enterDialogMode){
  dialogActive->waitForAction=true;
  if(mode==modeActive){setMode(modeDialog);}
 }
}
void GameEngine::closeDialog(){
 TextBox* toClose=dialogActive;
 screen->delObject((DrawObject*)toClose);
 dialogActive=toClose->parentBox;
 if(toClose->loot){
  currentItem=toClose->loot;
  if(inventory.size()<MAX_INVENTORY){
   inventory.push_back(currentItem); 
  }else{
   openDialog(CANNOT_PICKUP_MSG);
   return;
  }
 }
 if(toClose->childBox){
  toClose->childBox->centerOn(toClose);
  openBox(toClose->childBox);
 }
 for(int k=0;k<toClose->events.size();k++){toClose->events[k]->fire();}
 if(!dialogActive){setMode(modeOld);}
}
void GameEngine::closeAllDialogs(){
 while (dialogActive){
  closeDialog();
 }
}
void GameEngine::setMode(GameMode modeNew){
 if(mode==modeNew){return;}
 switch(mode){//first, leave the old mode
 case modeActive:
  if(player){player->stop();}
  break;
 case modePaused:
  Audio::resumeBGM();
  break; 
 }
 modeOld=mode;
 mode=modeNew;
 switch(mode){//then, set up the new mode
 case modePaused:
  Audio::pauseBGM();
  openDialog(PAUSED_MSG);
  map->cursor->invisible=true; 
  dialogActive->forceFinish();
  screen->draw();//have to do this manually, since it will not happen during pause
  screen->update(); 
  break;
 case modeMenu:
  openMenu(MENU_MSG,menuMain);
  //no break is intentional
 case modeDialog:
  map->cursor->invisible=true;
  break;
 case modeActive:
  map->checkCursorVisible();
  break;
 case modeOver:
  openDialog(GAMEOVER_MSG);
  break;
 }
}
void GameEngine::hideCursor(){
 ShowCursor(false);
 cursorHidden=true;
 map->checkCursorVisible();
}
void GameEngine::showCursor(){
 ShowCursor(true);
 cursorHidden=false;
 if(map->cursor){
  map->cursor->invisible=true;
 }
}
void GameEngine::interact(){
 if(!player){return;}
 player->stop();
 Entity* inFront=new Entity();
 inFront->height=player->height;
 inFront->width=player->width;
 inFront->depth=player->depth; 
 inFront->x=player->x;
 inFront->y=player->y;
 inFront->z=player->z; 
 switch(player->facing){
 case back:
  inFront->y-=inFront->depth*2;
  break;
 case front:
  inFront->y+=inFront->depth*2;
  break;
 case left:
  inFront->x-=inFront->width*2;
  break;
 case right:
  inFront->x+=inFront->width*2;
  break;  
 }
 for(int k=0;k<map->entities.size();k++){
  if(map->entities[k]!=player){
   if(inFront->overlapsWithNow(map->entities[k])){
    void* interaction;
    switch(map->entities[k]->interact(player,&interaction)){
    case interactionNull:
     break;
    case interactionLoot:
     {
      Item* item=static_cast<Item*>(interaction);
      pickUp(item);
      break;    
     }
    case interactionDialog:
     openBox(static_cast<TextBox*>(interaction));
     break;    
    }
   }
  }
 }
}
void GameEngine::pickUp(Item* item){
 currentItem=item;
 if(inventory.size()<MAX_INVENTORY){
  inventory.push_back(currentItem);
  Entity* owner = (Entity*)item->owner;
  if (owner){
   owner->toDelete=true;
   Plot::set(PLOT_DESTROYED(owner));
  }
  switch(currentItem->type){
  case itemArmor:
  case itemWeapon:
   openMenu(CONFIRM_EQUIP_MSG,menuConfirmEquip);
   break;
  case itemConsumable:
   openMenu(CONFIRM_CONSUME_MSG,menuPickupConsumable);
   break;  
  default: 
   openDialog(PICKUP_MSG);
  }
 } else {
  if(currentItem->type==itemConsumable){
   openMenu(CANNOT_PICKUP_CONSUMABLE_MSG,menuCannotPickupConsumable);
  } else {
   openDialog(CANNOT_PICKUP_MSG);
  }
 }
}
void GameEngine::saveGame(){
 std::remove(savePath.c_str());
 std::ofstream saveFile(savePath.c_str());
 player->saveTo(&saveFile);
 saveFile << "inventory:\n";
 for (int k=0;k<inventory.size();k++){
  saveFile << inventory[k]->name + "\n";
 }
 saveFile << "\n";
 saveFile << "equipped:\n";
 if(player->equippedWeapon){saveFile << player->equippedWeapon->name + "\n";}
 if(player->equippedArmor){saveFile << player->equippedArmor->name + "\n";}
 saveFile << "\n";
 Plot::saveTo(&saveFile);
 saveFile << "map:\n";
 saveFile << map->name;
 saveFile.close();
}
void GameEngine::loadGame(){
 if(dialogActive){dialogActive->toDelete=true;}
 dialogActive=NULL;
 std::ifstream saveFile(savePath.c_str());
 player=Unit::loadFrom(&saveFile);
 inventory.clear();
 std::string line;
 getline(saveFile,line);
 if(line!="inventory:"){
  popUp("error: invalid save data");
  return;
 }
 while ((getline(saveFile,line))&&(line.length())){
  inventory.push_back(new Item(line));
 }
 getline(saveFile,line);
 if(line!="equipped:"){
  popUp("error: invalid save data");
  return;
 }
 getline(saveFile,line);
 if (line.length()){
  for(int k=0;k<inventory.size();k++){
   if (inventory[k]->name==line){
    if(player){player->use(inventory[k]);}
    break;
   }
  } 
  getline(saveFile,line);
  if (line.length()){
   for(int k=0;k<inventory.size();k++){
    if (inventory[k]->name==line){
     if(player){player->use(inventory[k]);}
     break;
    }
   } 
   getline(saveFile,line);
  }
 }
 cursorHidden = true;
 setMode(modeActive);
 Plot::loadFrom(&saveFile);
 map->setControl(player);//needs to happen before load
 getline(saveFile,line);
 if(line!="map:"){
  popUp("error: invalid save data");
  return;
 }
 getline(saveFile,line);
 map->load(line);
 saveFile.close(); 
 map->checkCursorVisible();
}
void GameEngine::setActionMode(ActionMode actionNew){
 if(actionNew==actionMode){return;}
 switch(actionMode){
 case actionStandby:
  break;
 case actionAttack:
  unAttack();
  break;
 case actionDefend:
  unDefend();
  break;  
 }
 actionMode=actionNew;
 switch(actionMode){
 case actionStandby:
  if (map->cursor){map->cursor->sprite->greenScreen=CURSOR_COLOR_STANDBY;}
  break;
 case actionAttack:
  if (map->cursor){map->cursor->sprite->greenScreen=CURSOR_COLOR_ATTACK;}
  enAttack();
  break;
 case actionDefend:
  if (map->cursor){map->cursor->sprite->greenScreen=CURSOR_COLOR_DEFEND;}
  enDefend();
  break;  
 }
}
void GameEngine::enAttack(){
 
}
void GameEngine::enDefend(){
 if(player){
  player->defending=true;
  if(player->armor){
   switch(player->armor->type){
   case armorShield:
    player->stop();
    player->stationary=true;
    if(map->cursor){
     map->cursor->blocksBullets=true;
     map->cursor->blocker=true;
    }
   }
  }
 }
}
void GameEngine::unAttack(){
 
}
void GameEngine::unDefend(){
 if(player){
  player->defending=false;
  if(player->armor){
   switch(player->armor->type){
   case armorShield:
    player->stationary=false;
    if(map->cursor){
     map->cursor->blocksBullets=false;
     map->cursor->blocker=false;
    }
   }
  }
 } 
}
*/