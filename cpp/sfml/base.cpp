//g++ base.cpp -lsfml-graphics -lsfml-window -lsfml-system;./a.out;rm a.out
#include <SFML/Graphics.hpp>
#include <iostream>

int main(){
	sf::RenderWindow window(sf::VideoMode(100,100),"Title");
	window.setFramerateLimit(60);

	sf::CircleShape shape(10.f);
	shape.setFillColor(sf::Color::Green);

	sf::Text text;
	sf::Font font;
	font.loadFromFile("/usr/share/fonts/truetype/lato/Lato-Regular.ttf");
	text.setFont(font);
	text.setString("9999");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.move(10,10);

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type==sf::Event::Closed){
				window.close();
			}
		}

		float speed=10;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))shape.move(-speed,0);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))shape.move(speed,0);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))shape.move(0,-speed);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))shape.move(0,speed);
		if(event.key.code=='q')exit(0);

		window.clear();
		window.draw(shape);
		window.draw(text);
		window.display();
	}

	return 0;
}
