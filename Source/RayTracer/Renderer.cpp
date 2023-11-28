#include "Renderer.h"
#include <iostream>

bool Renderer::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void Renderer::Shutdown()
{
    if (m_window) SDL_DestroyWindow(m_window);
    if (m_Renderer) SDL_DestroyRenderer(m_Renderer);
    //if sdl window is not null, destroy sdl window
    //if sdl renderer is not null, destroy sdl window
    SDL_Quit();
}

bool Renderer::CreateWindow(const std::string& title, int width, int height)
{

    m_window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN);
    if (!m_window)
    {
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    
    }
    //the index of the rendering driver to initialize, or -1 to initialize the first one supporting the requested flags
    m_Renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_window)
    {
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        return false;

    }

    return true;
}