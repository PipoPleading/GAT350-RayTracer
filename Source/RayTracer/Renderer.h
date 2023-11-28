#pragma once
#include "SDL.h"
#include <string>
class Renderer
{
public:
	Renderer() = default;

	bool Initialize();
	void Shutdown();
	bool CreateWindow(const std::string& title, int width, int height);

private:
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_Renderer = nullptr;
	//<pointer to SDL_Window, set default to nullptr>
	//<pointer to SDL_Renderer, set default to nullptr>

};