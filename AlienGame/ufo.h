#ifndef UFO_H
#define UFO_H

#include "flyingObject.h"
#include "ufogun.h"

#define LIFE 10

class UFO : public FlyingObject
{
public:
	UFO() 
	{
		point.setX(-200);
		point.setY(200);
		count = 0;
		left = false;
		hits = 0;
		//alive = false;
		/*Point pt1(point.getX(), point.getY() - 108);
		gun1 = UFOGun(pt1, point);
		Point pt2(point.getX() - 80, point.getY() - 74);
		gun2 = UFOGun(pt2, point);
		Point pt3(point.getX() + 80, point.getY() - 74);
		gun3 = UFOGun(pt3, point);
		Point pt4(point.getX() - 42, point.getY() - 99);
		gun4 = UFOGun(pt4, point);
		Point pt5(point.getX() + 42, point.getY() - 99);
		gun5 = UFOGun(pt5, point);*/
	}

	void setCount(int c) {
		count = c;
	}
	void setLeft(bool l) {
		left = l;
	}
	void setHits(int h) {
		hits = h;
	}
	void draw()
	{
		if (hits > LIFE / 2)
		{
			drawUFO(point, 100, true);
		}
		else
		{
			drawUFO(point, 100, false);
		}
		/*gun1.draw();
		gun2.draw();
		gun3.draw();
		gun4.draw();
		gun5.draw();*/
	}

	void hit()
	{
		
		hits++;

		if (hits == LIFE)
		{
			setAlive(false);
		}
	}

	void advance()
	{
		count++;

		if (count < 400)
		{
			left = false;
		}
		else
		{
			left = true;
		}

		if (count == 800)
			count = 0;
		if (left)
		{
			//left = true;
			velocity.setDx(-1);
		}
		else
		{
			//left = false;
			velocity.setDx(1);
		}
		/*gun1.advance(velocity.getDx(), velocity.getDy());
		gun2.advance(velocity.getDx(), velocity.getDy());
		gun3.advance(velocity.getDx(), velocity.getDy());
		gun4.advance(velocity.getDx(), velocity.getDy());
		gun5.advance(velocity.getDx(), velocity.getDy());*/
		point.addX(velocity.getDx());
		point.addY(velocity.getDy());
	}

	//UFOGun gun1;
	//UFOGun gun2;
	//UFOGun gun3;
	//UFOGun gun4;
	//UFOGun gun5;
private:
	int count;
	bool left;
	int hits;

};

#endif
