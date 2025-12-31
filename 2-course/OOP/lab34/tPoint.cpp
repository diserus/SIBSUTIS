#include "tPoint.h"
#include <numbers>
tPoint::tPoint()
{
	x = rand() % 800+5;
	y = rand() % 800+5;
	color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
	speedX = static_cast<double>(rand()) / RAND_MAX * 2.0 - 1.0;
	speedY = static_cast<double>(rand()) / RAND_MAX * 2.0 - 1.0;
}
tPoint::tPoint(double x,double y, sf::Color color)
{
	this->x = x;
	this->y = y;
	this->color = color;
}
double tPoint::getX()
{
	return x;
}
double tPoint::getY()
{
	return y;
}
sf::Color tPoint::getColor()
{
	return color;
}

void tPoint::moveDefault(int width, int height)
{
	x = x + speedX;
	y = y + speedY;
	if (x > width-5 || x-5 < 0)
	{
		speedX = -speedX;
	}
	if (y > height-5 || y-5 < 0)
	{
		speedY = -speedY;
	}
}
void tPoint::moveRand(int width,int height)
{
	
	double angle= static_cast<double>(rand()) / RAND_MAX * (2*3.1415);
	speedX = cos(angle);
	speedY = sin(angle);
	x = x + speedX;
	y = y + speedY;
	if (x > width - 5 || x - 5 < 0)
	{
		speedX = -speedX;
		x = (x > width - 5) ? width - 5 : 5;
	}
	if (y > height - 5 || y - 5 < 0)
	{
		speedY = -speedY;
		y = (y >height - 5) ? height - 5 : 5;
	}
}