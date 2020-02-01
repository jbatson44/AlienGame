#ifndef ROCKS_H
#define ROCKS_H

#include "flyingObject.h"
#include "velocity.h"
#include "point.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "uiDraw.h"

class Rocks : public FlyingObject
{
	public:
		Rocks()
		{
			
		}
		
		virtual void draw() = 0;

		virtual int getRadius() = 0;

		void advance();

		virtual void kill() = 0;



	private:
		
};

class BigRock : public Rocks
{
	public:
		BigRock();

		void draw()
		{
			rotation += 2;
			drawLargeAsteroid(point, rotation);
		}

		int getRadius() { return 15; }
		//void advance();

		
		void kill() { setAlive(false); }

	private:
		float angle;
		float rotation;
};

class MediumRock : public Rocks
{
public:
	MediumRock();
	MediumRock(Point pt, Velocity vel, int y);

	void draw()
	{
		rotation += 5;
		drawMediumAsteroid(point, rotation);
	}

	int getRadius() { return 8; }

	//void advance();


	void kill() { setAlive(false); }

private:
	float angle;
	float rotation;
};

class SmallRock : public Rocks
{
public:
	SmallRock();
	SmallRock(Point pt, Velocity vel, int x);

	void draw()
	{
		rotation += 10;
		drawSmallAsteroid(point, rotation);
	}

	int getRadius() { return 4; }
	//void advance();


	void kill() { setAlive(false); }

private:
	float angle;
	float rotation;
};

#endif
