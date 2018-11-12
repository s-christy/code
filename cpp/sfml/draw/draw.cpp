//for i in {1..10};do echo;done;g++ draw.cpp -lsfml-graphics -lsfml-window -lsfml-system;./a.out;rm a.out
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
int x,y;
sf::Texture image;
sf::Sprite sprite;
Layer(int x, int y){
	this->x=x;
	this->y=y;

	sf::RenderTexture layer;
	layer.create(WIDTH,HEIGHT);
	image.loadFromFile("test.jpg");
	sprite.setTexture(image);
	sprite.move(x,y);
}
sf::Sprite getSprite(){
	return sprite;
}
};

class DrawLayer{
public:
sf::Sprite sprite;
int x,y;
sf::RenderTexture layer;
DrawLayer(int x=0, int y=0){
	this->x=x;
	this->y=y;
	layer.create(WIDTH,HEIGHT);
}
sf::Sprite getSprite(){
	layer.display();
	const sf::Texture& texture=layer.getTexture();
	sprite=sf::Sprite(texture);
	sprite.setPosition(x,y);
	return sprite;
}
};

int main(){

	//Init window
	sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"Title");
	window.setFramerateLimit(60);
	sf::Vector2i lastMouseXY=sf::Mouse::getPosition(window);

	Layer backLayer(299,62);

	//Create a layer to be rendered on top of the window.
	DrawLayer frontLayer;

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
			if(mouseXY.x!=lastMouseXY.x or mouseXY.y!=lastMouseXY.y){
				sf::Vector2i a=sf::Vector2i(mouseXY.x-frontLayer.x,mouseXY.y-frontLayer.y);
				sf::Vector2i b=sf::Vector2i(lastMouseXY.x-frontLayer.x,lastMouseXY.y-frontLayer.y);
				drawLine(a,b,1,frontLayer.layer,penSprite);
			}
			lastMouseXY=mouseXY;
		}else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			sf::Vector2i mouseXY=sf::Mouse::getPosition(window);
			float dx=mouseXY.x-lastMouseXY.x;
			float dy=mouseXY.y-lastMouseXY.y;
			backLayer.sprite.move(dx,dy);
			frontLayer.x+=dx;
			frontLayer.y+=dy;
			//std::cout<<backLayer.sprite.getPosition().x<<' ';
			//std::cout<<backLayer.sprite.getPosition().y<<'\n';
			lastMouseXY=mouseXY;
		}else{
			sf::Vector2i mouseXY=sf::Mouse::getPosition(window);
			lastMouseXY=mouseXY;
		}

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

