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

  std::array<std::pair<float, float>, 24> texture_;
  std::array<std::tuple<float, float, float>, 24> front_;
  std::array<std::tuple<float, float, float>, 24> back_;
  std::array<std::tuple<float, float, float>, 24> top_;
  std::array<std::tuple<float, float, float>, 24> bottom_;
  std::array<std::tuple<float, float, float>, 24> left_;
  std::array<std::tuple<float, float, float>, 24> right_;
};
