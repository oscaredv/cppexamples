#include "dice.h"

#include <cmath>

Dice::Dice() {
  // Load textures
  for (std::size_t i = 0; i < textures_.size(); i++) {
    std::filesystem::path filename = "dice" + std::to_string(i + 1) + ".png";
    textures_[i] = LoadTexture(filename);
  }

  // Calculate coordinates
  int i = 0;
  for (int d = 270; d <= 360; d += 18) {
    float r = 2.0f * std::numbers::pi / 360.0f * d;
    float sin10 = sin(r) / 10.0f;
    float cos10 = cos(r) / 10.0f;
    float sin5 = sin(r) / 5.0f;
    float cos5 = cos(r) / 5.0f;
    texture_[i] = std::make_pair(0.1f + sin10, 0.9f + cos10);
    front_[i] = std::make_tuple(-0.8f + sin5, 0.8f + cos5, 1.0f);
    top_[i] = std::make_tuple(0.8f - sin5, 1.0f, 0.8f + cos5);
    bottom_[i] = std::make_tuple(-0.8f + sin5, -1.0f, 0.8f + cos5);
    back_[i] = std::make_tuple(0.8f - sin5, 0.8f + cos5, -1.0f);
    left_[i] = std::make_tuple(-1.0f, 0.8f - sin5, 0.8f + cos5);
    right_[i] = std::make_tuple(1.0f, -0.8f + sin5, 0.8f + cos5);
    i++;
  }
  for (int d = 0; d <= 90; d += 18) {
    float r = 2.0f * std::numbers::pi / 360.0f * d;
    float sin10 = sin(r) / 10.0f;
    float cos10 = cos(r) / 10.0f;
    float sin5 = sin(r) / 5.0f;
    float cos5 = cos(r) / 5.0f;
    texture_[i] = std::make_pair(0.9f + sin10, 0.9f + cos10);
    front_[i] = std::make_tuple(0.8f + sin5, 0.8f + cos5, 1.0f);
    top_[i] = std::make_tuple(-0.8f - sin5, 1.0f, 0.8f + cos5);
    bottom_[i] = std::make_tuple(0.8f + sin5, -1.0f, 0.8f + cos5);
    back_[i] = std::make_tuple(-0.8f - sin5, 0.8f + cos5, -1.0f);
    left_[i] = std::make_tuple(-1.0f, -0.8f - sin5, 0.8f + cos5);
    right_[i] = std::make_tuple(1.0f, 0.8f + sin5, 0.8f + cos5);
    i++;
  }
  for (int d = 90; d <= 180; d += 18) {
    float r = 2.0f * std::numbers::pi / 360.0f * d;
    float sin10 = sin(r) / 10.0f;
    float cos10 = cos(r) / 10.0f;
    float sin5 = sin(r) / 5.0f;
    float cos5 = cos(r) / 5.0f;
    texture_[i] = std::make_pair(0.9f + sin10, 0.1f + cos10);
    front_[i] = std::make_tuple(0.8f + sin5, -0.8f + cos5, 1.0f);
    top_[i] = std::make_tuple(-0.8f - sin5, 1.0f, -0.8f + cos5);
    bottom_[i] = std::make_tuple(0.8f + sin5, -1.0f, -0.8f + cos5);
    back_[i] = std::make_tuple(-0.8f - sin5, -0.8f + cos5, -1.0f);
    left_[i] = std::make_tuple(-1.0f, -0.8f - sin5, -0.8f + cos5);
    right_[i] = std::make_tuple(1.0f, 0.8f + sin5, -0.8f + cos5);
    i++;
  }
  for (int d = 180; d <= 270; d += 18) {
    float r = 2.0f * std::numbers::pi / 360.0f * d;
    float sin10 = sin(r) / 10.0f;
    float cos10 = cos(r) / 10.0f;
    float sin5 = sin(r) / 5.0f;
    float cos5 = cos(r) / 5.0f;
    texture_[i] = std::make_pair(0.1f + sin10, 0.1f + cos10);
    front_[i] = std::make_tuple(-0.8f + sin5, -0.8f + cos5, 1.0f);
    top_[i] = std::make_tuple(0.8f - sin5, 1.0f, -0.8f + cos5);
    bottom_[i] = std::make_tuple(-0.8f + sin5, -1.0f, -0.8f + cos5);
    back_[i] = std::make_tuple(0.8f - sin5, -0.8f + cos5, -1.0f);
    left_[i] = std::make_tuple(-1.0, 0.8f - sin5, -0.8f + cos5);
    right_[i] = std::make_tuple(1.0, -0.8f + sin5, -0.8f + cos5);
    i++;
  }
}

void Dice::draw() {
  glEnable(GL_TEXTURE_2D);

  // Front face
  glBindTexture(GL_TEXTURE_2D, textures_[5]);
  glBegin(GL_TRIANGLE_FAN);
  glNormal3f(0.0f, 0.0f, 1.0f);
  for (int i = 0; i < 24; i++) {
    auto [tx, ty] = texture_[i];
    auto [x, y, z] = front_[i];
    glTexCoord2f(tx, ty);
    glVertex3f(x, y, z);
  }
  glEnd();

  // Back face
  glBindTexture(GL_TEXTURE_2D, textures_[0]);
  glBegin(GL_TRIANGLE_FAN);
  glNormal3f(0.0f, 0.0f, -1.0f);
  for (int i = 0; i < 24; i++) {
    auto [tx, ty] = texture_[i];
    auto [x, y, z] = back_[i];
    glTexCoord2f(tx, ty);
    glVertex3f(x, y, z);
  }
  glEnd();

  // Top face
  glBindTexture(GL_TEXTURE_2D, textures_[2]);
  glBegin(GL_TRIANGLE_FAN);
  glNormal3f(0.0f, 1.0f, 0.0f);
  for (int i = 0; i < 24; i++) {
    auto [tx, ty] = texture_[i];
    auto [x, y, z] = top_[i];
    glTexCoord2f(tx, ty);
    glVertex3f(x, y, z);
  }
  glEnd();

  // Bottom face
  glBindTexture(GL_TEXTURE_2D, textures_[3]);
  glBegin(GL_TRIANGLE_FAN);
  glNormal3f(0.0f, -1.0f, 0.0f);
  for (int i = 0; i < 24; i++) {
    auto [tx, ty] = texture_[i];
    auto [x, y, z] = bottom_[i];
    glTexCoord2f(tx, ty);
    glVertex3f(x, y, z);
  }
  glEnd();

  // Right face
  glBindTexture(GL_TEXTURE_2D, textures_[4]);
  glBegin(GL_TRIANGLE_FAN);
  glNormal3f(1.0f, 0.0f, 0.0f);
  for (int i = 0; i < 24; i++) {
    auto [tx, ty] = texture_[i];
    auto [x, y, z] = right_[i];
    glTexCoord2f(tx, ty);
    glVertex3f(x, y, z);
  }
  glEnd();

  // Left face
  glBindTexture(GL_TEXTURE_2D, textures_[1]);
  glBegin(GL_TRIANGLE_FAN);
  glNormal3f(-1.0f, 0.0f, 0.0f);
  for (int i = 0; i < 24; i++) {
    auto [tx, ty] = texture_[i];
    auto [x, y, z] = left_[i];
    glTexCoord2f(tx, ty);
    glVertex3f(x, y, z);
  }
  glEnd();
}
