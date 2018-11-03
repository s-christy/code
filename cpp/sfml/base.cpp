//g++ base.cpp -lsfml-graphics -lsfml-window -lsfml-system;./a.out;rm a.out
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <string>


/**
 *
 * This is an example
 *
 */
int main(){

	//Init window
	sf::RenderWindow window(sf::VideoMode(100,100),"Title");
	window.setFramerateLimit(60);

	//Create the circle
	sf::RectangleShape shape(sf::Vector2f(10,10));
	shape.move(50,50);
	shape.setFillColor(sf::Color::Green);

	//Create the text
	sf::Text text;
	sf::Font font;
	font.loadFromFile("/usr/share/fonts/truetype/lato/Lato-Regular.ttf");
	text.setFont(font);
	text.setCharacterSize(12);
	text.setFillColor(sf::Color::White);
	text.move(10,10);

	//Main loop
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type==sf::Event::Closed){
				window.close();
			}
		}

		//Handle events
		float speed=2*M_PI;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))shape.move(-speed,0);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))shape.move(speed,0);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))shape.move(0,-speed);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))shape.move(0,speed);
		if(event.key.code=='q')exit(0);

		//Update the text
		text.setString("[ "+
			std::to_string(shape.getPosition().x)+", "+
			std::to_string(shape.getPosition().y)+" ]"
		);

		//Draw everything again
		window.clear();
		window.draw(shape);
		window.draw(text);
		window.display();
	}

	return 0;
}
