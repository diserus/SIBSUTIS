#include "Square.h"
Square::Square()
{
	height = rand() % 200 + 50;
	width = height;
	existing++;
	created++;
}
Square::Square(sf::RenderWindow* window)
{
	height = rand() % 200 + 50;
	width = height;
	this->window = window;
	existing++;
	created++;
}
Square::~Square()
{
	existing--;
}
void Square::draw()
{
	square.setPosition(std::min(x, x2), std::min(y, y2));
	square.setFillColor(color);
	square.setSize(sf::Vector2f(width,height));
	this->window->draw(square);
}	
double Square::getArea()
{
	area = width * height;
	return area;
}
void Square::printArea()
{
	std::cout << "Area = " << getArea() << "\n";
}
void Square::moveStraight()
{
	x = x + speedX;
	y = y + speedY;
	x2 = x2 + speedX;
	y2 = y2 + speedY;
	double screenWidth = window->getSize().x;
	double screenHeight = window->getSize().y;
	if (x < 0 || x2 > screenWidth) {
		speedX = -speedX; 
	}
	if (y < 0 || y2 > screenHeight) {
		speedY = -speedY; 
	}

	if (x < 0) {
		x = 0;
		x2 = x + width; 
	}
	if (x2 > screenWidth) {
		x2 = screenWidth;
		x = x2 - width; 
	}
	if (y < 0) {
		y = 0;
		y2 = y + width; 
	}
	if (y2 > screenHeight) {
		y2 = screenHeight;
		y = y2 - width; 
	}

}
void Square::moveRotate()
{
	square.setOrigin(square.getSize().x/2,square.getSize().y/2);
	square.rotate(0.1);
}

void Square::perimeter()
{
	std::cout << "Perimeter Square is " << 4 * width << "\n";
}