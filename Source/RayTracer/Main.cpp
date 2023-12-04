#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Scene.h"
#include "Camera.h"
#include "Material.h"
#include "Sphere.h"
#include "Random.h"

 int main(int, char**)
{
     seedRandom((unsigned int)time(nullptr));

     Renderer renderer;
     renderer.Initialize();
     renderer.CreateWindow("Window", 1920, 1080);

     Canvas canvas(1920, 1080, renderer);

     float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
     std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

     Scene scene(20); // sky color could be set with the top and bottom color
     scene.SetCamera(camera);

     // create material
     auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
     auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);

     // create objects -> add to scene
     for (int i = 0; i < 10; i++)
     {
         std::shared_ptr<Material> material = ((int)random(0, 2) == 0) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal); //<use rand() and %to randomly pick the material>
         auto sphere = std::make_unique<Sphere>(random({ -5, -5, -15 }, { 5, 5, -5 }), random01() * 3, material);//<create the sphere with the material>;
         scene.AddObject(std::move(sphere));
     }

     //// create material
     //auto material = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });

     //for (int i = 0; i < 2; i++)
     //{
     //    // create objects -> add to scene
     //    auto sphere = std::make_unique<Sphere>(random({ -5, -5, -15 }, { 5, 5, -5 }), random01() * 3, material);
     //    scene.AddObject(std::move(sphere));

     //}

     canvas.Clear({ 0, 0, 0, 1 });
     scene.Render(canvas, 100);
     canvas.Update();

     bool quit = false;
     while (!quit)
     {
         renderer.PresentCanvas(canvas);
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

     renderer.Shutdown();

     return 0;
}