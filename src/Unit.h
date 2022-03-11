/*
 * Unit.h
 *
 *  Created on: Nov 21, 2017
 *      Author: tr_dawson
 */

#ifndef UNIT_H_
#define UNIT_H_

#include "Entity.h"
#include "Door.h"
#include "Item.h"
#include "Plot.h"
#include "TextBox.h"
#include "Bar.h"

#define UNIT_RH  "RH"
#define UNIT_LH  "LH"
#define UNIT_BH  "BH"
#define UNIT_ACC "ACC"

enum Faction {factionNull, factionPlayer, factionEnemy, factionChaotic};
enum AIType {aiNull, aiAggressive, aiNeutral, aiDefensive};

class Bullet; //forward declaration

class Unit: public Entity {
public:
 Unit();
 float weaponSpeed;
 virtual ~Unit(){};
 void getHitFrom(Direction dir, Unit* other);
 void jump();
 void moveRight();
 void moveLeft();
 Bar* hpBar;
 Bar* mpBar;
 void use (const std::string& useType, Item* item);
 void unUse (Item* item);
 void advance(float gravity, const std::vector<Entity*>& others, std::vector<Entity*>& toAdd);
 virtual void interactWith(Entity* other);
 bool canPickUp;
 std::vector<Item*> inventory;
 int inventoryMax;
 Faction faction;
 AIType ai;
 std::vector<Faction> enemyFactions;
 void setFaction(Faction factionNew);
 void doAI(const std::vector<Entity*>& others);
 int rhCap;
 int lhCap;
 int accCap;
 float atk;
 float def;
 int visualRange;
 int hp;
 bool hurtOnTouch;
 bool stunMove;
 bool stunShoot;
 int stunned;
 int dead;
 Direction patrol;
 void getShotBy(Bullet* bullet);
 void takeDamage(int damage);
 void getStunned(int stunFrames);
 int hpMax;
 int mp;
 int mpMax;
 bool fireR;
 bool fireL;
 Entity* target; //maybe use float pointers instead?
 void addHp(int toAdd);
 void fireAll(const std::vector<Item*>& toFire, std::vector<Entity*>& newBullets);
 std::vector<Item*> lh;
 std::vector<Item*> rh;
 std::vector<Item*> bh;
 std::vector<Item*> acc;
protected:
 void resetJumps();
 bool wallJump;
 int maxJumps;
 int jumpsLeft;
 float agi;
 void die();
 virtual bool hitFrom(Entity* other, Direction dir);
};

#endif /* UNIT_H_ */
