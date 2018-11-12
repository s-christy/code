//g++ draw.cpp -lsfml-graphics -lsfml-window -lsfml-system;./a.out;rm a.out
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#include "line.hpp"

#define WIDTH 1920
#define HEIGHT 1080
#define BRUSHWIDTH 2

/*
 *
 * TODO
 * Make both layers instances of the same class.
 * Add widgets to control things like layer opacity and brush color/size
 *
 */

class Layer{
public:
Layer(){
	sf::RenderTexture layer;
	layer.create(WIDTH,HEIGHT);
	sf::Texture image;
	image.loadFromFile("test.jpg");
	sf::Sprite sprite;
	sprite.setTexture(image);
	sprite.move(299,62);
}
};

int main(){

	//Init window
	sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"Title");
	window.setFramerateLimit(60);
	sf::Vector2i lastMouseXY=sf::Mouse::getPosition(window);

	//Create a layer to be rendered on top of the window.
	sf::RenderTexture layer;
	layer.create(WIDTH,HEIGHT);

	//Create the image layer
	sf::Texture image;
	image.loadFromFile("test.jpg");
	sf::Sprite sprite;
	sprite.setTexture(image);
	sprite.move(299,62);

	//Create the pen sprite
	sf::RenderTexture pen;
	pen.create(BRUSHWIDTH*2,BRUSHWIDTH*2);
	sf::CircleShape brush;

	brush=sf::CircleShape(BRUSHWIDTH);
	brush.setFillColor(sf::Color(50,50,50,50));
	pen.draw(brush);

	pen.display();
	const sf::Texture& penTexture=pen.getTexture();
	sf::Sprite penSprite(penTexture);
	penSprite.setOrigin(
		brush.getLocalBounds().width/2,
		brush.getLocalBounds().height/2
	);

	//Main loop
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type==sf::Event::Closed){
				window.close();
			}
		}

		//handle mouse events
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			sf::Vector2i mouseXY=sf::Mouse::getPosition(window);
			if(mouseXY.x!=lastMouseXY.x or mouseXY.y!=lastMouseXY.y)
				drawLine(lastMouseXY,mouseXY,1,layer,penSprite);
			lastMouseXY=mouseXY;
		}else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			sf::Vector2i mouseXY=sf::Mouse::getPosition(window);
			float dx=mouseXY.x-lastMouseXY.x;
			float dy=mouseXY.y-lastMouseXY.y;
			sprite.move(dx,dy);
			std::cout<<sprite.getPosition().x<<' ';
			std::cout<<sprite.getPosition().y<<'\n';
			lastMouseXY=mouseXY;
		}else{
			sf::Vector2i mouseXY=sf::Mouse::getPosition(window);
			lastMouseXY=mouseXY;
		}

		//Handle keyboard events
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))exit(0);

		//Draw to the layer
		layer.display();
		const sf::Texture& texture=layer.getTexture();
		sf::Sprite layer(texture);

		//Draw to the window
		window.clear(sf::Color::White);

		window.draw(sprite);

		window.draw(layer);
		window.display();
	}

	return 0;
}

