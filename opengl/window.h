#pragma once

#include "overlay.h"
#include "scene.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>

#include <cstddef>
#include <memory>

class Window {
public:
  Window(std::size_t width, std::size_t height);

  ~Window();

  void loop();

protected:
  void poll_events(bool &quit);
  void measure_fps();

private:
  std::size_t width_;
  std::size_t height_;
  SDL_Window *window_handle_ = {};
  std::unique_ptr<Scene> scene_;
  std::unique_ptr<Overlay> overlay_;

  Uint32 last_time_ = SDL_GetTicks();
  int frame_count_ = 0;
};
