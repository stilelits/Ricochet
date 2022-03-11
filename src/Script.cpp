/*
 * Script.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: tr_dawson
 */

#include "Script.h"
#include "OptionBox.h"
#include "Game.h"

int Script::switchVal(const std::string& str){
 static std::vector<std::string> MacStrs;
 if (!MacStrs.size()){
#define PUSHMAC(str)  MacStrs.push_back(str)
#define x_SCRIPT            0
#define x_SCRIPT_STR        \
       "x"
PUSHMAC(x_SCRIPT_STR);
#define y_SCRIPT            1
#define y_SCRIPT_STR        \
       "y"
PUSHMAC(y_SCRIPT_STR);
#define z_SCRIPT            2
#define z_SCRIPT_STR        \
       "z"
PUSHMAC(z_SCRIPT_STR);
#define w_SCRIPT            3
#define w_SCRIPT_STR        \
       "w"
PUSHMAC(w_SCRIPT_STR);
#define h_SCRIPT            4
#define h_SCRIPT_STR        \
       "h"
PUSHMAC(h_SCRIPT_STR);
#define d_SCRIPT            5
#define d_SCRIPT_STR        \
       "d"
PUSHMAC(d_SCRIPT_STR);
#define destZ_SCRIPT        6
#define destZ_SCRIPT_STR    \
       "destZ"
PUSHMAC(destZ_SCRIPT_STR);
#define destY_SCRIPT        7
#define destY_SCRIPT_STR    \
       "destY"
PUSHMAC(destY_SCRIPT_STR);
#define destX_SCRIPT        8
#define destX_SCRIPT_STR    \
       "destX"
PUSHMAC(destX_SCRIPT_STR);
#define dest_SCRIPT         9
#define dest_SCRIPT_STR     \
       "dest"
PUSHMAC(dest_SCRIPT_STR);
#define immobile_SCRIPT     10
#define immobile_SCRIPT_STR \
       "immobile"
PUSHMAC(immobile_SCRIPT_STR);
#define bounciness_SCRIPT          11
#define bounciness_SCRIPT_STR       \
       "bounciness"
PUSHMAC(bounciness_SCRIPT_STR);
#define color_SCRIPT         12
#define color_SCRIPT_STR       \
       "color"
PUSHMAC(color_SCRIPT_STR);
#define uid_SCRIPT           13
#define uid_SCRIPT_STR       \
       "uid"
PUSHMAC(uid_SCRIPT_STR);
#define    BGM_SCRIPT         14
#define    BGM_SCRIPT_STR       \
       "BGM"
PUSHMAC(BGM_SCRIPT_STR);
#define name_SCRIPT          15
#define name_SCRIPT_STR       \
       "name"
PUSHMAC(name_SCRIPT_STR);
#define TURNON_SCRIPT         16
#define TURNON_SCRIPT_STR     \
       "TURNON"
PUSHMAC(TURNON_SCRIPT_STR);
#define sprite_SCRIPT         17
#define sprite_SCRIPT_STR       \
       "sprite"
PUSHMAC(sprite_SCRIPT_STR);
#define  noMask_SCRIPT        18
#define  noMask_SCRIPT_STR       \
       "noMask"
PUSHMAC(noMask_SCRIPT_STR);
#define CLOSE_SCRIPT       19
#define CLOSE_SCRIPT_STR       \
       "CLOSE"
PUSHMAC(CLOSE_SCRIPT_STR);
#define TURNOFF_SCRIPT       20
#define TURNOFF_SCRIPT_STR       \
       "TURNOFF"
PUSHMAC(TURNOFF_SCRIPT_STR);
#define IF_SCRIPT          21
#define IF_SCRIPT_STR       \
       "IF"
PUSHMAC(IF_SCRIPT_STR);
#define ELSE_SCRIPT         22
#define ELSE_SCRIPT_STR       \
       "ELSE"
PUSHMAC(ELSE_SCRIPT_STR);
#define ELSEIF_SCRIPT         23
#define ELSEIF_SCRIPT_STR       \
       "ELSEIF"
PUSHMAC(ELSEIF_SCRIPT_STR);
#define ENDIF_SCRIPT          24
#define ENDIF_SCRIPT_STR       \
       "ENDIF"
PUSHMAC(ENDIF_SCRIPT_STR);
#define NOFADE_SCRIPT        25
#define NOFADE_SCRIPT_STR       \
       "NOFADE"
PUSHMAC(NOFADE_SCRIPT_STR);
#define QUIT_SCRIPT         26
#define QUIT_SCRIPT_STR       \
       "QUIT"
PUSHMAC(QUIT_SCRIPT_STR);
#define OPTION_SCRIPT        27
#define OPTION_SCRIPT_STR       \
       "OPTION"
PUSHMAC(OPTION_SCRIPT_STR);
#define OPTIONBOX_SCRIPT       28
#define OPTIONBOX_SCRIPT_STR       \
       "OPTIONBOX"
PUSHMAC(OPTIONBOX_SCRIPT_STR);
#define TEXTBOX_SCRIPT          29
#define TEXTBOX_SCRIPT_STR       \
       "TEXTBOX"
PUSHMAC(TEXTBOX_SCRIPT_STR);
#define SET_SCRIPT          30
#define SET_SCRIPT_STR       \
       "SET"
PUSHMAC(SET_SCRIPT_STR);
#define GIVEITEM_SCRIPT         31
#define GIVEITEM_SCRIPT_STR       \
       "GIVEITEM"
PUSHMAC(GIVEITEM_SCRIPT_STR);
#define TAKEITEM_SCRIPT         32
#define TAKEITEM_SCRIPT_STR       \
       "TAKEITEM"
PUSHMAC(TAKEITEM_SCRIPT_STR);
#define MODELESS_SCRIPT          33
#define MODELESS_SCRIPT_STR       \
       "MODELESS"
PUSHMAC(MODELESS_SCRIPT_STR);
#define MAKEITEMSCREEN_SCRIPT        34
#define MAKEITEMSCREEN_SCRIPT_STR       \
       "MAKEITEMSCREEN"
PUSHMAC(MAKEITEMSCREEN_SCRIPT_STR);
#define MAKESTATSCREEN_SCRIPT         35
#define MAKESTATSCREEN_SCRIPT_STR       \
       "MAKESTATSCREEN"
PUSHMAC(MAKESTATSCREEN_SCRIPT_STR);
#define MAKEQUITSCREEN_SCRIPT         36
#define MAKEQUITSCREEN_SCRIPT_STR       \
       "MAKEQUITSCREEN"
PUSHMAC(MAKEQUITSCREEN_SCRIPT_STR);
#define WHEN_SCRIPT          37
#define WHEN_SCRIPT_STR       \
       "WHEN"
PUSHMAC(WHEN_SCRIPT_STR);
#define ENDWHEN_SCRIPT         38
#define ENDWHEN_SCRIPT_STR       \
       "ENDWHEN"
PUSHMAC(ENDWHEN_SCRIPT_STR);
#define USE_SCRIPT           39
#define USE_SCRIPT_STR       \
       "USE"
PUSHMAC(USE_SCRIPT_STR);
#define RH_SCRIPT          40
#define RH_SCRIPT_STR       \
       "RH"
PUSHMAC(RH_SCRIPT_STR);
#define BH_SCRIPT          41
#define BH_SCRIPT_STR       \
       "BH"
PUSHMAC(BH_SCRIPT_STR);
#define LH_SCRIPT          42
#define LH_SCRIPT_STR       \
       "LH"
PUSHMAC(LH_SCRIPT_STR);
#define ACC_SCRIPT        43
#define ACC_SCRIPT_STR       \
       "ACC"
PUSHMAC(ACC_SCRIPT_STR);
#define UNEQUIP_SCRIPT          44
#define UNEQUIP_SCRIPT_STR       \
       "UNEQUIP"
PUSHMAC(UNEQUIP_SCRIPT_STR);
#define CASCADE_SCRIPT         45
#define CASCADE_SCRIPT_STR       \
       "CASCADE"
PUSHMAC(CASCADE_SCRIPT_STR);
#define ENDOPTIONBOX_SCRIPT        46
#define ENDOPTIONBOX_SCRIPT_STR       \
       "ENDOPTIONBOX"
PUSHMAC(ENDOPTIONBOX_SCRIPT_STR);
#define OPEN_SCRIPT           47
#define OPEN_SCRIPT_STR       \
       "OPEN"
PUSHMAC(OPEN_SCRIPT_STR);
#define NEWGAME_SCRIPT           48
#define NEWGAME_SCRIPT_STR       \
       "NEWGAME"
PUSHMAC(NEWGAME_SCRIPT_STR);
#define WALL_SCRIPT        49
#define WALL_SCRIPT_STR    \
       "WALL"
PUSHMAC(WALL_SCRIPT_STR);
#define FLOOR_SCRIPT        50
#define FLOOR_SCRIPT_STR    \
       "FLOOR"
PUSHMAC(FLOOR_SCRIPT_STR);
#define ENDSCRIPT_SCRIPT        51
#define ENDSCRIPT_SCRIPT_STR    \
       "ENDSCRIPT"
PUSHMAC(ENDSCRIPT_SCRIPT_STR);
#define DOOR_SCRIPT        52
#define DOOR_SCRIPT_STR    \
       "DOOR"
PUSHMAC(DOOR_SCRIPT_STR);
#define ENEMY_SCRIPT        53
#define ENEMY_SCRIPT_STR    \
       "ENEMY"
PUSHMAC(ENEMY_SCRIPT_STR);
#define BLOCK_SCRIPT        54
#define BLOCK_SCRIPT_STR    \
       "BLOCK"
PUSHMAC(BLOCK_SCRIPT_STR);
#define END_SCRIPT        55
#define END_SCRIPT_STR    \
       "END"
PUSHMAC(END_SCRIPT_STR);
#define WALLPAPER_SCRIPT        56
#define WALLPAPER_SCRIPT_STR    \
       "WALLPAPER"
PUSHMAC(WALLPAPER_SCRIPT_STR);
#define TOP_SCRIPT        57
#define TOP_SCRIPT_STR    \
       "TOP"
PUSHMAC(TOP_SCRIPT_STR);
#define RIGHT_SCRIPT        58
#define RIGHT_SCRIPT_STR    \
       "RIGHT"
PUSHMAC(RIGHT_SCRIPT_STR);
#define LEFT_SCRIPT        59
#define LEFT_SCRIPT_STR    \
       "LEFT"
PUSHMAC(LEFT_SCRIPT_STR);
#define BOTTOM_SCRIPT        60
#define BOTTOM_SCRIPT_STR    \
       "BOTTOM"
PUSHMAC(BOTTOM_SCRIPT_STR);
#define SWITCH_SCRIPT        61
#define SWITCH_SCRIPT_STR    \
       "SWITCH"
PUSHMAC(SWITCH_SCRIPT_STR);
#define NPC_SCRIPT        62
#define NPC_SCRIPT_STR    \
       "NPC"
PUSHMAC(NPC_SCRIPT_STR);
#define ITEM_SCRIPT        63
#define ITEM_SCRIPT_STR    \
       "ITEM"
PUSHMAC(ITEM_SCRIPT_STR);
#define SCRIPT_SCRIPT        64
#define SCRIPT_SCRIPT_STR    \
       "SCRIPT"
PUSHMAC(SCRIPT_SCRIPT_STR);
#define spriteSpeed_SCRIPT        65
#define spriteSpeed_SCRIPT_STR    \
       "spriteSpeed"
PUSHMAC(spriteSpeed_SCRIPT_STR);
#define PATROL_SCRIPT        66
#define PATROL_SCRIPT_STR    \
       "PATROL"
PUSHMAC(PATROL_SCRIPT_STR);
#define UP_SCRIPT        67
#define UP_SCRIPT_STR    \
       "UP"
PUSHMAC(UP_SCRIPT_STR);
#define DOWN_SCRIPT        68
#define DOWN_SCRIPT_STR    \
       "DOWN"
PUSHMAC(DOWN_SCRIPT_STR);
#define weightless_SCRIPT        69
#define weightless_SCRIPT_STR    \
       "weightless"
PUSHMAC(weightless_SCRIPT_STR);
#define hurtOnTouch_SCRIPT        70
#define hurtOnTouch_SCRIPT_STR    \
       "hurtOnTouch"
PUSHMAC(hurtOnTouch_SCRIPT_STR);
#define maxDx_SCRIPT        71
#define maxDx_SCRIPT_STR    \
       "maxDx"
PUSHMAC(maxDx_SCRIPT_STR);
#define maxDy_SCRIPT        72
#define maxDy_SCRIPT_STR    \
       "maxDy"
PUSHMAC(maxDy_SCRIPT_STR);
#define CEILING_SCRIPT        73
#define CEILING_SCRIPT_STR    \
       "CEILING"
PUSHMAC(CEILING_SCRIPT_STR);
#define scriptFile_SCRIPT        74
#define scriptFile_SCRIPT_STR    \
       "scriptFile"
PUSHMAC(scriptFile_SCRIPT_STR);
#define SAVEGAME_SCRIPT        75
#define SAVEGAME_SCRIPT_STR    \
       "SAVEGAME"
PUSHMAC(SAVEGAME_SCRIPT_STR);
#define LOADGAME_SCRIPT        76
#define LOADGAME_SCRIPT_STR    \
       "LOADGAME"
PUSHMAC(LOADGAME_SCRIPT_STR);
#define ABORT_SCRIPT        77
#define ABORT_SCRIPT_STR    \
       "ABORT"
PUSHMAC(ABORT_SCRIPT_STR);
#define RESTART_SCRIPT        78
#define RESTART_SCRIPT_STR    \
       "RESTART"
PUSHMAC(RESTART_SCRIPT_STR);
#define appendScriptFile_SCRIPT        79
#define appendScriptFile_SCRIPT_STR    \
       "appendScriptFile"
PUSHMAC(appendScriptFile_SCRIPT_STR);
#define INV_SCRIPT        80
#define INV_SCRIPT_STR    \
       "INV"
PUSHMAC(INV_SCRIPT_STR);
#define ai_SCRIPT        81
#define ai_SCRIPT_STR    \
       "ai"
PUSHMAC(ai_SCRIPT_STR);
#define weaponSpeed_SCRIPT        82
#define weaponSpeed_SCRIPT_STR    \
       "weaponSpeed"
PUSHMAC(weaponSpeed_SCRIPT_STR);
#define JUMP_SCRIPT        83
#define JUMP_SCRIPT_STR    \
       "JUMP"
PUSHMAC(JUMP_SCRIPT_STR);
#define destDoor_SCRIPT        84
#define destDoor_SCRIPT_STR    \
       "destDoor"
PUSHMAC(destDoor_SCRIPT_STR);
#define HEAL_SCRIPT        85
#define HEAL_SCRIPT_STR    \
       "HEAL"
PUSHMAC(HEAL_SCRIPT_STR);
#define slope_SCRIPT        86
#define slope_SCRIPT_STR    \
       "slope"
PUSHMAC(slope_SCRIPT_STR);
#undef PUSHMAC
 }
 int result = VECTOR_INDEX_OF(MacStrs, str);
 if (result >= MacStrs.size()){result = -1;}
 return result;
}

Script::Script(Entity* ownerNew) {
 owner = ownerNew;
 currentLine = -1;
 map = NULL;
}

void Script::append(const std::string& owner){                        //popUp(__FILE__);
 std::vector<std::vector<std::string> > lineByLine = tokenize(owner); //popUp(__LINE__);
 for (unsigned k = 0; k < lineByLine.size(); k++){                    //popUp(__LINE__); //popUp(joinVector(lineByLine[k], " "));
  lines.push_back(lineByLine[k]);                                     //popUp(__LINE__);
 }                                                                    //popUp(__LINE__);
}
void Script::appendLine(std::vector<std::string> owner){
 lines.push_back(owner);
 switch (switchVal(owner[0])){
 case WHEN_SCRIPT:                                 //popUp("adding trigger for " + owner[1]);
  if (!triggers.count(owner[1])){Plot::setTrigger(owner[1], this);}           //tell the Plot to notify this if it changes
  triggers[owner[1]].push_back(lines.size() - 1);  //popUp(fullText());
  break;
 }
}
std::string Script::fullText(){
 std::vector<std::string> result;
 for (unsigned k=0;k<lines.size();k++){result.push_back(joinVector(lines[k]," "));}
 return joinVector(result, "\n");
}
std::vector<std::string> Script::nextLine(){ //popUp(__FILE__); popUp(fullText());
 std::string token;                                            //popUp(__LINE__);
 for (currentLine++; currentLine < lines.size(); currentLine++){
  if (lines[currentLine].size() > 0){
   switch (switchVal(lines[currentLine][0])){
   case WHEN_SCRIPT:                                                                                    //popUp(WHEN_SCRIPT_STR); popUp(fullText());
   {                                                                                                    //popUp(__LINE__);
    bool append = false;                                                                                //popUp(__LINE__);
    if (owner && this != owner->script){                                                                //popUp(__LINE__); popUp(owner->name);
     append = true;                                                                                     //popUp(__LINE__);
    }                                                                                                   //popUp(__LINE__);
    int stack = 0;                                                                                      //popUp(__LINE__);
    do {                                                                                                //popUp(__LINE__); popUp(lines[currentLine][0]);
     switch (switchVal(lines[currentLine][0])){                                                         //popUp(__LINE__);
     case WHEN_SCRIPT:    stack++; break;                                                               //popUp(__LINE__);
     case ENDWHEN_SCRIPT: stack--; break;                                                               //popUp(__LINE__);
     }                                                                                                  //popUp(__LINE__);
     if (append){owner->script->appendLine(lines[currentLine]);}                                        //popUp(__LINE__);
     currentLine++;                                                                                     //popUp(__LINE__); popUp(stack);
    } while (stack);                                                                                    //popUp(__LINE__);
    currentLine--;
    break;
   }
   case IF_SCRIPT:                                                //popUp(fullText());
    if (!Plot::evaluate(lines[currentLine++])){                   //popUp(__LINE__);
     for (int stack = 1; stack; currentLine++){                   //popUp(__LINE__);
      switch (switchVal(lines[currentLine][0])){                  //popUp(__LINE__);
      case IF_SCRIPT:     stack++;                                                        break;
      case ENDIF_SCRIPT:  stack--;                                                        break;
      case ELSEIF_SCRIPT: if (stack == 1 && Plot::evaluate(lines[currentLine])){stack--;} break;
      case ELSE_SCRIPT:   if (stack == 1){stack--;}                                       break;
      }
     }
    }
    currentLine--;
    break;
   case ELSE_SCRIPT:
   case ELSEIF_SCRIPT: //either way, skip to the corresponding ENDIF
    for (int stack = 1; stack; currentLine++){
     token = lines[currentLine][0];
     switch (switchVal(token)){
     case IF_SCRIPT:    stack++; break;
     case ENDIF_SCRIPT: stack--; break;
     }
    }
    currentLine--;
    break;
   case ENDIF_SCRIPT:
   case ENDWHEN_SCRIPT:
   case ENDOPTIONBOX_SCRIPT:
    //ignore and go on to the next line
    break;
   case OPTION_SCRIPT:
    currentLine++;
    for (int stack = 1; stack; currentLine++){
     switch (switchVal(lines[currentLine][0])){
     case OPTIONBOX_SCRIPT:     stack++;                                                        break;
     case ENDOPTIONBOX_SCRIPT:  stack--;                                                        break;
     }
    }
    break;
   default: //if it's not one of those recognized cases, we must be on the next valid line of script
    return lines[currentLine];
   }
  }
 }
 return std::vector<std::string>();
}
bool Script::execFromStart(){ //popUp(__FILE__); popUp(__LINE__);
 currentLine = -1;            //popUp(__LINE__);
 return execNext();
}
bool Script::execNext(){      //popUp(__FILE__); popUp(__LINE__);
 nextLine();                  //popUp(__LINE__);
 return execCurrent();
}
bool Script::execLine(unsigned newLine){
 currentLine = newLine;
 return execCurrent();
}
bool Script::execCurrent(){                                                    //popUp(__FILE__); popUp(__LINE__); popUp(fullText());
 if (currentLine >= lines.size()){return false;}
 Entity* trueOwner = owner;
 for (std::vector<std::string> line = lines[currentLine]; currentLine < lines.size(); line = nextLine()){
  int i=0;
  if (line.size() > i){                                                        //popUp(line[i]);
   switch (switchVal(line[i])){
   case TOP_SCRIPT:    map->top = parseInt(line[1]); break;
   case LEFT_SCRIPT:   map->left = parseInt(line[1]); break;
   case RIGHT_SCRIPT:  map->right = parseInt(line[1]); break;
   case BOTTOM_SCRIPT: map->bottom = parseInt(line[1]); break;
   case ABORT_SCRIPT:  currentLine = -1; return true;
   case RESTART_SCRIPT: currentLine = -1; break;
   case SWITCH_SCRIPT:
    trueOwner = owner;
    owner = new Switch();
    if (line.size() > ++i){owner->name = line[i];}
    if (Plot::get(owner->name)){static_cast<Switch*>(owner)->toggle();}
    break;
   case ITEM_SCRIPT:
    trueOwner = owner;
    owner = new Item();       if (line.size() > ++i){owner->setName(line[i]);}
    break;
   case NPC_SCRIPT:
    trueOwner = owner;
    owner = new Unit();
    owner->setColor(PIXEL_LIGHTEN(PIXEL_PURPLE,3,4) | PIXEL_ALPHA);
    if (line.size() > ++i){owner->setName(line[i]);}
    break;
   case ENEMY_SCRIPT:
   {
    trueOwner = owner;
    Unit* u = new Unit();
    u->setColor(PIXEL_RED | PIXEL_ALPHA);
    u->setFaction(factionEnemy);
    if (line.size() > ++i){u->setName(line[i]);}
    owner = u;
    break;
   }
   case BLOCK_SCRIPT:
    trueOwner = owner;
    owner = new Entity();     if (line.size() > ++i){owner->name = line[i];}
    owner->bounciness = 1;
    owner->immobile = false;
    break;
   case FLOOR_SCRIPT:
   case CEILING_SCRIPT:
   case WALL_SCRIPT:
    trueOwner = owner;
    owner = new Entity();     if (line.size() > ++i){owner->name = line[i];}
    //owner->sprite = Sprite::load("Stone", false);
    break;
   case DOOR_SCRIPT:
    trueOwner = owner;
    owner = new Door();
    if (line.size() > ++i){owner->setName(line[i]); owner->uid = line[i];} //doors locate each other by uid
    if (map)              {
     static_cast<Door*>(owner)->destDoor = map->path;}
    break;
   case WALLPAPER_SCRIPT:
    trueOwner = owner;
    owner = new Background(); if (line.size() > ++i){owner->name = line[i];}
    break;
   case LOADGAME_SCRIPT: Game::engine->load(); return true; //loading a game MUST abort the current script
   case SAVEGAME_SCRIPT: Game::engine->save(); break; //saving a game does NOT necessarily abort the current script
   case scriptFile_SCRIPT:
    owner->script = new Script(); //clear out the old script, and proceed to the next case
   case appendScriptFile_SCRIPT:
   {
    Script* scriptNew = Script::fromFile("scripts/" + line[i+1]);
    scriptNew->owner = owner;
    scriptNew->execFromStart();
    break;
   }
   case SCRIPT_SCRIPT:
   {
    if (!owner->script){owner->script = new Script(owner);}
    int stack = 1;
    do {
     std::vector<std::string> line = lines[++currentLine];
     switch (switchVal(line[0])){
     case SCRIPT_SCRIPT:    stack++; break;
     case ENDSCRIPT_SCRIPT: stack--; break;
     }
     if (stack > 0){owner->script->appendLine(line);}
    } while (stack);
    break;
   }
   case END_SCRIPT:
    if (!owner->uid.size()){ //popUp("generating uid for entity " + owner->name);
     owner->uid = this->map->path + "_" + toStr((int)currentLine);
    } //popUp(owner->uid);
    if (!Plot::get(PLOT_DESTROYED(owner))){map->addEntity(owner);}
    owner = trueOwner; //we have finished generating the item, so return control to the normal owner
    break;
   case OPTIONBOX_SCRIPT:                                                      //popUp(__LINE__);
   {                                                                           //popUp(__LINE__);
    i++;                                                                       //popUp(__LINE__);
    std::string prompt;                                                        //popUp(__LINE__);
    if (line.size() > i){prompt = line[i++];}                                  //popUp(__LINE__);
    std::vector<std::pair<std::string, unsigned> > options;                    //popUp(__LINE__);
    OptionBox* result = new OptionBox(prompt,options);                         //popUp("making option box with prompt: " + prompt);
    for  (; i < line.size(); i++){                                             //popUp(__LINE__);
     switch (switchVal(line[i])){                                              //popUp(__LINE__);
     case CASCADE_SCRIPT: result->cascade = true; break;                       //popUp(__LINE__);
     case MODELESS_SCRIPT: result->modal = false; break;                       //popUp(__LINE__);
     default: popUp("error: unrecognized keyword " + line[i] + " in line " + joinVector(lines[currentLine], " ")); return false; //popUp(__LINE__);
     }                                                                         //popUp(__LINE__);
    }                                                                          //popUp(__LINE__);
    for (std::string token = lines[++currentLine][0]; switchVal(token) != ENDOPTIONBOX_SCRIPT; token = lines[currentLine][0]){ //popUp(__LINE__);
     switch (switchVal(token)){                                                //popUp(__LINE__);
     case OPTION_SCRIPT:                                                       //popUp(__LINE__);
     {                                                                         //popUp(__LINE__);
      prompt = lines[currentLine][1];
      options.push_back(std::make_pair(prompt, currentLine++));                //popUp("option " + prompt + " will trigger line " + toStr((int)currentLine));
      for (int stack = 1; stack; currentLine++){                               //popUp(__LINE__);
       switch (switchVal(lines[currentLine][0])){                              //popUp(__LINE__);
       case OPTION_SCRIPT:       if (stack == 1){stack--;} break;              //popUp(__LINE__);
       case OPTIONBOX_SCRIPT:    stack++; break;                               //popUp(__LINE__);
       case ENDOPTIONBOX_SCRIPT: stack--; break;                               //popUp(__LINE__);
       }                                                                       //popUp(__LINE__);
      }                                                                        //popUp(__LINE__);
      currentLine--;                                                           //popUp(__LINE__);
      break;                                                                   //popUp(__LINE__);
     }                                                                         //popUp(__LINE__);
     default:                                                                  //popUp(__LINE__);
      popUp("error: expected next OPTION for OPTIONBOX, but found line " + joinVector(lines[currentLine], " ")); //popUp(__LINE__);
      return false;                                                            //popUp(__LINE__);
     }                                                                         //popUp(__LINE__);
    }                                                                          //popUp(__LINE__);
    result->options = options;                                                 //popUp(__LINE__);
    result->script = this;                                                     //popUp(__LINE__);
    result->owner = this->owner;                                               //popUp(__LINE__);
    result->refresh();                                                         //popUp(__LINE__);
    Game::engine->addBox(result);                                              //popUp(__LINE__);
    return true;
   }
   case TEXTBOX_SCRIPT:
   {
    i++;
    std::string text;
    if (line.size() > i){text = line[i++];}
    TextBox* result = new TextBox(text);
    for  (; i < line.size(); i++){ //optional parameters
     switch (switchVal(line[i])){
     case CASCADE_SCRIPT:  result->cascade = true;  break;
     case MODELESS_SCRIPT: result->modal = false;   break;
     case NOFADE_SCRIPT:   result->closeAfter = -1; break;
     default: popUp("error: unrecognized keyword " + line[i] + " in line " + joinVector(lines[currentLine], " ")); return false;
     }
    }
    result->owner = owner;
    result->script = this;
    Game::engine->addBox(result);
    return true;
   }
   case SET_SCRIPT:                           //popUp(__LINE__);
    if (line.size() > ++i + 1){               //popUp(__LINE__);
     Plot::set(line[i], parseInt(line[i+1])); //popUp(__LINE__);
    } else {                                  //popUp(__LINE__);
     Plot::set(line[i], 1);                   //popUp(__LINE__);
    }                                         //popUp(__LINE__);
    break;
   case MAKEITEMSCREEN_SCRIPT:
   {
    bool cascade = false;
    if (line.size() > ++i && switchVal(line[i]) == CASCADE_SCRIPT){cascade = true;}
    Game::engine->makeItemScreen(cascade);
    return true;
   }
   case NEWGAME_SCRIPT:
    Game::engine->setMode(modeInit);
    return true;
   case MAKESTATSCREEN_SCRIPT: Game::engine->makeStatScreen();            return true;
   case MAKEQUITSCREEN_SCRIPT: Script::fromFile("scripts/QuitMenu")->execFromStart(); return true;
   case color_SCRIPT:
    owner->color = parseInt(line[i+1]);
    if (owner->sprite){owner->sprite->greenScreen = parseInt(line[i+1]) | PIXEL_ALPHA;}
    break;
   case sprite_SCRIPT: owner->sprite = Sprite::load(line[i+1]);        break;
   case noMask_SCRIPT: owner->sprite = Sprite::load(line[i+1], false); break;
   case PATROL_SCRIPT:
    if (line.size() > i + 1){
     switch (switchVal(line[i+1])){
     case UP_SCRIPT:    owner->patrolTo(dirUp);    break;
     case DOWN_SCRIPT:  owner->patrolTo(dirDown);  break;
     case LEFT_SCRIPT:  owner->patrolTo(dirLeft);  break;
     case RIGHT_SCRIPT:
     default:           owner->patrolTo(dirRight); break;
     }
    } else {
     owner->patrolTo(dirRight);
    }
    break;
   case JUMP_SCRIPT:  static_cast<Unit*>(owner)->jump();       break;
   case immobile_SCRIPT:  owner->immobile = true;              break;
   case weightless_SCRIPT:  owner->weightless = true;          break;
   case uid_SCRIPT:    owner->uid = line[i+1];                 break;
   case weaponSpeed_SCRIPT: static_cast<Unit*>(owner)->weaponSpeed = parseFloat(line[i+1]);       break;
   case x_SCRIPT:      owner->x = parseFloat(line[i+1]);       break;
   case y_SCRIPT:      owner->y = parseFloat(line[i+1]);       break;
   case z_SCRIPT:      owner->z = parseFloat(line[i+1]);       break;
   case h_SCRIPT:      owner->h = parseFloat(line[i+1]);       break;
   case w_SCRIPT:      owner->setWidth(parseFloat(line[i+1])); break;
   case d_SCRIPT:      owner->d = parseFloat(line[i+1]);       break;
   case ai_SCRIPT:
    if (!line[i+1].compare("defensive")){
     static_cast<Unit*>(owner)->ai = aiDefensive;
    } else if (!line[i+1].compare("aggressive")){
     static_cast<Unit*>(owner)->ai = aiAggressive;
    } else if (!line[i+1].compare("neutral")){
     static_cast<Unit*>(owner)->ai = aiNeutral;
    }
    break;
   case slope_SCRIPT:
    if (!line[i+1].compare("U")){
     owner->slope = slopeU;
    } else if (!line[i+1].compare("D")){
     owner->slope = slopeD;
    } else if (!line[i+1].compare("IU")){
     owner->slope = slopeIU;
    } else if (!line[i+1].compare("ID")){
     owner->slope = slopeID;
    }
    break;
   case HEAL_SCRIPT: if (line.size() == 2){Game::engine->heal(line[i+1]);} else {Game::engine->heal(line[i+1],line[i+2]);}
   case maxDx_SCRIPT:  owner->setMaxDx(parseFloat(line[i+1])); break;
   case maxDy_SCRIPT:  owner->setMaxDy(parseFloat(line[i+1])); break;
   case hurtOnTouch_SCRIPT: static_cast<Unit*>(owner)->hurtOnTouch = true;       break;
   case spriteSpeed_SCRIPT: owner->sprite->setSpeed(parseFloat(line[i+1]));      break;
   case destDoor_SCRIPT: static_cast<Door*>(owner)->destDoor = line[i+1];        break;
   case OPEN_SCRIPT:     static_cast<Door*>(owner)->setOpen(true);               break;
   case CLOSE_SCRIPT:    static_cast<Door*>(owner)->setOpen(false);              break;
   case destX_SCRIPT:    static_cast<Door*>(owner)->destX = parseInt(line[i+1]); break;
   case destY_SCRIPT:    static_cast<Door*>(owner)->destY = parseInt(line[i+1]); break;
   case destZ_SCRIPT:    static_cast<Door*>(owner)->destZ = parseInt(line[i+1]); break;
   case dest_SCRIPT:     static_cast<Door*>(owner)->dest = line[i+1];            break;
   case QUIT_SCRIPT:     PostQuitMessage(0); break;
   case BGM_SCRIPT:      Audio::playBGM(line[i+1]); break;
   case INV_SCRIPT:
   {
    Item* item = new Item();
    item->setName(line[i+1]);
    Unit* u = static_cast<Unit*>(owner);
    u->inventory.push_back(item);
    item->owner = u;
    break;
   }
   case USE_SCRIPT:
   case RH_SCRIPT:
   case BH_SCRIPT:
   case LH_SCRIPT:
   case ACC_SCRIPT:
   {
    Unit* u = static_cast<Unit*>(owner);
    Item* item;
    if (isInt(line[i+1])){
     item = u->inventory[parseInt(line[i+1])];
    } else {
     item = new Item();
     item->setName(line[i+1]);
     item->owner = static_cast<Unit*>(owner);
    }
    u->use(line[i], item);
    Game::engine->checkCursorVisible(); //the used item may have made the cursor visible/invisible
    break;
   }
   case UNEQUIP_SCRIPT:
   {
    Unit* u = static_cast<Unit*>(owner);
    u->unUse(u->inventory[parseInt(line[i+1])]);
    Game::engine->checkCursorVisible(); //the used item may have made the cursor visible/invisible
    break;
   }
   case -1: //this keyword does not belong to Script, so pass it back to whatever called us
    popUp("unrecognized keyword: " + line[i]);
    return false;
   default:
    popUp(line[i] + " gives an unhandled switchVal of " + toStr(switchVal(line[i])));
    return false;
   }
  }
 }
 return false;
}
Script* Script::fromFile(const std::string& path){     //popUp(__FILE__);
 Script* result = NULL;                                //popUp(__LINE__);
 std::ifstream file((g_folder + "/" + path).c_str());                     //popUp(__LINE__);
 if (!file.fail()){                                    //popUp(__LINE__);
  result = new Script();                               //popUp(__LINE__);
  std::stringstream buffer;                            //popUp(__LINE__);
  buffer << file.rdbuf();                              //popUp(__LINE__);
  result->append(buffer.str());                        //popUp(__LINE__);
 }                                                     //popUp(__LINE__);
 file.close();                                         //popUp(__LINE__);
 return result;
}
void Script::trigger(const std::string& plotKey, bool force){   //popUp("a script belonging to " + owner->name + " has been notified that " + plotKey + " is now " + toStr(plotVal));
 for (unsigned k=0;k<triggers[plotKey].size();k++){
  unsigned i = triggers[plotKey][k];                //popUp("evaluating " + joinVector(lines[i], " ") + " for " + owner->name);
  if (force || Plot::evaluate(lines[i])){           //popUp(joinVector(lines[i], " ") + " came back true for " + owner->name);
   execLine(i + 1);
  }
 }
}
void Script::removeTrigger(const std::string& plotKey){if(triggers.count(plotKey)){triggers.erase(plotKey);}}
