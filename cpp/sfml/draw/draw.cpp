//for i in {1..10};do echo;done;g++ draw.cpp -lsfml-graphics -lsfml-window -lsfml-system;./a.out;rm a.out
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <string>

#include "layer.hpp"
#include "line.hpp"
#include "pen.hpp"

/*
 *
 * TODO
 * Add widgets to control things like layer opacity and brush color/size
 *
 */

class Text{
public:
sf::Text text;
sf::Font font;
Text(std::string string,int x, int y){
	font.loadFromFile("/usr/share/fonts/truetype/lato/Lato-Regular.ttf");
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color(20,20,20,255));
	text.move(x,y);
	text.setString(string);
}
};

class UI{
public:
Layer l;
UI(){
}
sf::Sprite getSprite(){
	l.layer.clear(sf::Color(255,255,255,0));
	addRibbon();
	return l.getSprite();
}
void addRibbon(){
	sf::RectangleShape ribbon=sf::RectangleShape(sf::Vector2f(WIDTH,100));
	ribbon.setFillColor(sf::Color(50,50,50,255));
	l.layer.draw(ribbon);
	addButton("Test");
}
void addButton(std::string text){
	int x=10;
	int y=10;

	Text t=Text(text,x,y);
	sf::FloatRect bounds=t.text.getGlobalBounds();

	sf::RectangleShape button=sf::RectangleShape(sf::Vector2f(bounds.width,bounds.height));
	button.setPosition(x,y);
	button.setFillColor(sf::Color(255,255,255,255));

	l.layer.draw(button);
	l.layer.draw(t.text);

	//sf::Vector2i mouse=sf::Mouse::getPosition(window);
	//if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
	//	std::cout<<1;
	//}
}
};

class Mouse{
public:
sf::Vector2i prev;
sf::Vector2i next;
};

int main(){

	//init window
	sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"Title");
	window.setFramerateLimit(60);
	Mouse mouse;
	mouse.prev=sf::Mouse::getPosition(window);

	//create the layers
	Layer backLayer(299,62,"test.jpg");
	Layer frontLayer;
	UI ui();

	//create the pen sprite
	Pen pen(200,sf::Color(50,50,50,5));

	//main loop
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type==sf::Event::Closed){
				window.close();
			}
		}

		//handle mouse events
		mouse.next=sf::Mouse::getPosition(window);

		//when the LMB is pressed, draw with the pen object
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			if(mouse.next.x!=mouse.prev.x or mouse.next.y!=mouse.prev.y){
				sf::Vector2i a=sf::Vector2i(mouse.next.x-frontLayer.x,mouse.next.y-frontLayer.y);
				sf::Vector2i b=sf::Vector2i(mouse.prev.x-frontLayer.x,mouse.prev.y-frontLayer.y);
				drawLine(a,b,1,frontLayer.layer,pen.penSprite);
			}

		//when the LMB is pressed, pan the layers
		}else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			float dx=mouse.next.x-mouse.prev.x;
			float dy=mouse.next.y-mouse.prev.y;
			backLayer.move(dx,dy);
			frontLayer.move(dx,dy);
		}else{
		}
		mouse.prev=mouse.next;

		//handle keyboard events
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))exit(0);

		//draw to the window
		window.clear(sf::Color::White);

		//draw the layers
		window.draw(backLayer.getSprite());
		window.draw(frontLayer.getSprite());
		window.draw(ui.getSprite());

		window.display();
	}

	return 0;
}

