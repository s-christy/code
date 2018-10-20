//g++ arena.cpp; ./a.out; rm a.out
#include <iostream>

class Fighter{
public:
	int health=100;
	const char* name="Base";
	volatile int bid(){return 0;}
};

class Bot1: public Fighter{
public:
	const char* name="Bot1";
	int bid(){return 1;}
};

void fight(Fighter* a,Fighter* b){
	int bid1=a->bid();
	int bid2=b->bid();
	std::cout<<bid1;
	std::cout<<bid2;
	if(bid1>bid2){
		a->health-=bid1;
		b->health=0;
	}else if(bid1<bid2){
		b->health-=bid2;
		a->health=0;
	}else{
		a->health-=1;
		b->health-=1;
	}
}

int main(){
	Fighter *f=new Fighter;
	Bot1 *b=new Bot1;
	fight(f,b);
	std::cout<<f->health<<'\n';
	std::cout<<b->health<<'\n';
}
