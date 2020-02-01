#include "enemy.h"

void Enemy::advance()
{
	float dy = speed * (-cos(M_PI / 180.0 * angle));
	float dx = speed * (sin(M_PI / 180.0 * angle));

	dy *= -1;
	dx *= -1;

	velocity.setDx(velocity.getDx() + dx);
	velocity.setDy(velocity.getDy() + dy);

	velocity.setDx(dx);
	velocity.setDy(dy);

	point.addY(velocity.getDy());
	point.addX(velocity.getDx());

	if (point.getX() > 300)
		point.setX(-300);
	if (point.getX() < -300)
		point.setX(300);
	if (point.getY() < -300)
		point.setY(300);
	if (point.getY() > 300)
		point.setY(-300);

	delay++;
	//turn();
}

void Enemy::advance(Ship ship)
{
	float shipX = ship.getPoint().getX();
	float shipY = ship.getPoint().getY();
	float difx = shipX - point.getX();
	float dify = shipY - point.getY();

	angle = atan2(difx, dify) * 180 / M_PI;
	angle *= -1;
	//std::cout << angle << std::endl;

	//angle = answer;
	float dy = (speed + .2) * (-cos(M_PI / 180.0 * angle));
	float dx = (speed + .2) * (sin(M_PI / 180.0 * angle));

	dy *= -1;
	dx *= -1;

	velocity.setDx(velocity.getDx() + dx);
	velocity.setDy(velocity.getDy() + dy);

	velocity.setDx(dx);
	velocity.setDy(dy);

	point.addY(velocity.getDy());
	point.addX(velocity.getDx());
	//
	if (point.getX() > 300)
		point.setX(-300);
	if (point.getX() < -300)
		point.setX(300);
	if (point.getY() < -300)
		point.setY(300);
	if (point.getY() > 300)
		point.setY(-300);

	delay++;
	//turn();
}