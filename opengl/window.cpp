#include "window.h"

#include <SDL2/SDL_image.h>

Window::Window(std::size_t width, std::size_t height)
    : width_(width), height_(height) {
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);
  TTF_Init();

  window_handle_ = SDL_CreateWindow(
      "Textured Cube with Lighting", SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

  SDL_GLContext context = SDL_GL_CreateContext(window_handle_);

  scene_ = std::make_unique<Scene>();
  overlay_ = std::make_unique<Overlay>(width, height);
}

Window::~Window() {
  SDL_DestroyWindow(window_handle_);
  SDL_Quit();
}

void Window::loop() {

  bool quit = false;
  while (!quit) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene_->draw();
    overlay_->draw();

    measure_fps();

    SDL_GL_SwapWindow(window_handle_);

    poll_events(quit);
  }
}

void Window::measure_fps() {
  frame_count_++;
  Uint32 current_time = SDL_GetTicks();
  float elapsed_time = (current_time - last_time_) / 1000.0;
  if (elapsed_time > 1.0) {
    overlay_->set_fps(frame_count_ / elapsed_time);
    frame_count_ = 0;
    last_time_ = current_time;
  }
}

void Window::poll_events(bool &quit) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      quit = true;
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        quit = true;
        break;
      case SDLK_UP:
        scene_->set_speed_y(-1.0f);
        break;
      case SDLK_DOWN:
        scene_->set_speed_y(1.0f);
        break;
      case SDLK_LEFT:
        scene_->set_speed_x(-1.0f);
        break;
      case SDLK_RIGHT:
        scene_->set_speed_x(1.0f);
        break;
      }
      break;
    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
      case SDLK_UP:
      case SDLK_DOWN:
        scene_->set_speed_y(0.0f);
        break;
      case SDLK_LEFT:
      case SDLK_RIGHT:
        scene_->set_speed_x(0.0f);
        break;
      }
      break;
    }
  }
}

int main(int argc, char **argv) {
  Window window(1500, 900);
  window.loop();
  return 0;
}
