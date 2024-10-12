#pragma once

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <filesystem>

class Shape {
public:
  Shape() = default;
  virtual ~Shape() = default;

  virtual void draw() = 0;

  GLuint LoadTexture(const std::filesystem::path &filename);
};