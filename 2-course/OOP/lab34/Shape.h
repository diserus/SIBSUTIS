#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
class Shape
{
private:
	sf::Vertex point;
protected:
	double x;
	double y;
	double speedX;
	double speedY;
	double rotationAngle;
	sf::Color color;
	sf::RenderWindow* window;
public:
	Shape();
	void setX(double x);
	void setY(double y);
	double getX();
	double getY();
};

