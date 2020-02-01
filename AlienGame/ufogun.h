#ifndef UFOGUN_H
#define UFOGUN_H

#include "flyingObject.h"
#include "uiDraw.h"
#include <vector>
#include "bullet.h"
#include "ship.h"

#define LIFE 10

class UFOGun : public FlyingObject
{
public:
	UFOGun()
	{

	}
	UFOGun(Point point, Point ufoPt)
	{
		this->point = point;
		alive = true;
		count = 0;

		float ufoX = ufoPt.getX();
		float ufoY = ufoPt.getY();
		float difx = ufoX - point.getX();
		float dify = ufoY - point.getY();

		angle = atan2(difx, dify) * 180 / M_PI;
		angle *= -1;
		origAngle = angle;

		hits = 0;
	}

	void draw();
	
	void hit()
	{
		hits++;
		if (hits == LIFE)
		{
			setAlive(false);
		}
	}

	void advance(float dx, float dy);
	

	void advance(float dx, float dy, Ship ship);
	

	void eraseBullets()
	{
		std::vector<Bullet>::iterator bulletIt = bullets.begin();
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
	}
	std::vector <Bullet> bullets;
private:
	float angle;
	float origAngle;
	int count;
	int hits;
};

#endif
