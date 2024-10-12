#pragma once

#include "shape.h"

#include <array>

class Dice : public Shape {
public:
  Dice();

  ~Dice() override = default;

  void draw() override;

private:
  std::array<GLuint, 6> textures_;
};
