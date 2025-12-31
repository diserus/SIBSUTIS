#pragma once
#include "Shape.h"
class Line:public Shape
{
private:
	sf::ConvexShape line;
	double lineLength;
	static int created;
	static int existing;
protected:
	double x2;
	double y2;
public:
	Line();
	Line(sf::RenderWindow* window);
	~Line();
	void setX2(double x2);
	void setY2(double y2);
	double getX2();
	double getY2();
	void printLength();
	double length();
	void draw();
	void moveStraight();
	void moveRotate();
	void perimeter() override;
	static void printCountObjects();
};

