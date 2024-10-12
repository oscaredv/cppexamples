#include "dice.h"

#include <iostream>

Dice::Dice() {
  for (std::size_t i = 0; i < textures_.size(); i++) {
    std::filesystem::path filename = "dice" + std::to_string(i + 1) + ".png";
    std::cout << "LOAD: " << filename << std::endl;
    textures_[i] = LoadTexture(filename);
  }
}

void Dice::draw() {
  glEnable(GL_TEXTURE_2D);

  // Front face
  std::array<GLfloat, 3> vector_normal_front = {0.0f, 0.0f, 1.0f};
  glBindTexture(GL_TEXTURE_2D, textures_[4]);
  glBegin(GL_QUADS);
  glNormal3fv(vector_normal_front.data());
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glEnd();

  // Back face
  std::array<GLfloat, 3> vector_normal_back = {0.0f, 0.0f, -1.0f};
  glBindTexture(GL_TEXTURE_2D, textures_[1]);
  glBegin(GL_QUADS);
  glNormal3fv(vector_normal_back.data());
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glEnd();

  // Top face
  std::array<GLfloat, 3> vector_normal_top = {0.0f, 1.0f, 0.0f};
  glBindTexture(GL_TEXTURE_2D, textures_[0]);
  glBegin(GL_QUADS);
  glNormal3fv(vector_normal_top.data());
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glEnd();

  // Bottom face
  std::array<GLfloat, 3> vector_normal_bottom = {0.0f, -1.0f, 0.0f};
  glBindTexture(GL_TEXTURE_2D, textures_[5]);
  glBegin(GL_QUADS);
  glNormal3fv(vector_normal_bottom.data());
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glEnd();

  // Right face
  std::array<GLfloat, 3> vector_normal_right = {1.0f, 0.0f, 0.0f};
  glBindTexture(GL_TEXTURE_2D, textures_[3]);
  glBegin(GL_QUADS);
  glNormal3fv(vector_normal_right.data());
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glEnd();

  // Left face
  std::array<GLfloat, 3> vector_normal_left = {-1.0f, 0.0f, 0.0f};
  glBindTexture(GL_TEXTURE_2D, textures_[2]);
  glBegin(GL_QUADS);
  glNormal3fv(vector_normal_left.data());
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glEnd();
}
