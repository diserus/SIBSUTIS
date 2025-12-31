#pragma once
#include "Line.h"
class Square:public Line

{
private:
	sf::RectangleShape square;
	static int existing;
	static int created;
protected:
	double width;
	double height;
	double area;
	double perimetr;
public:
	Square();
	Square(sf::RenderWindow *window);
	~Square();
	double getArea();
	void printArea();
	void draw();
	void moveStraight();
	void moveRotate();
	void perimeter() override;
};

