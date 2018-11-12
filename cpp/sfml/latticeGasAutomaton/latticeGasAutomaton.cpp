//for i in {1..10};do echo;done;g++ latticeGasAutomaton.cpp -Wall -lsfml-graphics -lsfml-window -lsfml-system;./a.out;rm a.out

#include <SFML/Graphics.hpp>
#include <iostream>

#define WIDTH 1920
#define HEIGHT 1080
#define CELLSIZE 10
#define BORDER 10

class Subject{
public:
sf::Color color;
unsigned int x,y;

Subject(sf::Color& color,unsigned int x, unsigned int y){
	this->color=color;
	this->x=x;
	this->y=y;
}

void goTo(unsigned int fx, unsigned int fy){
	if(x>fx)x--;
	if(y>fy)y--;
	if(x<fx)x++;
	if(y<fy)y++;
}

};

class Board{
public:

sf::Color black=sf::Color(20,20,20,255);
sf::Color white=sf::Color::White;
sf::Color blue=sf::Color::Blue;
sf::Color red=sf::Color::Red;
sf::Color green=sf::Color::Green;

std::vector<Subject> subjects;

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
		board.push_back(black);
	}

	unsigned int peds=width*height*.02;
	unsigned int cops=1;
	unsigned int bads=4;

	std::vector<unsigned int> used;
	for(unsigned int i=0;i<peds+cops+bads;i++){
		unsigned int num=width*height+1;
		while(num==width*height+1 or (std::find(used.begin(),used.end(),num)!=used.end())){
			num=random()%(width*height);
		}
		used.push_back(num);
	}

	for(unsigned int i=0;i<used.size();i++){
		if(i<peds){
			subjects.push_back(Subject(green,used[i]%width,used[i]/width));
		}else if(i<peds+cops){
			subjects.push_back(Subject(blue,used[i]%width,used[i]/width));
		}else{
			subjects.push_back(Subject(red,used[i]%width,used[i]/width));
		}
	}

	//for(unsigned int i=0;i<peds;i++)subjects.push_back(Subject(green,random()%width,random()%height));
	//for(unsigned int i=0;i<cops;i++)subjects.push_back(Subject(blue,random()%width,random()%height));
	//for(unsigned int i=0;i<bads;i++)subjects.push_back(Subject(red,random()%width,random()%height));
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
	//std::vector<sf::Color> backBoard;
	//for(unsigned int i=0;i<board.size();i++){
	//	backBoard.push_back(board[i]);
	//}


	for(unsigned int i=0;i<subjects.size();i++){
		if(subjects[i].color==green){
			subjects[i].goTo(60,30);
		}
	}

}

void display(sf::RenderWindow& window){
	for(unsigned int x=0;x<width;x++){
		for(unsigned int y=0;y<height;y++){
			cell.setPosition((BORDER+x)*CELLSIZE,(BORDER+y)*CELLSIZE);
			cell.setFillColor(board[x+y*width]);
			for(unsigned int i=0;i<subjects.size();i++)
				if(subjects[i].x==x)
					if(subjects[i].y==y)
						cell.setFillColor(subjects[i].color);
			window.draw(cell);
		}
	}
	int x=0;
	for(unsigned int y=height/2;y<height/2+5;y++){
		cell.setPosition((BORDER+x)*CELLSIZE,(BORDER+y)*CELLSIZE);
		cell.setFillColor(white);
		window.draw(cell);
	}
}
};

int main(){

	//Init window
	sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"Conway");
	window.setFramerateLimit(60);

	//Create the board
	Board b(WIDTH/CELLSIZE-BORDER*2,HEIGHT/CELLSIZE-BORDER*2);

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

