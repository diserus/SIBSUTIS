#pragma once
#include "Circle.h"
class Ellipse:public Circle
{
private:
	sf::CircleShape ellipse;
	int scaleX;
	int scaleY;
public: 
	Ellipse();
	Ellipse(sf::RenderWindow *window);
	void draw();
	void moveStraight();
	void moveRotate();
	void perimeter() override;
};
