#ifndef VELOCITY_H
#define VELOCITY_H

class Velocity
{
	private:
		float dx;
		float dy;
	public:
		Velocity();
		Velocity(float dx, float dy);
		float getDx() {return dx;}
		float getDy() {return dy;}
		void setDx(float dx) {this->dx = dx;}
		void setDy(float dy) {this->dy = dy;}
};


#endif /* velocity_h */
