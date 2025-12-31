#include "Shape.h"
Shape::Shape()
{
	x = rand() % 800 + 5;
	y = rand() % 800 + 5;
	speedX = static_cast<double>(rand()) / RAND_MAX * 2.0 - 1.0;
	speedY = static_cast<double>(rand()) / RAND_MAX * 2.0 - 1.0;
	color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
}
void Shape::setX(double x)
{
	this->x = x;
}

void Shape::setY(double y)
{
	this->y = y;
}

double Shape::getX()
{
	return x;
}

double Shape::getY()
{
	return y;
}
