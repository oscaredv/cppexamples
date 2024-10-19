#pragma once

#include "camera.h"
#include "dice.h"

#include <memory>

class Scene {
public:
  Scene();

  ~Scene() = default;

  void SetupLighting();

  void draw();
  void set_speed_x(float speed) { speed_x_ = speed; }
  void set_speed_y(float speed) { speed_y_ = speed; }

private:
  Camera camera_;
  std::unique_ptr<Dice> dice_;

  float angle_x_ = 0.0f;
  float angle_y_ = 0.0f;
  float speed_x_ = 0.0f;
  float speed_y_ = 0.0f;
};
