#pragma once
#include "Color.h"
#include "glm/glm.hpp"
#include "SDL.h"
#include <vector>
class Canvas
{
public:
    Canvas(int width, int height, const class Renderer& renderer);
    ~Canvas();

    void Update();

    void Clear(const color4_t& color);
    void DrawPoint(const glm::ivec2& point, const color4_t& color);

    const glm::vec2& GetSize() const { return m_size; }

    //<allow Renderer to access Canvas private data>
    friend class Renderer;

private:
    //<SDL Texture pointer(forward declaration)> m_texture<default to nullptr>;
    struct SDL_Texture* m_texture{ nullptr };
    //<vector of rgba_t> m_buffer;
    std::vector<rgba_t> m_buffer;
    glm::ivec2 m_size { 0 };
};