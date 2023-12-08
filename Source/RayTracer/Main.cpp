#include "Renderer.h"
#include "Canvas.h"
#include "Scene.h"
#include "Camera.h"

#include "Material.h"
#include "Mesh.h"
//#include "Triangle.h"
#include "Plane.h"
#include "Sphere.h"

#include "Triangle.h"
#include "Random.h"

#include <glm/gtx/color_space.hpp>
#include <memory>
#include <iostream>

void InitScene01(Scene& scene, const Canvas& canvas);
void InitScene02(Scene& scene, const Canvas& canvas);
void InitSceneEmissiveCube(Scene& scene, const Canvas& canvas);

 int main(int, char**)
{
     seedRandom((unsigned int)time(nullptr));

     const int width = 720;
     const int height = 480;
     const int samples = 200;
     const int depth = 10;

     Renderer renderer;
     renderer.Initialize();
     renderer.CreateWindow("Ray Tracer", width, height);

     Canvas canvas(width, height, renderer);
     Scene scene(glm::vec3{ 1 }, glm::vec3{ 1 });

     //InitScene02(scene, canvas);
     InitScene02(scene, canvas);

     // render scene
     //canvas.Clear({ 0, 0, 0, 1 });
     //scene.Render(canvas, samples, depth);
     //canvas.Update();

     //random balls w/ materials

     canvas.Clear({ 0, 0, 0, 1 }); //potential scuffage
     scene.Render(canvas, samples, depth);
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

void InitScene01(Scene& scene, const Canvas& canvas)
{
    float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
    scene.SetCamera(camera);

    // create objects -> add to scene
    for (int x = -10; x < 10; x++)
    {
        for (int z = -10; z < 10; z++)
        {
            std::shared_ptr<Material> material;

            // create random material
            float r = random01();
            if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
            else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
            else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
            else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

            // set random sphere radius
            float radius = random(0.2f, 0.3f);
            // create sphere using random radius and material
            auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
            // add sphere to the scene
            scene.AddObject(std::move(sphere));
        }
    }

    auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.8f }));
    scene.AddObject(std::move(plane));
}

void InitScene02(Scene& scene, const Canvas& canvas)
{
    float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 3 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
    scene.SetCamera(camera);

    //auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
    //scene.AddObject(std::move(triangle));

    //auto plane = std::make_unique<Plane>(glm::vec3{ 0, -1, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.8f }));
    //scene.AddObject(std::move(plane));

    //auto mesh = std::make_unique<Mesh>(std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ 0.0f , 1.0f, 1.0f }), 5.0f));
    //mesh->Load("models/bloopy.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
    //scene.AddObject(std::move(mesh));
    
    //white walls
    auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0.8f }));
    mesh->Load("models/cube.obj", glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 0, 0 });
    scene.AddObject(std::move(mesh));

    auto mesh1 = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0.8f }));
    mesh1->Load("models/cube.obj", glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 1, 1, 5 });
    scene.AddObject(std::move(mesh1));

    auto mesh2 = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0.8f }));
    mesh2->Load("models/cube.obj", glm::vec3{ 0, -1, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 1, 1, 5 });
    scene.AddObject(std::move(mesh2));

    //behind camera
    auto mesh3 = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0.8f }));
    mesh3->Load("models/cube.obj", glm::vec3{ 0, 0, -5 }, glm::vec3{ 0, 0, 0 });
    scene.AddObject(std::move(mesh3));

    //green
    auto green = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0.0f, 1.0f, 0.0f }));
    green->Load("models/cube.obj", glm::vec3{ -1, 0, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 1, 1, 5 });
    scene.AddObject(std::move(green));

    //red
    auto red = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
    red->Load("models/cube.obj", glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{1, 1, 5});
    scene.AddObject(std::move(red));

    //light
    auto light = std::make_unique<Mesh>(std::make_shared<Emissive>(color3_t{20}, 0.8f));
    light->Load("models/cube.obj", glm::vec3{ 0, 0.55f, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0.15f });
    scene.AddObject(std::move(light));

    //other objects

    auto test = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 1, 1, 0 }));
    test->Load("models/cube.obj", glm::vec3{ -0.25f, 0, 0 }, glm::vec3{ 0, 45, 0 }, glm::vec3{ 0.25f });
    scene.AddObject(std::move(test));

    auto test2 = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 1, 1 }));
    test2->Load("models/cube.obj", glm::vec3{ 0.25f, -0.3f, 0.25f }, glm::vec3{ 0, 135, 0 }, glm::vec3{ 0.25f, 0.75, 0.75 });
    scene.AddObject(std::move(test2));

}

void InitSceneEmissiveCube(Scene& scene, const Canvas& canvas)
{
    float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
    scene.SetCamera(camera);

    //auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
    //mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
    //scene.AddObject(std::move(mesh));

    auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
    scene.AddObject(std::move(plane));
    
    auto mesh = std::make_unique<Mesh>(std::make_shared<Emissive>(color3_t{ 20 }));
    mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
    scene.AddObject(std::move(mesh));
}