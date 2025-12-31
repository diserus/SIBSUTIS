//#include <SFML/Graphics.hpp>
//#include "tPoint.h"
//#include <vector>
//int main()
//{
//    srand(time(0));
//    int screenWidth = 800;
//    int screenHeight = 800;
//    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML works!");
//    std::vector<tPoint> points(100);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        for (int i = 0; i<100; i++)
//        {
//            points[i].moveRand(screenWidth, screenHeight);
//            sf::CircleShape circle;
//            circle.setPosition(points[i].getX(), points[i].getY());
//            circle.setFillColor(points[i].getColor());
//            circle.setRadius(5);
//            window.draw(circle);
//        }
//        window.display();
//    }
//
//    return 0;
//}

#include "Shape.h"
#include "Line.h"
#include "Square.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Ellipse.h"
#include <vector>
#include <iostream>
int main()
{
    srand(time(0));
    int screenWidth = 800;
    int screenHeight = 800;
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML works!");
    Line line(&window);
    Square sq(&window);
    Rectangle rect(&window);
    Circle circle(&window);
    Ellipse ellipse(&window);
    line.printLength();
    sq.printPerimeter();
    sq.printArea();
    rect.printPerimeter();
    rect.printArea();
    std::vector<Rectangle> rectangles(3);
    for (int i = 0; i < rectangles.size(); i++)
    {
        rectangles[i] = Rectangle(&window, rand()%screenWidth+1, rand()%screenHeight+1, rand()%screenWidth+1, rand()%screenHeight+1);
        rectangles[i].printArea();
        rectangles[i].printPerimeter();
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        sq.moveStraight();
        rect.moveStraight();
        line.moveStraight();
        circle.moveStraight();
        ellipse.moveStraight();
        
       /* sq.moveRotate();
        rect.moveRotate();
        line.moveRotate();
        ellipse.moveRotate();*/

        sq.draw();
        rect.draw();
        line.draw();
        circle.draw();
        ellipse.draw();
        
        window.display();
    }

    return 0;
}