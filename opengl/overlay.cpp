#include "overlay.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <array>
#include <format>
#include <iostream>

Overlay::Overlay(std::size_t width, std::size_t height)
    : width_(width), height_(height) {
  font_ = TTF_OpenFont("font.ttf", 18);
  if (!font_) {
    std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
  }

  fps_label_ =
      std::make_unique<Label>("FPS: -", font_, width - 140, height - 20);
}

void Overlay::set_fps(double fps) {
  fps_label_->set_text(
      std::format("FPS: {}", std::round(fps * 1000.0) / 1000.0));
}

void Overlay::draw() {
  glDisable(GL_LIGHTING);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0, width_, height_, 0, -1, 1); // 2D-ortografisk projeksjon

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  fps_label_->draw();

  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}
