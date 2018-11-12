//g++ base.cpp -lSDL2 -lSDL2main;./a.out;rm a.out

#include <iostream>
#include <SDL2/SDL.h>

int main(){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *win=SDL_CreateWindow("asdf",10,10,300,300,0);
	SDL_Renderer *ren=SDL_CreateRenderer(win,0,SDL_RENDERER_SOFTWARE);
	SDL_Texture *screen=SDL_CreateTexture(ren,0,0,300,300);

	bool done=false;
	SDL_Event e;
	while(!done){
		while(SDL_PollEvent(&e)){
			std::cout<<e.key.keysym.sym<<'\n';
			if(e.key.keysym.sym==SDLK_ESCAPE)done=true;
			if(e.key.keysym.sym=='q')done=true;
		}
	}
}

