//g++ dummy.cpp;./a.out;rm a.out

#include <iostream>
#include <unistd.h>

int main(){
	unsigned int i=0;
	while(1){
		std::cout<<i<<'\n';
		usleep(1000000);
		//usleep(100);
		i++;
	}
}

