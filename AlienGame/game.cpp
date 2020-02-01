/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>

using namespace std;

/*****************************************************************
* CONSTRUCTOR
* Make all the rocks
* make all the enemies
* set counter to 0
* set score to 0
*****************************************************************/
Game::Game(Point topLeft, Point bottomRight)
{
	Point point(-30, 0);
	drawText(point, "Press the space bar to start!");
	
	reset();
	pause = false;
}

void Game::reset()
{
	Ship newShip;
	ship = newShip;
	rocks.clear();
	for (int i = 0; i < BIG; i++)
	{
		BigRock* bigrock = new BigRock();
		//rocks.push_back(bigrock);
	}
    ufo.setAlive(true);
	ufo.setPoint(Point(-200, 200));
	ufo.setHits(0);
	ufo.setLeft(false);
	ufo.setCount(0);

	guns.clear();
	enemy.clear();

	Point pt1(ufo.getPoint().getX(), ufo.getPoint().getY() - 108);
	UFOGun g1(pt1, ufo.getPoint());
	guns.push_back(g1);

	Point pt2(ufo.getPoint().getX() - 80, ufo.getPoint().getY() - 74);
	UFOGun g2(pt2, ufo.getPoint());
	guns.push_back(g2);

	Point pt3(ufo.getPoint().getX() + 80, ufo.getPoint().getY() - 74);
	UFOGun g3(pt3, ufo.getPoint());
	guns.push_back(g3);

	Point pt4(ufo.getPoint().getX() - 42, ufo.getPoint().getY() - 99);
	UFOGun g4(pt4, ufo.getPoint());
	guns.push_back(g4);

	Point pt5(ufo.getPoint().getX() + 42, ufo.getPoint().getY() - 99);
	UFOGun g5(pt5, ufo.getPoint());
	guns.push_back(g5);

	counter = 0;

	// our killcount starts at 0
	kills = 0;
	score = 0;
	over = false;
}

/*****************************************************************
* call the clear functions for each vector
*****************************************************************/
Game::~Game()
{
	rocks.clear();
	bullets.clear();
	enemy.clear();
	guns.clear();
	cleanUpZombies();
}


/*****************************************************************
* HANDLE INPUT
* handle user input to move the ship and fire bullets
*****************************************************************/
void Game :: handleInput(const Interface & ui)
{
	
	if (ship.isAlive())
	{
		if (ui.isUp())
		{
			ship.move();
		}
		if (ui.isLeft())
		{
			ship.turnLeft();
		}
		if (ui.isRight())
		{
			ship.turnRight();
		}
		if (ui.isDown())
		{
			ship.brakes();
		}
		if (ui.isSpace())
		{
			//pause = !pause;
			// shoot a bullet
			bullets.push_back(Bullet(ship.getPoint(), ship.getVelocity(), ship.getAngle(), false));
			// special gun: shoot 5 bullets at once;
			if (ui.isV() && kills > 5)
			{
				bullets.push_back(Bullet(ship.getPoint(), ship.getVelocity(), ship.getAngle()+30, false));
				bullets.push_back(Bullet(ship.getPoint(), ship.getVelocity(), ship.getAngle()+15, false));
				bullets.push_back(Bullet(ship.getPoint(), ship.getVelocity(), ship.getAngle(), false));
				bullets.push_back(Bullet(ship.getPoint(), ship.getVelocity(), ship.getAngle()-15, false));
				bullets.push_back(Bullet(ship.getPoint(), ship.getVelocity(), ship.getAngle()-30, false));
			}
		}
	}
	else if (over)
	{
		if (ui.isSpace())
		{
			reset();
		}
	}
	if (ui.isV())
	{
		
	}
}


/*****************************************************************
* ADVANCE
* call each objects advance function. And cleanUpZombies
*****************************************************************/
void Game::advance()
{
	if (!pause)
	{
		advanceShip();

		advanceUFO();

		advanceEnemy();

		advanceDebris();

		advanceBullets();

		advanceEbullets();

		advanceRock();

		handleCollisions();

		cleanUpZombies();
	}
}

/*****************************************************************
* DRAW
* draw all of the objects in our game
*****************************************************************/
void Game :: draw(const Interface & ui)
{
	/***********************************************************
	* Our ship
	**********************************************************/
	// draw our ship
	if (ship.isAlive())
		ship.draw();
	// draw the game over message
	else
	{
		Point point(-30, 0);
		drawText(point, "Game Over");
	}

	// draw our bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
			bullets[i].draw();
	}
	/*********************************************************/

	/***********************************************************
	* The Enemies
	**********************************************************/
	// draw the UFO and it's guns
	//if (ufo.isAlive())
	{
		ufo.draw();
		for (int i = 0; i < guns.size(); i++)
		{
			guns[i].draw();
		}

	}

	// draw the enemy ships
	for (int i = 0; i < enemy.size(); i++)
	{
		if (enemy[i].isAlive())
			enemy[i].draw();
	}


	// draw enemy bullets
	for (int i = 0; i < ebullets.size(); i++)
	{
		if (ebullets[i].isAlive())
			ebullets[i].draw();
	}
	/*********************************************************/

	/*************************************************************
	* Asteroids
	**************************************************************/
	for (int i = 0; i < rocks.size(); i++)
	{
		if (rocks[i]->isAlive())
			rocks[i]->draw();
	}
	/***************************************************/


	// if we've killed everyone then we win!
	if (!ufo.isAlive() && enemy.empty() && rocks.empty())
	{
		over = true;
		Point point(-30, 0);
		drawText(point, "You Win!");
	}

	
	// draw the debris of destroyed ships
	for (int i = 0; i < debris.size(); i++)
	{
		if (debris[i].isAlive())
		{
			//cout << debris.size() << endl;
			debris[i].draw();
		}
	}



	// draw health
	Point text(0, 280);
	drawText(text, "Health:");
	Point sc(50, 289);
	drawNumber(sc, ship.numHits());

	// draw kill count
	Point text1(90, 280);
	drawText(text1, "Kills:");
	Point sc1(140, 289);
	drawNumber(sc1, kills);
}


///*****************************************************************
//*
//*****************************************************************/
//bool Game :: isOnScreen(const Point & point)
//{
//	return true;
//}

/*****************************************************************
* ADVANCE UFO
* this will call our ufo's advance function and ADVANCE UFO GUNS
* We will also spawn enemy ships
*****************************************************************/
void Game::advanceUFO()
{
	counter++;
	if (ufo.isAlive())
	{
		advanceUFOguns();
		ufo.advance();
		if (counter % 80 == 0)
		{
			// create more enemies
			enemy.push_back(Enemy(ufo.getPoint()));
		}
	}
}

/*****************************************************************
* ADVANCE UFO GUNS
* We move the guns to match the motion of the ufo
* we also check to see if the ship is close enough to shoot at
*****************************************************************/
void Game::advanceUFOguns()
{
	for (int i = 0; i < guns.size(); i++)
	{
		if (ship.isAlive())
		{
			if (getClosestDistance(ship, guns[i]) < 150 && ship.isAlive() && guns[i].isAlive())
			{
				guns[i].advance(ufo.getVelocity().getDx(), ufo.getVelocity().getDy(), ship);
			}
			else
			{
				guns[i].advance(ufo.getVelocity().getDx(), ufo.getVelocity().getDy());
			}
		}
		else
		{
			guns[i].advance(ufo.getVelocity().getDx(), ufo.getVelocity().getDy());
		}
	}
}


/*****************************************************************
* ADVANCE BULLETS
* move our bullets
*****************************************************************/
void Game :: advanceBullets()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].advance();
	}
}


/*****************************************************************
* ADVANCE EBULLETS
* move enemy bullets
*****************************************************************/
void Game::advanceEbullets()
{
	for (int i = 0; i < ebullets.size(); i++)
	{
		ebullets[i].advance();
	}
}

/*****************************************************************
* ADVANCE SHIP
* Move our ship
*****************************************************************/
void Game :: advanceShip()
{
	if (ship.isAlive())
		ship.advance();
	else
		over = true;
}

/*****************************************************************
* ADVANCE ENEMY
* Move the enemys
* Check to see if the enemy ships can see us and if they can have
* them pursue us.
*****************************************************************/
void Game::advanceEnemy()
{
	// loop through all enemies
	for (int i = 0; i < enemy.size(); i++)
	{
		inSight(enemy[i].getAngle(), enemy[i], ship);
		// if the ship is within a certain distance of the enemy 
		if (getClosestDistance(ship, enemy[i]) < 200 && ship.isAlive())
		{
			// we check to see if the enemy can see our ship
			// if they can then they will pursue us
			if (inSight(enemy[i].getAngle(), enemy[i], ship))
			{
				enemy[i].advance(ship);
				// and we have them shoot at us
				if (enemy[i].getDelay() % 10 == 0)
				{
					ebullets.push_back(Bullet(enemy[i].getPoint(), enemy[i].getVelocity(), enemy[i].getAngle(), true));
				}
			}
			// they can't see us now so they go in one direction
			else
			{
				enemy[i].advance();
			}
		}
		// if our ship isn't close then they go in one direction
		else
			enemy[i].advance();
	}
}

/*****************************************************************
* IN SIGHT
* Check to see if one flyingObject can see another
* For now it only checks if enemy ships can see our ship.
*****************************************************************/
bool Game::inSight(float angle, FlyingObject &looking, FlyingObject &seen)
{
	angle += 180;
	float mainX = looking.getPoint().getX();
	float mainY = looking.getPoint().getY();
	// find x2 y2
	float angle2 = angle + 25;

	float dy2 = 200 * (-cos(M_PI / 180.0 * angle2));
	float dx2 = 200 * (sin(M_PI / 180.0 * angle2));

	float x2 = mainX + dx2;
	float y2 = mainY + dy2;

	Point pt2(x2, y2);
	//drawDot(pt2);
	

	float angle3 = angle - 25;

	float dy3 = 200 * (-cos(M_PI / 180.0 * angle3));
	float dx3 = 200 * (sin(M_PI / 180.0 * angle3));

	float x3 = mainX + dx3;
	float y3 = mainY + dy3;

	Point pt3(x3, y3);
	//drawDot(pt3);
	// this will show their vision
	//drawLine(looking.getPoint(), pt2, 1, 1, 0);
	//drawLine(looking.getPoint(), pt3, 1, 1, 0);
	//drawLine(pt3, pt2, 1, 1, 0);

	/*std::cout << "enemys point: " << looking.getPoint() << std::endl;
	std::cout << "ships point: " << seen.getPoint() << std::endl;
	std::cout << "pt2 point: " << pt2 << std::endl;
	std::cout << "pt3 point: " << pt3 << std::endl;*/

	float A = area(looking.getPoint().getX(), looking.getPoint().getY(), x2, y2, x3, y3);

	float A1 = area(seen.getPoint().getX(), seen.getPoint().getY(), x2, y2, x3, y3);

	float A2 = area(looking.getPoint().getX(), looking.getPoint().getY(), seen.getPoint().getX(), seen.getPoint().getY(), x3, y3);

	float A3 = area(looking.getPoint().getX(), looking.getPoint().getY(), x2, y2, seen.getPoint().getX(), seen.getPoint().getY());
	
	bool in = (A == A1 + A2 + A3);
	/*std::cout << "angle: " << angle << std::endl;
	std::cout << "in?: " << in << std::endl;*/
	return in;
}

/*****************************************************************
* AREA
* get the area of a triangle
*****************************************************************/
float Game::area(int x1, int y1, int x2, int y2, int x3, int y3)
{
	return abs((x1*(y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}

/*****************************************************************
* ADVANCE DEBRIS
* Move the dead stuff
*****************************************************************/
void Game::advanceDebris()
{
	for (int i = 0; i < debris.size(); i++)
	{
		if (debris[i].isAlive())
		{
			debris[i].advance();
		}
	}
}

/*****************************************************************
* ADVANCE ROCK
* Move all of the asteroids.
*****************************************************************/
void Game :: advanceRock()
{
	for (int i = 0; i < rocks.size(); i++)
	{
		rocks[i]->advance();
	}
}

/*****************************************************************
* HANDLE COLLISIONS
* Check if any objects hit each other
*****************************************************************/
void Game :: handleCollisions()
{
	/********************************************************
	* ASTEROIDS: does the ship crash int a rock?
	*********************************************************/
	for (int i = 0; i < rocks.size(); i++)
	{
		if (getClosestDistance(*rocks[i], ship) < 16)
		{
			ship.setAlive(false);
		}
	}
	
	/***********************************************************/

	/********************************************************
	* ASTEROIDS: did our bullets kill a rock?
	*********************************************************/
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int j = 0; j < rocks.size(); j++)
		{
			if (getClosestDistance(*rocks[j], bullets[i]) < rocks[j]->getRadius())
			{
				rocks[j]->kill();
				bullets[i].setAlive(false);

				if (rocks[j]->getRadius() == 15)
				{
					MediumRock * medrock1 = new MediumRock(rocks[j]->getPoint(), rocks[j]->getVelocity(), 1);
					rocks.push_back(medrock1);
					MediumRock * medrock2 = new MediumRock(rocks[j]->getPoint(), rocks[j]->getVelocity(), -1);
					rocks.push_back(medrock2);
					SmallRock * smarock = new SmallRock(rocks[j]->getPoint(), rocks[j]->getVelocity(), 2);
					rocks.push_back(smarock);
					score += 3;
				}
				else if (rocks[j]->getRadius() == 8)
				{
					SmallRock * smarock = new SmallRock(rocks[j]->getPoint(), rocks[j]->getVelocity(), 3);
					rocks.push_back(smarock);
					SmallRock * smarock2 = new SmallRock(rocks[j]->getPoint(), rocks[j]->getVelocity(), -3);
					rocks.push_back(smarock2);
					score += 6;
				}
				else
				{
					score += 9;

					debris.push_back(Debris(rocks[j]->getPoint(), Velocity(-1, 0), 3));
					debris.push_back(Debris(rocks[j]->getPoint(), Velocity(1, 0), 3));
					debris.push_back(Debris(rocks[j]->getPoint(), Velocity(0, 1), 3));
					debris.push_back(Debris(rocks[j]->getPoint(), Velocity(0, -1), 3));
				}
			}
		}
	}
	/**********************************************************/

	/**********************************************************
	* Did we get hit by an enemy's bullets?
	***********************************************************/
	for (int i = 0; i < ebullets.size(); i++)
	{
		if (getClosestDistance(ebullets[i], ship) < 3)
		{
			ship.hit();
			
			ebullets[i].setAlive(false);
			if (!ship.isAlive())
			{
				debris.push_back(Debris(ship.getPoint(), Velocity(-1, 0), 1));
				debris.push_back(Debris(ship.getPoint(), Velocity(1, 0), 1));
				debris.push_back(Debris(ship.getPoint(), Velocity(0, 1), 1));
				debris.push_back(Debris(ship.getPoint(), Velocity(0, -1), 1));
			}
		}
	}
	/**************************************************************/

	/****************************************************
	* handle ufo bullets hitting the ship
	****************************************************/
	for (int i = 0; i < guns.size(); i++)
	{
		for (int j = 0; j < guns[i].bullets.size(); j++)
		{
			if (getClosestDistance(guns[i].bullets[j], ship) < 5)
			{
				//ship.setAlive(false);
				ship.hit();

				guns[i].bullets[j].setAlive(false);
				if (!ship.isAlive())
				{
					debris.push_back(Debris(ship.getPoint(), Velocity(-1, 0), 1));
					debris.push_back(Debris(ship.getPoint(), Velocity(1, 0), 1));
					debris.push_back(Debris(ship.getPoint(), Velocity(0, 1), 1));
					debris.push_back(Debris(ship.getPoint(), Velocity(0, -1), 1));
				}
			}
		}
	}
	/****************************************************/

	/*********************************************************
	* Are we shooting a UFO or an enemy ship?
	*********************************************************/
	for (int i = 0; i < bullets.size(); i++)
	{
		if (ufo.isAlive())
		{
			if (getClosestDistance(bullets[i], ufo) < 100)
			{
				bullets[i].setAlive(false);
				score += 1;
				//drawFire(bullets[i].getPoint(), 0);
				//debris.push_back(Debris(bullets[i].getPoint(), Velocity(bullets[i].getVelocity().getDx() * -1 + 3, bullets[i].getVelocity().getDy() * -1 + 3)));
				int dead = 0;
				for (int i = 0; i < guns.size(); i++)
				{
					if (!guns[i].isAlive())
					{
						dead++;
					}
				}
				if (guns.size() == dead)
				{
					drawFire(bullets[i].getPoint(), 0);
					ufo.hit();
				}
				
				if (!ufo.isAlive())
				{
				debris.push_back(Debris(ufo.getPoint(), Velocity(1, 1), 2));
				debris.push_back(Debris(ufo.getPoint(), Velocity(1, -1), 2));
				debris.push_back(Debris(ufo.getPoint(), Velocity(-1, 1), 2));
				debris.push_back(Debris(ufo.getPoint(), Velocity(-1, -1), 2));
				debris.push_back(Debris(ufo.getPoint(), Velocity(-1.5, -1), 2));
				debris.push_back(Debris(ufo.getPoint(), Velocity(-1, -1.5), 2));
				}
			}
			for (int j = 0; j < guns.size(); j++)
			{
				if (getClosestDistance(bullets[i], guns[j]) < 8)
				{
					bullets[i].setAlive(false);
					score += 1;
					guns[j].hit();
				}
			}
		}
		// did we kill an enemy
		for (int j = 0; j < enemy.size(); j++)
		{
			if (enemy[j].isAlive())
			{
				if (getClosestDistance(bullets[i], enemy[j]) < 5)
				{
					//enemy[j].hit();
					enemy[j].setAlive(false);
					bullets[i].setAlive(false);
					score += 4;
					kills++;
					if (j % 2 == 0)
					{
						debris.push_back(Debris(enemy[j].getPoint(), Velocity(-1, 0), 2));
						debris.push_back(Debris(enemy[j].getPoint(), Velocity(1, 0), 2));
						debris.push_back(Debris(enemy[j].getPoint(), Velocity(0, 1), 2));
						debris.push_back(Debris(enemy[j].getPoint(), Velocity(0, -1), 2));
					}
					else
					{
						debris.push_back(Debris(enemy[j].getPoint(), Velocity(1, 1), 2));
						debris.push_back(Debris(enemy[j].getPoint(), Velocity(1, -1), 2));
						debris.push_back(Debris(enemy[j].getPoint(), Velocity(-1, 1), 2));
						debris.push_back(Debris(enemy[j].getPoint(), Velocity(-1, -1), 2));
					}
				}
			}
		}
	}
	/**********************************************************/
	

	/***********************************************************
	* Did we crash into the UFO?
	* we should take damage but we should also bounce off
	*************************************************************/
	if (ufo.isAlive() && ship.isAlive())
	{
		if (getClosestDistance(ship, ufo) < 100)
		{
			//ship.setAlive(false);
			ship.hit();
			//std::cout << "old velocity " << ship.getVelocity().getDx() << ", " << ship.getVelocity().getDy() << std::endl;
			Velocity vel(ship.getVelocity().getDx() * -0.25, ship.getVelocity().getDy() * -0.25);
			ship.setVelocity(vel);
			//std::cout << "vel " << vel.getDx() << ", " << vel.getDy() << std::endl;
			//std::cout << "new velocity " << ship.getVelocity().getDx() << ", " << ship.getVelocity().getDy() << std::endl;
			debris.push_back(Debris(ship.getPoint(), Velocity(-1, 0), 1));
			debris.push_back(Debris(ship.getPoint(), Velocity(1, 0), 1));
			debris.push_back(Debris(ship.getPoint(), Velocity(0, 1), 1));
			debris.push_back(Debris(ship.getPoint(), Velocity(0, -1), 1));
		}
	}
	/************************************************************/

	/***********************************************************
	* Did we crash into an enemy ship?
	* we should both explode!
	*************************************************************/
	for (int j = 0; j < enemy.size(); j++)
	{
		if (enemy[j].isAlive() && ship.isAlive())
		{
			if (getClosestDistance(ship, enemy[j]) < 5)
			{
				//enemy[j].hit();
				enemy[j].setAlive(false);
				ship.setAlive(false);

				debris.push_back(Debris(ship.getPoint(), Velocity(-1, 0), 1));
				debris.push_back(Debris(ship.getPoint(), Velocity(1, 0), 1));
				debris.push_back(Debris(ship.getPoint(), Velocity(0, 1), 1));
				debris.push_back(Debris(ship.getPoint(), Velocity(0, -1), 1));


				score += 4;

				if (j % 2 == 0)
				{
					debris.push_back(Debris(enemy[j].getPoint(), Velocity(-1, 0), 2));
					debris.push_back(Debris(enemy[j].getPoint(), Velocity(1, 0), 2));
					debris.push_back(Debris(enemy[j].getPoint(), Velocity(0, 1), 2));
					debris.push_back(Debris(enemy[j].getPoint(), Velocity(0, -1), 2));
				}
				else
				{
					debris.push_back(Debris(enemy[j].getPoint(), Velocity(1, 1), 2));
					debris.push_back(Debris(enemy[j].getPoint(), Velocity(1, -1), 2));
					debris.push_back(Debris(enemy[j].getPoint(), Velocity(-1, 1), 2));
					debris.push_back(Debris(enemy[j].getPoint(), Velocity(-1, -1), 2));
				}
			}
		}
	}
	/**************************************************************/
}

/*****************************************************************
* CLEAN UP ZOMBIES
* we check each vector for dead objects and then erase them.
*****************************************************************/
void Game::cleanUpZombies()
{
	// asteroids
	vector<Rocks*>::iterator rockIt = rocks.begin();
	while (rockIt != rocks.end())
	{
		Rocks * b = *rockIt;
		if (!b->isAlive())
		{
			rockIt = rocks.erase(rockIt);
		}
		else
		{
			rockIt++;
		}
	}
	
	// our bullets
	vector<Bullet>::iterator bulletIt = bullets.begin();
	while (bulletIt != bullets.end())
	{
		Bullet bull = *bulletIt;
		if (!bull.isAlive())
		{
			bulletIt = bullets.erase(bulletIt);
		}
		else
		{
			bulletIt++;
		}
	}

	// enemy bullets
	vector<Bullet>::iterator ebulletIt = ebullets.begin();
	while (ebulletIt != ebullets.end())
	{
		Bullet bull = *ebulletIt;
		if (!bull.isAlive())
		{
			ebulletIt = ebullets.erase(ebulletIt);
		}
		else
		{
			ebulletIt++;
		}
	}

	// enemy ships
	vector<Enemy>::iterator eIt = enemy.begin();
	while (eIt != enemy.end())
	{
		Enemy en = *eIt;
		if (!en.isAlive())
		{
			eIt = enemy.erase(eIt);
		}
		else
		{
			eIt++;
		}
	}

	// debris
	vector<Debris>::iterator dIt = debris.begin();
	while (dIt != debris.end())
	{
		Debris de = *dIt;
		if (!de.isAlive())
		{
			dIt = debris.erase(dIt);
		}
		else
		{
			dIt++;
		}
	}
}

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/
float Game :: getClosestDistance(const FlyingObject &obj1,
				 const FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}
