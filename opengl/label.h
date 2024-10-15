#pragma once

#include "shape.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Label : public Shape {
public:
  Label(const std::string &text, TTF_Font *font, std::size_t pos_x,
        std::size_t pos_y);

  void set_text(const std::string &text);

  void draw() override;

private:
  GLuint texture_id_ = 0;
  TTF_Font *font_ = nullptr;
  std::size_t pos_x_;
  std::size_t pos_y_;
  std::size_t width_ = 0;
  std::size_t height_ = 0;
};
