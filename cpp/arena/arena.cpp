//g++ arena.cpp; ./a.out; rm a.out
#include <iostream>
#include <stdlib.h>

class Fighter{
public:
	int health=100;
	virtual char const * name(){return "Base";}
	virtual int bid(){return 0;}
};

class Bot1: public Fighter{
public:
	char const * name(){return "Bot1";}
	int bid(){return 1;}
};

class Dummy: public Fighter{
public:
	char const * name(){return "Dummy";}
	int bid(){return 0;}
};

class Rando: public Fighter{
public:
	char const * name(){return "Rando";}
	int bid(){return rand()%health-1;}
};

//stubborn picks a value and sticks with it
//TheFullHalfie
//OnePunch
//

Fighter *randomFighter(){
	int choice=rand()%3;
	switch(choice){
		case 0: return new Bot1;
		case 1: return new Dummy;
		case 2: return new Rando;
	}
	return new Fighter;
}

void fight(Fighter* a,Fighter* b){
	int bid1=a->bid();
	int bid2=b->bid();
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
	std::cout
<<a->name()<<' '
<<bid1<<' '
<<a->health<<'\n';

	std::cout
<<b->name()<<' '
<<bid2<<' '
<<b->health<<'\n';
}

int main(){
	srand(time(0));
	Fighter *a=randomFighter();
	Fighter *b=randomFighter();
	for(int i=0;i<105;i++){
		fight(a,b);
		if(a->health<0)a=randomFighter();
		if(b->health<0)b=randomFighter();
		std::cout<<'\n';
	}
}










