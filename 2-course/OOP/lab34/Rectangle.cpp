#include "Rectangle.h"

Rectangle::Rectangle()
{

}
Rectangle::Rectangle(sf::RenderWindow *window)
{
	height = rand() % 200 + 50;
	width = rand() % 200 + 50;
	this->window = window;
}
Rectangle::Rectangle(sf::RenderWindow* window, double x, double y, double x2, double y2)
{
	height = rand() % 200 + 50;
	width = rand() % 200 + 50;
	this->x = x;
	this->y = y;
	this->y2 = y2;
	this->x2 = x2;
	this->window = window;
}
void Rectangle::draw()
{
	rectangle.setPosition(std::min(x, x2), std::min(y, y2));
	rectangle.setFillColor(color);
	rectangle.setSize(sf::Vector2f(width, height));
	this->window->draw(rectangle);
}
void Rectangle::moveRotate()
{
	rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);
	rectangle.rotate(0.1);
}

void Rectangle::moveStraight()
{
	x = x + speedX;
	y = y + speedY;
	x2 = x2 + speedX;
	y2 = y2 + speedY;
	double screenWidth = window->getSize().x;
	double screenHeight = window->getSize().y;
	if (x < 0 || x2 > screenWidth) {
		speedX = -speedX; 
	}
	if (y < 0 || y2 > screenHeight) {
		speedY = -speedY; 
	}

	if (x < 0) {
		x = 0;
		x2 = x + width;
	}
	if (x2 > screenWidth) {
		x2 = screenWidth;
		x = x2 - width; 
	}
	if (y < 0) {
		y = 0;
		y2 = y + height; 
	}
	if (y2 > screenHeight) {
		y2 = screenHeight;
		y = y2 - height; 
	}

}