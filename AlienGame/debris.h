#ifndef DEBRIS_H
#define DEBRIS_H

#include "flyingObject.h"

class Debris : public FlyingObject
{
public:
	Debris(Point point, Velocity velocity, int type)
	{
		this->point = point;
		this->velocity = velocity;
		life = 0;
		this->type = type;
	}

	void draw()
	{
		if (type == 1)
			drawBlueDot(point);
		else if (type == 2)
			drawGreenDot(point);
		else if (type == 3)
			drawDot(point);
	}

	void advance()
	{
		life++;
		if (life == 20)
			setAlive(false);

		point.addX(velocity.getDx());
		point.addY(velocity.getDy());
	}

private:
	float angle;
	int life;
	int type;
};

#endif