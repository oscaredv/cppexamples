#include "scene.h"

#include <SDL2/SDL.h>

#include <iostream>

Scene::Scene() {
  glewExperimental = GL_TRUE;
  glewInit();

  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, 1500.0f / 900.0f, 0.1f, 100.0f);

  glMatrixMode(GL_MODELVIEW);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CW);

  SetupLighting();

  dice_ = std::make_unique<Dice>();
}

void Scene::SetupLighting() {
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  std::array<GLfloat, 4> light_position = {0.0f, 2.0f, 2.0f, 1.0f};
  std::array<GLfloat, 4> light_diffuse_color = {1.0f, 1.0f, 1.0f, 1.0f};
  std::array<GLfloat, 4> light_specular = {1.0f, 1.0f, 1.0f, 1.0f};
  std::array<GLfloat, 4> light_ambient_color = {0.1f, 0.1f, 0.1f, 1.0f};

  glLightfv(GL_LIGHT0, GL_POSITION, light_position.data());
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse_color.data());
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular.data());
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient_color.data());
}

void Scene::draw() {
  glEnable(GL_LIGHTING);

  glLoadIdentity();

  camera_.move();

  // glRotatef(SDL_GetTicks() * 0.1f, 1.0f, -0.8f, 0.5f);
  glRotatef(angle_x_, 0.0f, 1.0f, 0.0f);
  glRotatef(angle_y_, 1.0f, 0.0f, 0.0f);

  angle_x_ += speed_x_;
  angle_y_ += speed_y_;

  dice_->draw();
}
