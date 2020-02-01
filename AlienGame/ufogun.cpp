#include "ufogun.h"

void UFOGun:: draw()
{
	if (isAlive())
	{
		if (hits < LIFE / 2)
		{
			drawGreenCircle(point, 8);
		}
		else
		{
			drawRedCircle(point, 8);
		}

		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i].isAlive())
				bullets[i].draw();
		}
	}
	else
	{
		Point nPt(point.getX(), point.getY() + 10);
		drawFire(nPt, origAngle);
	}
}

\
void UFOGun::advance(float dx, float dy)
{
	point.addX(dx);
	point.addY(dy);
	count++;
	if (count % 20 == 0)
	{
		if (isAlive())
		{
			//bullets.push_back(Bullet(point, Velocity(0, 0), origAngle + 180, true));
		}
		//std::cout << "angle: " << angle << std::endl;

	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			bullets[i].advance();
		}
	}

	eraseBullets();
}

void UFOGun::advance(float dx, float dy, Ship ship)
{

	float shipX = ship.getPoint().getX();
	float shipY = ship.getPoint().getY();
	float difx = shipX - point.getX();
	float dify = shipY - point.getY();

	angle = atan2(difx, dify) * 180 / M_PI;
	angle *= -1;
	//std::cout << "angle1: " << angle << std::endl;


	point.addX(dx);
	point.addY(dy);
	count++;
	if (count % 20 == 0)
	{
		if (isAlive())
		{
			bullets.push_back(Bullet(point, Velocity(0, 0), angle, true));
		}
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			bullets[i].advance();
		}
	}

	eraseBullets();
}