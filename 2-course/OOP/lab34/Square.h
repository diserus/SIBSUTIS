#pragma once
#include "Line.h"
class Square:public Line

{
private:
	sf::RectangleShape square;
protected:
	double width;
	double height;
	double area;
	double perimeter;
public:
	Square();
	Square(sf::RenderWindow *window);
	double getArea();
	double getPerimeter();
	void printArea();
	void printPerimeter();
	void draw();
	void moveStraight();
	void moveRotate();
};

