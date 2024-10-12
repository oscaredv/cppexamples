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

private:
  Camera camera_;
  std::unique_ptr<Dice> dice_;
};
