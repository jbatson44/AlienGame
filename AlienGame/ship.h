#ifndef SHIP_H
#define SHIP_H

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT .1


#include "velocity.h"
#include "point.h"
#include "flyingObject.h"
#include "uiDraw.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "uiInteract.h"

class Ship : public FlyingObject
{
	public:
		Ship() : angle(0), thrust(false)
		{
			point.setX(0);
			point.setY(-200);
			velocity.setDx(0);
			velocity.setDy(0);
			hits = 10;
		}

		void advance();

		void move();

		void brakes();

		float getAngle() { return angle; }

		void draw()
		{
			drawShip(getPoint(), angle, thrust);
		}
		
		void turnLeft()
		{
			angle += ROTATE_AMOUNT;
			if (angle == 360)
				angle = 0;
		}

		void turnRight()
		{
			angle -= ROTATE_AMOUNT;
			if (angle == -1)
				angle = 359;
		}

		void kill()
		{
			setAlive(false);

		}

		void hit()
		{
			if (hits != 0)
			{
				hits--;
			}
			if (hits == 0)
			{
				kill();
			}
		}

		int numHits()
		{
			return hits;
		}
		
  
	private:
		bool alive;
		float angle;
		bool thrust;
		int hits;
};

#endif
