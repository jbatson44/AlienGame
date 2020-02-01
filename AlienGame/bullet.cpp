#include "bullet.h"

void Bullet::advance()
{
	point.addX(velocity.getDx());
	point.addY(velocity.getDy());

	/*if (point.getX() > 200)
		point.setX(-200);
	if (point.getX() < -200)
		point.setX(200);
	if (point.getY() < -200)
		point.setY(200);
	if (point.getY() > 200)
		point.setY(-200);*/

	life++;
	if (life == 40)
		alive = false;
	//std::cout << "alive " << life << std::endl;
}