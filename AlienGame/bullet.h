#ifndef BULLET_H
#define BULLET_H

#include "velocity.h"
#include "point.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "uiDraw.h"
#include "flyingObject.h"

class Bullet : public FlyingObject
{
	public:
		Bullet() : angle(0), life(0), evil(false) {}
		Bullet(Point pt, Velocity vel, float a, bool bad)
		{
			angle = a;

			float dy = 5 * (-cos(M_PI / 180.0 * angle));
			float dx = 5 * (sin(M_PI / 180.0 * angle));

			dy *= -1;
			dx *= -1;

			point.setX(pt.getX());
			point.setY(pt.getY());
			velocity.setDx(vel.getDx() + dx);
			velocity.setDy(vel.getDy() + dy);
			
			evil = bad;
		
			life = 0;
		}
		void advance();
		
		void draw()
		{
			if (evil == true)
				drawGreenDot(point);
			else
				drawRedDot(point);
		}
		
	private:
		//Velocity velocity;
		//Point point;
		float angle;
		int life;
		//bool alive;
		bool evil;
};

#endif
