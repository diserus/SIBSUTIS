#pragma once
#include "Square.h"
class Rectangle:public Square
{
private:
	sf::RectangleShape rectangle;
public:
	Rectangle();
	Rectangle(sf::RenderWindow* window);
	Rectangle(sf::RenderWindow*window, double x,double y,double x2,double y2);
	void draw();
	void moveRotate();
	void moveStraight();
};

