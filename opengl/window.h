#pragma once

#include "scene.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <memory>

class Window {
public:
  Window();

  ~Window();

  void loop();

protected:
  void poll_events(bool &quit);

private:
  SDL_Window *window_handle_ = {};
  std::unique_ptr<Scene> scene_;
};
