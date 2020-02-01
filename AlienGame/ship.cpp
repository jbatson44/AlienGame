#include "ship.h"

void Ship :: advance()
{
	point.addY(velocity.getDy());
	point.addX(velocity.getDx());

	if (point.getX() > 300)
	{
		point.setX(-300);
		//setAlive(false);
	}
	if (point.getX() < -300)
	{
		point.setX(300);
		//setAlive(false);
	}
	if (point.getY() < -300)
	{
		point.setY(300);
		//velocity.setDx(velocity.getDx() * -0.5);
		//velocity.setDy(velocity.getDy() * -0.5);
		//setAlive(false);
	}
	if (point.getY() > 300)
	{
		point.setY(-300);
		//setAlive(false);
	}
	thrust = false;

	
}

void Ship :: move()
{
	//std::cout << "ships point in class: " << point << std::endl;
	//std::cout << "ships getPoint in class: " << getPoint() << std::endl;
	thrust = true;
	float dy = THRUST_AMOUNT * (-cos(M_PI / 180.0 * angle));
	float dx = THRUST_AMOUNT * (sin(M_PI / 180.0 * angle));

	dy *= -1;
	dx *= -1;
	velocity.setDx(velocity.getDx() + dx);
	velocity.setDy(velocity.getDy() + dy);
}

void Ship::brakes()
{
	//thrust = true;
	if (velocity.getDx() != 0 || velocity.getDy() != 0)
	{
		float dy = THRUST_AMOUNT * (-cos(M_PI / 180.0 * (angle + 180)));
		float dx = THRUST_AMOUNT * (sin(M_PI / 180.0 * (angle + 180)));

		dy *= -1;
		dx *= -1;
		velocity.setDx(velocity.getDx() + dx);
		velocity.setDy(velocity.getDy() + dy);
	}
}