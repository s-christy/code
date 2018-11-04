//g++ base.cpp -lsfml-graphics -lsfml-window -lsfml-system;./a.out;rm a.out
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <string>

#define WIDTH 1920
#define HEIGHT 1080

/**
 *
 * TODO:
 * Draw the user's brush strokes to a "layer" buffer using CircleShapes,
 * destroy the CircleShapes, but save the buffer and draw it to the screen.
 *
 */

/**
 *
 * This is an example
 *
 */
int main(){

	//Init window
	sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"Title");
	window.setFramerateLimit(60);

	//Create the shape
	sf::RectangleShape shape(sf::Vector2f(10,10));

	shape.setOrigin(
		shape.getLocalBounds().width/2,
		shape.getLocalBounds().height/2
	);

	shape.move(50,50);
	shape.setFillColor(sf::Color::Green);

	//Create a layer to be rendered on top of the window.
	sf::RenderTexture layer1;
	layer1.create(WIDTH,HEIGHT);

	//create the triangle
	sf::VertexArray triangle(sf::Triangles,3);
	triangle[0].position=sf::Vector2f(110,110);
	triangle[1].position=sf::Vector2f(200,110);
	triangle[2].position=sf::Vector2f(200,200);
	triangle[0].color=sf::Color::Red;
	triangle[1].color=sf::Color::Green;
	triangle[2].color=sf::Color::Blue;

	//Create the text
	sf::Text text;
	sf::Font font;
	font.loadFromFile("/usr/share/fonts/truetype/lato/Lato-Regular.ttf");
	text.setFont(font);
	text.setCharacterSize(12);
	text.setFillColor(sf::Color(200,200,200,255));
	text.move(10,10);

	//Main loop
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type==sf::Event::Closed){
				window.close();
			}
		}

		shape.rotate(10);

		//Handle keyboard events
		float speed=2*M_PI;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))shape.move(-speed,0);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))shape.move(speed,0);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))shape.move(0,-speed);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))shape.move(0,speed);
		if(event.key.code=='q')exit(0);
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){

			//Update the text
			text.setString("[ "+
				std::to_string(sf::Mouse::getPosition(window).x)+", "+
				std::to_string(sf::Mouse::getPosition(window).y)+" ]"
			);
		}

		//Draw to the layer
		layer1.clear(sf::Color(0,0,0,0));
		//layer1.draw(shape);
		layer1.display();
		const sf::Texture& texture=layer1.getTexture();
		sf::Sprite layer(texture);

		//Draw to the window
		window.clear();
		window.draw(triangle);
		window.draw(text);
		window.draw(shape);
		window.draw(layer);
		window.display();
	}

	return 0;
}
