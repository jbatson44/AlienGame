#include "rocks.h"

void Rocks::advance()
{
	point.addX(velocity.getDx());
	point.addY(velocity.getDy());

	if (point.getX() > 300)
		point.setX(-300);
	if (point.getX() < -300)
		point.setX(300);
	if (point.getY() < -300)
		point.setY(300);
	if (point.getY() > 300)
		point.setY(-300);
}

BigRock::BigRock()
{
	point.setY(random(-200, 200));
	int x = random(0, 2);
	if (x == 1)
		point.setX(200);
	else
		point.setX(-200);

	angle = random(0, 360);

	float dy = 1 * (-cos(M_PI / 180.0 * angle));
	float dx = 1 * (sin(M_PI / 180.0 * angle));

	velocity.setDx(dx);
	velocity.setDy(dy);

	rotation = 0;
}

MediumRock::MediumRock()
{
	point.setY(random(-200, 200));
	int x = random(0, 2);
	if (x == 1)
		point.setX(200);
	else
		point.setX(-200);

	angle = random(0, 360);

	float dy = 1 * (-cos(M_PI / 180.0 * angle));
	float dx = 1 * (sin(M_PI / 180.0 * angle));

	velocity.setDx(dx);
	velocity.setDy(dy);

	rotation = 0;
}

MediumRock::MediumRock(Point pt, Velocity vel, int y)
{
	point.setX(pt.getX());
	point.setY(pt.getY());
	velocity.setDx(vel.getDx());
	velocity.setDy(vel.getDy() + y);
}

SmallRock::SmallRock()
{
	point.setY(random(-200, 200));
	int x = random(0, 2);
	if (x == 1)
		point.setX(200);
	else
		point.setX(-200);

	angle = random(0, 360);

	float dy = 1 * (-cos(M_PI / 180.0 * angle));
	float dx = 1 * (sin(M_PI / 180.0 * angle));

	velocity.setDx(dx);
	velocity.setDy(dy);

	rotation = 0;
}

SmallRock::SmallRock(Point pt, Velocity vel, int x)
{
	point.setX(pt.getX());
	point.setY(pt.getY());
	velocity.setDx(vel.getDx() + x);
	velocity.setDy(vel.getDy());
}