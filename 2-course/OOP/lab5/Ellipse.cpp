#include "Ellipse.h"
Ellipse::Ellipse()
{
	scaleX = rand() % 5 + 1;
	scaleY = rand() % 5 + 1;
}

Ellipse::Ellipse(sf::RenderWindow *window)
{
	this->window = window;
	scaleX = rand() % 5 + 1;
	scaleY = rand() % 5 + 1;
}

void Ellipse::draw()
{
	ellipse.setPosition(x,y);
	ellipse.setRadius(radius);
	ellipse.setFillColor(color);
	ellipse.setScale(scaleX, scaleY);
	this->window->draw(ellipse);
}
void Ellipse::moveStraight()
{
	x = x + speedX;
	y = y + speedY;
	double screenWidth = window->getSize().x;
	double screenHeight = window->getSize().y;
	if (x > screenWidth - radius*scaleX || x - radius*scaleX < 0)
	{
		speedX = -speedX;
	}
	if (y > screenHeight - radius*scaleY || y - radius*scaleY < 0)
	{
		speedY = -speedY;
	}


}
void Ellipse::moveRotate()
{
	ellipse.setOrigin(ellipse.getOrigin().x / 2, ellipse.getOrigin().y / 2);
	ellipse.rotate(0.1);
}

void Ellipse::perimeter()
{
	std::cout << "Perimeter Ellipse is " << 2 * 3.1415 * sqrt((pow(radius * 2 * scaleY, 2) + pow(radius * 2 * scaleX, 2)) / 8) << "\n";
}