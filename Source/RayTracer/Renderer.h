#pragma once
#include "SDL.h"
#include <string>
class Renderer
{
public:
	Renderer() = default;
	void Render(class Canvas& canvas);

	bool Initialize();
	void Shutdown();
	bool CreateWindow(const std::string& title, int width, int height);

	void PresentCanvas(const class Canvas& canvas);

	friend class Canvas;

private:
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
	//<pointer to SDL_Window, set default to nullptr>
	//<pointer to SDL_Renderer, set default to nullptr>

};