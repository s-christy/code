//g++ dummy2.cpp;./a.out;rm a.out

#include <iostream>
#include <unistd.h>

int main(){
	unsigned int i=89;
	char c;
	while(c=getchar()){
		if(c=='d')std::cout<<std::dec<<i<<'\n';
		if(c=='q')break;
		if(c=='w')std::cin>>std::dec>>i;
	}
}

