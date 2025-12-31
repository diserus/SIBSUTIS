#include "Line.h"
Line::Line()
{
	x2 = rand() % 800 + 5;
	y2 = rand() % 800 + 5;
	if (x > x2) std::swap(x, x2);
	if (y > y2) std::swap(y, y2);
	created++;
	existing++;
}
Line::Line(sf::RenderWindow *window)
{
	x2 = rand() % 400 + 5;
	y2 = rand() % 400 + 5;
	this->window = window;
	if (x > x2) std::swap(x, x2);
	if (y > y2) std::swap(y, y2);
	created++;
	existing++;
}
Line::~Line()
{
	existing--;
}
void Line::setX2(double x2)
{
	this->x2 = x2;
}

void Line::setY2(double y2)
{
	this->y2 = y2;
}

double Line::getX2()
{
	return x2;
}

double Line::getY2()
{
	return y2;
}
double Line::length()
{
	lineLength = std::sqrt(std::pow(x2 - x,2) + std::pow(y2 - y,2));
	return lineLength;
}

void Line::printLength()
{
	std::cout << "Length of line: " <<  length()<< "\n";
}

void Line::draw()
{
	line.setPointCount(4);
	line.setPoint(0, sf::Vector2f(x, y));
	line.setPoint(1, sf::Vector2f(x2, y2));
	line.setPoint(2, sf::Vector2f(x2, y2+5));
	line.setPoint(3, sf::Vector2f(x, y+5));
	line.setFillColor(color);
	this->window->draw(line);
}
void Line::moveStraight()
{
	x = x + speedX;
	y = y + speedY;
	x2 = x2 + speedX;
	y2 = y2 + speedY;
	double screenWidth = window->getSize().x;
	double screenHeight = window->getSize().y;
	if (x < 0 || x2 > screenWidth) {
		speedX = -speedX; // ќтражение по оси X
	}
	if (y < 0 || y2 > screenHeight) {
		speedY = -speedY; // ќтражение по оси Y
	}

	// ќбновл€ем координаты в случае столкновени€
	if (x < 0) {
		x = 0;
		x2 = x + lineLength; // «десь замените квадратна€ƒлина на длину вашей стороны квадрата
	}
	if (x2 > screenWidth) {
		x2 = screenWidth;
		x = x2 - lineLength; // «десь замените квадратна€ƒлина на длину вашей стороны квадрата
	}
	if (y < 0) {
		y = 0;
		y2 = y + lineLength; // «десь замените квадратна€ƒлина на длину вашей стороны квадрата
	}
	if (y2 > screenHeight) {
		y2 = screenHeight;
		y = y2 - lineLength; // «десь замените квадратна€ƒлина на длину вашей стороны квадрата
	}

}
void Line::moveRotate()
{
	line.setPosition(x2 - x, y2 - y);
	line.setOrigin((x2+x)/2,(y2+y)/2);
	line.rotate(0.1);

}

void Line::perimeter()
{
	std::cout << "Perimeter Line is " << length() << "\n";
}
void Line::printCountObjects()
{
	std::cout << "Existing count: " << existing << "\n";
	std::cout << "Created count: " << created << "\n";
}