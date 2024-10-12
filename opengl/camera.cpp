#include "camera.h"
#include <SDL2/SDL_opengl.h>

void Camera::move() { glTranslatef(0.0f, 0.0f, -4.0f); }
