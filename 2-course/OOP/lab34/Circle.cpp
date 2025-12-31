#include "Circle.h"

Circle::Circle()
{
	this->radius = rand() % 30 + 5;
}

Circle::Circle(sf::RenderWindow* window)
{
	this->window = window;
	this->radius = rand() % 50+10;
}
void Circle::draw()
{
	circle.setPosition(x, y);
	circle.setRadius(radius);
	circle.setFillColor(color);
	this->window->draw(circle);

}
void Circle::moveStraight()
{
	x = x + speedX;
	y = y + speedY;
	double screenWidth = window->getSize().x;
	double screenHeight = window->getSize().y;
	if (x > screenWidth-radius || x-radius  < 0)
	{
		speedX = -speedX;
	}
	if (y > screenHeight-radius || y-radius < 0)
	{
		speedY = -speedY;
	}

	
}