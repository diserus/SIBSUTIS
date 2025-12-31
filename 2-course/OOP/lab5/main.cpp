#include "Shape.h"
#include "Line.h"
#include "Square.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Ellipse.h"
#include <vector>
#include <iostream>
int Line::created = 0;
int Line::existing = 0;
int Square::created = 0;
int Square::existing = 0;
int Rectangle::created = 0;
int Rectangle::existing = 0;
int main()
{
    srand(time(0));
    int screenWidth = 800;
    int screenHeight = 800;
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML works!");
   
        Line lineDef;
        Line line(&window);
        Square squareDef;
        Square square(&window);
        Rectangle rectDef;
        Rectangle rect(&window);
    
    

    Rectangle::printCountObjects();
    Rectangle* pRect;
    std::cout << "\n\nAfter creating pointer: \n";
    Rectangle::printCountObjects();
    std::cout << "\n\nAfter creating dynamic object: \n";
    Rectangle* dynamicRect = new Rectangle;
    Rectangle::printCountObjects();
    
    Shape* shapes[4];
    shapes[0] = new Square;
    shapes[1] = new Rectangle;
    shapes[2] = new Circle;
    shapes[3] = new Ellipse;

    std::cout << "\n\nAfter creating dynamic array: \n";
    Rectangle::printCountObjects();

    for (int i = 0; i < 4; i++)
    {
        shapes[i]->perimeter();
        delete  shapes[i];
    }
    delete dynamicRect;
    
    Rectangle::printCountObjects();
    return 0;
}