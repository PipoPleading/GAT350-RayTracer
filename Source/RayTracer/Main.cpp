#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Scene.h"
#include "Camera.h"
 int main(int, char**)
{
	 std::cout << "Hello World!";

	 seedRandom((unsigned int)time(nullptr));

	 Renderer rend;
	 rend.Initialize();
	 rend.CreateWindow("Window", 400, 300);

	 //canvas creation
	 Canvas canvas(400, 300, rend);
	 //aspect ratio
	
	 float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	 std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	 //camera
	 Scene scene; // sky color could be set with the top and bottom color
	 scene.SetCamera(camera);

	 
	 bool quit = false;
	 while (!quit)
	 {

		canvas.Clear({ 0, 0, 0, 1 });
		scene.Render(canvas);
		rend.PresentCanvas(canvas);
		for (int i = 0; i < 100000; i++) canvas.DrawPoint({ random(0, canvas.GetSize().x), random(0, canvas.GetSize().y)}, {random(0.0f, 1.0f),random(0.0f, 1.0f), random(0.0f, 1.0f), 1});
		canvas.Update();

		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type)
		{
		 case SDL_QUIT:
			 quit = true;
			 break;
		 case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
			quit = true;
			break;
			}
			break;
		 }

	 }
	 rend.Shutdown();

	 return 0;
}