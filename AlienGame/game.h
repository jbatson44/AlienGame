/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#define BIG 11
#define ENEMIES 1
#include <vector>
#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"
#include "rocks.h"
#include "ship.h"
#include "bullet.h"
#include "flyingObject.h"
#include "enemy.h"
#include "debris.h"
#include "ufo.h"
#include "ufogun.h"

using namespace std;
class Game
{
private:
	int score;
    Point topLeft;
    Point bottomRight;
    Ship ship;
	vector <Rocks*> rocks;
    vector <Enemy> enemy;
 
    vector <Bullet> bullets;
    vector <Bullet> ebullets;
   
    vector <Debris> debris;
    UFO ufo;
   vector <UFOGun> guns;
  
    int kills;
	bool over;
    int counter;
	bool pause;
public:
   Game(Point topLeft, Point bottomRight);
   ~Game();
   void reset();
   void handleInput(const Interface & ui);
   void advance();
   void draw(const Interface & ui);
   //bool isOnScreen(const Point & point);
   void advanceShip();
   void advanceUFO();
   void advanceUFOguns();
   void advanceEnemy();
   void advanceDebris();
   void advanceBullets();
   void advanceEbullets();
   void advanceRock();


   bool inSight(float angle, FlyingObject &looking, FlyingObject &seen);
   float area(int x1, int y1, int x2, int y2, int x3, int y3);
   
   void handleCollisions();
   void cleanUpZombies();
   float getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const;
};



#endif /* GAME_H */
