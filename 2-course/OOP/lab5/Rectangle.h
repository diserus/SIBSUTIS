#pragma once
#include "Square.h"
class Rectangle:public Square
{
private:
	sf::RectangleShape rectangle;
	static int created;
	static int existing;
public:
	Rectangle();
	Rectangle(sf::RenderWindow* window);
	Rectangle(sf::RenderWindow*window, double x,double y,double x2,double y2);
	~Rectangle();
	void draw();
	void moveRotate();
	void moveStraight();
	void perimeter() override;
	static void printCountObjects();
};

