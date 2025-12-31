#pragma once
#include "Shape.h"
class Circle:public Shape
{
private:
	sf::CircleShape circle;
protected:
	double radius;
public:
	Circle();
	Circle(sf::RenderWindow* window);
	void draw();
	void moveStraight();
	void perimeter() override;
};

