#include "label.h"

Label::Label(const std::string &text, TTF_Font *font, std::size_t pos_x,
             std::size_t pos_y)
    : font_(font), pos_x_(pos_x), pos_y_(pos_y) {
  set_text(text);
}

void Label::set_text(const std::string &text) {
  if (texture_id_) {
    glDeleteTextures(1, &texture_id_);
  }

  SDL_Color text_color = {255, 255, 255, 255};
  auto *surface = TTF_RenderText_Blended(font_, text.c_str(), text_color);
  width_ = surface->w;
  height_ = surface->h;

  auto *rgb_surface = SDL_CreateRGBSurface(0, width_, height_, 32,
                                           0x00FF0000,  // R-mask
                                           0x0000FF00,  // G-mask
                                           0x000000FF,  // B-mask
                                           0xFF000000); // A-mask
  SDL_BlitSurface(surface, nullptr, rgb_surface, nullptr);

  glGenTextures(1, &texture_id_);
  glBindTexture(GL_TEXTURE_2D, texture_id_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rgb_surface->w, rgb_surface->h, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, rgb_surface->pixels);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glBindTexture(GL_TEXTURE_2D, 0);
  SDL_FreeSurface(rgb_surface);
  SDL_FreeSurface(surface);
}

void Label::draw() {
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_id_);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(pos_x_, pos_y_);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(pos_x_ + width_, pos_y_);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(pos_x_ + width_, pos_y_ + height_);
  glTexCoord2f(0.0f, 1.0f);
  glVertex2f(pos_x_, pos_y_ + height_);
  glEnd();
}