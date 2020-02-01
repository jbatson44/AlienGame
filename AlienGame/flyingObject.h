#ifndef FLYINGOBJECT_H
#define FLYINGOBJECT_H

#include "point.h"
#include "velocity.h"

class FlyingObject
{
	public:
		FlyingObject()
		{
			alive = true;
		}
 
		virtual void draw() = 0;

		Velocity getVelocity() const { return velocity; }
		void setVelocity(Velocity velocity) { this->velocity = velocity; }

		Point getPoint() const{ return point; }
		void setPoint(Point point) { this->point = point; }

		bool isAlive() { return alive; }
		void setAlive(bool alive) { this->alive = alive; }

		//float getAngle() { return angle; }

	protected:
		Velocity velocity;
		Point point;
		bool alive;
		float angle;
};

#endif
