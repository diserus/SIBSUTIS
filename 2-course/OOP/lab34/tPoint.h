#include <SFML/Graphics.hpp>
#pragma once
class tPoint
{
private:
	double x;
	double y;
	double speedX;
	double speedY;
	sf::Color color;
public:
	tPoint();
	tPoint(double x, double y, sf::Color);
	double getX();
	double getY();
	sf::Color getColor();
	void moveDefault(int width,int height);
	void moveRand(int width, int height);
};

