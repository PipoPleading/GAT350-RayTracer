#include <iostream>
#include "Renderer.h"
 int main(int, char**)
{
	 std::cout << "Hello World!";

	 Renderer rend;
	 rend.Initialize();
	 rend.CreateWindow("Window", 400, 300);

	 bool quit = false;
	 while (!quit)
	 {
		 SDL_Event event;
		 SDL_PollEvent(&event);
		 switch (event.type)
		 {
		 case SDL_QUIT:
			 quit = true;
			 break;
		 }
	 }
	 rend.Shutdown();

	 return 0;
}