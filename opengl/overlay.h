#pragma once

#include "label.h"

#include <cstddef>
#include <memory>

class Overlay {
public:
  Overlay(std::size_t width, std::size_t height);

  ~Overlay() = default;

  void set_fps(double fps);

  void draw();

private:
  std::size_t width_;
  std::size_t height_;
  std::unique_ptr<Label> fps_label_;

  TTF_Font *font_ = nullptr;
};
