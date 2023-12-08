#include "Canvas.h"
#include "Renderer.h"
#include "iostream"

Canvas::Canvas(int width, int height, const Renderer& renderer)
{
	//<set size with width and height>
	m_size = { width, height  };
	m_texture = SDL_CreateTexture(renderer.m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
	width, height);

	m_buffer.resize(width * height); //vector to hold width* height elements >
}

Canvas::~Canvas()
{
	//<if m_texture not nullptr SDL Destroy Texture https ://wiki.libsdl.org/SDL2/SDL_DestroyTexture

	if (m_texture) SDL_DestroyTexture(m_texture);
}

void Canvas::Update()
{
	// set texture with buffer rgba_t data
	//texture, map, pixels pitch
	SDL_UpdateTexture(m_texture, NULL, m_buffer.data(), m_size.x * sizeof(rgba_t));
}


void Canvas::Clear(const color4_t& color)
{
	rgba_t rgba = ColorToRGBA(color); //<convert color to RGBA>
		
	std::fill(m_buffer.begin(), m_buffer.end(), rgba);

}

void Canvas::DrawPoint(const glm::ivec2& point, const color4_t& color)
{
	//< point is outside of canvas bounds(point < 0 or >= size width or size height>)
	if (point.x >= m_size.x || point.y >= m_size.y || point.x < 0 || point.y < 0) return;
	m_buffer[point.x + (point.y * m_size.x)] = ColorToRGBA(color); //convert color to rgba
}