#include "window.h"

#include <SDL2/SDL_image.h>

#include <iostream>

Window::Window() {
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);

  window_handle_ =
      SDL_CreateWindow("Textured Cube with Lighting", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 1500, 900, SDL_WINDOW_OPENGL);

  SDL_GLContext context = SDL_GL_CreateContext(window_handle_);

  scene_ = std::make_unique<Scene>();
}

Window::~Window() {
  SDL_DestroyWindow(window_handle_);
  SDL_Quit();
}

void Window::loop() {
  Uint32 lastTime = SDL_GetTicks();
  int frameCount = 0;

  bool quit = false;
  while (!quit) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene_->draw();

    SDL_GL_SwapWindow(window_handle_);

    poll_events(quit);
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
      }
      break;
    }
  }
}

int main(int argc, char **argv) {
  Window window;
  window.loop();
  return 0;
}
