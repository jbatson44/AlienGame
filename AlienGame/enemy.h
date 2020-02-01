#ifndef ENEMY_H
#define ENEMY_H

#define SPEED 1

#include "flyingObject.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "uiDraw.h"
#include "ship.h"

class Enemy : public FlyingObject
{
public:
	Enemy() : thrust(true), delay(0), hits(0)
	{
		point.setX(random(-200,200));
		float y = random(0, 2);
		if (y == 1)
		point.setY(200);
		else 
			point.setY(-200);
		
		//angle = random(0, 359);
		angle = 180;
		float dy = 0;// THRUST_AMOUNT * (-cos(M_PI / 180.0 * angle));
		float dx = 0;//THRUST_AMOUNT * (sin(M_PI / 180.0 * angle));

		dy *= -1;
		dx *= -1; 

		velocity.setDx(dx);
		velocity.setDy(dy);
		speed = 1;
	}
	Enemy(Point point)
	{
		delay = 0;
		hits = 0;
		thrust = true;
		this->point = point;

		angle = random(135, 225);
		//angle = 180;
		float dy = 0;// THRUST_AMOUNT * (-cos(M_PI / 180.0 * angle));
		float dx = 0;//THRUST_AMOUNT * (sin(M_PI / 180.0 * angle));

		dy *= -1;
		dx *= -1;

		velocity.setDx(dx);
		velocity.setDy(dy);
		speed = 1;
	}

	void draw()
	{
		drawEnemyShip(point, angle, thrust);
		//drawToughBird(point, 2, 0);
		//drawPolygon(point, 30, 3, angle+150);
	}

	void advance(Ship ship);
	void advance();

	void hit()
	{
		hits++;
		if (hits == 3)
			setAlive(false);
	}

	float getAngle() { return angle; }

	int getDelay() { return delay; }

	void turn() { angle -= 6; }

private:
	float angle;
	bool thrust;
	int delay;
	int hits;
	float speed;
};


#endif