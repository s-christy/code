//for i in {1..10};do echo;done;g++ draw.cpp -lsfml-graphics -lsfml-window -lsfml-system;./a.out;rm a.out
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <string>

#include "layer.h"
#include "line.hpp"
#include "pen.h"

/*
 *
 * TODO
 * Add widgets to control things like layer opacity and brush color/size
 *
 */

class Mouse{
public:
sf::Vector2i prev;
sf::Vector2i next;
};

int main(){

	//Init window
	sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"Title");
	window.setFramerateLimit(60);
	Mouse mouse;
	mouse.prev=sf::Mouse::getPosition(window);

	//Create the layers
	Layer backLayer(299,62,"test.jpg");
	Layer frontLayer;

	//Create the pen sprite
	Pen pen(200,sf::Color(50,50,50,5));

	//Main loop
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type==sf::Event::Closed){
				window.close();
			}
		}

		//handle mouse events
		mouse.next=sf::Mouse::getPosition(window);
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			if(mouse.next.x!=mouse.prev.x or mouse.next.y!=mouse.prev.y){
				sf::Vector2i a=sf::Vector2i(mouse.next.x-frontLayer.x,mouse.next.y-frontLayer.y);
				sf::Vector2i b=sf::Vector2i(mouse.prev.x-frontLayer.x,mouse.prev.y-frontLayer.y);
				drawLine(a,b,1,frontLayer.layer,pen.penSprite);
			}
		}else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			float dx=mouse.next.x-mouse.prev.x;
			float dy=mouse.next.y-mouse.prev.y;
			backLayer.move(dx,dy);
			frontLayer.move(dx,dy);
		}else{
		}
		mouse.prev=mouse.next;

		//Handle keyboard events
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))exit(0);

		//Draw to the window
		window.clear(sf::Color::White);

		window.draw(backLayer.getSprite());
		window.draw(frontLayer.getSprite());

		window.display();
	}

	return 0;
}

