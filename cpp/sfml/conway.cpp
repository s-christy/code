//for i in {1..10};do echo;done;g++ conway.cpp -Wall -lsfml-graphics -lsfml-window -lsfml-system;./a.out;rm a.out

#include <SFML/Graphics.hpp>

#define WIDTH 1920
#define HEIGHT 1080
#define CELLSIZE 10

class Board{
public:

sf::Color black=sf::Color(20,20,20,255);
sf::Color white=sf::Color::White;
unsigned int width;
unsigned int height;
std::vector<sf::Color> board;
sf::RectangleShape cell=
	sf::RectangleShape(sf::Vector2f(CELLSIZE-1,CELLSIZE-1));

Board(unsigned int width,unsigned int height){
	srand(clock());
	this->width=width;
	this->height=height;
	for(unsigned int i=0;i<width*height;i++){
		if(random()%2){
			board.push_back(black);
		}else{
			board.push_back(white);
		}
	}
}

sf::Color getCellColor(unsigned int x,unsigned int y,std::vector<sf::Color>& b){
	if(x>width)return black;
	if(y>height)return black;
	if(x<0)return black;
	if(y<0)return black;
	return b[x+width*y];
}

int getNeighbors(unsigned int x,unsigned int y,std::vector<sf::Color>& b){
	int ret=0;
	if(getCellColor(x-1,y-1,b)==white)ret++;
	if(getCellColor(x-1,y+0,b)==white)ret++;
	if(getCellColor(x-1,y+1,b)==white)ret++;
	if(getCellColor(x+0,y-1,b)==white)ret++;
	if(getCellColor(x+0,y+1,b)==white)ret++;
	if(getCellColor(x+1,y-1,b)==white)ret++;
	if(getCellColor(x+1,y+0,b)==white)ret++;
	if(getCellColor(x+1,y+1,b)==white)ret++;
	return ret;
}

void simulate(){
	std::vector<sf::Color> backBoard;
	for(unsigned int i=0;i<board.size();i++){
		backBoard.push_back(board[i]);
	}
	for(unsigned int x=0;x<width;x++){
		for(unsigned int y=0;y<height;y++){
			if(getCellColor(x,y,backBoard)==white){
				if(getNeighbors(x,y,backBoard) <2)board[x+y*width]=black;
				if(getNeighbors(x,y,backBoard)==2)board[x+y*width]=white;
				if(getNeighbors(x,y,backBoard)==3)board[x+y*width]=white;
				if(getNeighbors(x,y,backBoard) >3)board[x+y*width]=black;
			}else{
				if(getNeighbors(x,y,backBoard)==3)board[x+y*width]=white;
			}
		}
	}
}

void display(sf::RenderWindow& window){
	for(unsigned int x=0;x<width;x++){
		for(unsigned int y=0;y<height;y++){
			cell.setPosition(1+x*CELLSIZE,1+y*CELLSIZE);
			cell.setFillColor(board[x+y*width]);
			window.draw(cell);
		}
	}
}
};

int main(){

	//Init window
	sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"Conway");
	window.setFramerateLimit(60);

	//Create the board
	Board b(WIDTH/CELLSIZE-1,HEIGHT/CELLSIZE-1);

	//Main loop
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type==sf::Event::Closed)
				window.close();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))exit(0);

		//Draw to the window
		window.clear();
		b.simulate();
		b.display(window);
		window.display();
	}

	return 0;
}

