#pragma once

#include "shape.h"

#include <array>

class Dice : public Shape {
public:
  Dice();

  ~Dice() override = default;

  void draw() override;

protected:
  void draw_face(GLuint texture_id, const std::array<float, 3> &normal,
                 const std::array<std::array<float, 3>, 24> &coords);
  void draw_corner(const std::array<float, 3> &normal,
                   const std::array<std::array<float, 3>, 24> &coords,
                   int coords_offset);

private:
  std::array<GLuint, 6> textures_;

  std::array<std::array<float, 2>, 24> texture_;
  std::array<std::array<float, 3>, 24> front_;
  std::array<std::array<float, 3>, 24> back_;
  std::array<std::array<float, 3>, 24> top_;
  std::array<std::array<float, 3>, 24> bottom_;
  std::array<std::array<float, 3>, 24> left_;
  std::array<std::array<float, 3>, 24> right_;
};
