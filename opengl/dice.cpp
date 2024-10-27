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
    texture_[i] = {0.1f + sin10, 0.9f + cos10};
    front_[i] = {-0.8f + sin5, 0.8f + cos5, 1.0f};
    top_[i] = {0.8f - sin5, 1.0f, 0.8f + cos5};
    bottom_[i] = {-0.8f + sin5, -1.0f, 0.8f + cos5};
    back_[i] = {0.8f - sin5, 0.8f + cos5, -1.0f};
    left_[i] = {-1.0f, 0.8f - sin5, 0.8f + cos5};
    right_[i] = {1.0f, -0.8f + sin5, 0.8f + cos5};
    i++;
  }
  for (int d = 0; d <= 90; d += 18) {
    float r = 2.0f * std::numbers::pi / 360.0f * d;
    float sin10 = sin(r) / 10.0f;
    float cos10 = cos(r) / 10.0f;
    float sin5 = sin(r) / 5.0f;
    float cos5 = cos(r) / 5.0f;
    texture_[i] = {0.9f + sin10, 0.9f + cos10};
    front_[i] = {0.8f + sin5, 0.8f + cos5, 1.0f};
    top_[i] = {-0.8f - sin5, 1.0f, 0.8f + cos5};
    bottom_[i] = {0.8f + sin5, -1.0f, 0.8f + cos5};
    back_[i] = {-0.8f - sin5, 0.8f + cos5, -1.0f};
    left_[i] = {-1.0f, -0.8f - sin5, 0.8f + cos5};
    right_[i] = {1.0f, 0.8f + sin5, 0.8f + cos5};
    i++;
  }
  for (int d = 90; d <= 180; d += 18) {
    float r = 2.0f * std::numbers::pi / 360.0f * d;
    float sin10 = sin(r) / 10.0f;
    float cos10 = cos(r) / 10.0f;
    float sin5 = sin(r) / 5.0f;
    float cos5 = cos(r) / 5.0f;
    texture_[i] = {0.9f + sin10, 0.1f + cos10};
    front_[i] = {0.8f + sin5, -0.8f + cos5, 1.0f};
    top_[i] = {-0.8f - sin5, 1.0f, -0.8f + cos5};
    bottom_[i] = {0.8f + sin5, -1.0f, -0.8f + cos5};
    back_[i] = {-0.8f - sin5, -0.8f + cos5, -1.0f};
    left_[i] = {-1.0f, -0.8f - sin5, -0.8f + cos5};
    right_[i] = {1.0f, 0.8f + sin5, -0.8f + cos5};
    i++;
  }
  for (int d = 180; d <= 270; d += 18) {
    float r = 2.0f * std::numbers::pi / 360.0f * d;
    float sin10 = sin(r) / 10.0f;
    float cos10 = cos(r) / 10.0f;
    float sin5 = sin(r) / 5.0f;
    float cos5 = cos(r) / 5.0f;
    texture_[i] = {0.1f + sin10, 0.1f + cos10};
    front_[i] = {-0.8f + sin5, -0.8f + cos5, 1.0f};
    top_[i] = {0.8f - sin5, 1.0f, -0.8f + cos5};
    bottom_[i] = {-0.8f + sin5, -1.0f, -0.8f + cos5};
    back_[i] = {0.8f - sin5, -0.8f + cos5, -1.0f};
    left_[i] = {-1.0, 0.8f - sin5, -0.8f + cos5};
    right_[i] = {1.0, -0.8f + sin5, -0.8f + cos5};
    i++;
  }
}

void Dice::draw() {
  glEnable(GL_TEXTURE_2D);

  // Rounded faces
  draw_face(textures_[5], {0.0f, 0.0f, 1.0f}, front_);
  draw_face(textures_[0], {0.0f, 0.0f, -1.0f}, back_);
  draw_face(textures_[2], {0.0f, 1.0f, 0.0f}, top_);
  draw_face(textures_[3], {0.0f, -1.0f, 0.0f}, bottom_);
  draw_face(textures_[4], {1.0f, 0.0f, 0.0f}, right_);
  draw_face(textures_[1], {-1.0f, 0.0f, 0.0f}, left_);

  // Corner 1
  draw_corner({-1.0f, 1.0f, 1.0f}, front_, 0);
  draw_corner({-1.0f, 1.0f, 1.0f}, top_, 6);
  draw_corner({-1.0f, 1.0f, 1.0f}, left_, 0);

  // Corner 2
  draw_corner({1.0f, 1.0f, 1.0f}, front_, 6);
  draw_corner({1.0f, 1.0f, 1.0f}, top_, 0);
  draw_corner({1.0f, 1.0f, 1.0f}, right_, 6);

  // Corner 3
  draw_corner({1.0f, -1.0f, 1.0f}, front_, 12);
  draw_corner({1.0f, -1.0f, 1.0f}, bottom_, 6);
  draw_corner({1.0f, -1.0f, 1.0f}, right_, 0);

  // Corner 4
  draw_corner({-1.0f, -1.0f, 1.0f}, front_, 18);
  draw_corner({-1.0f, -1.0f, 1.0f}, bottom_, 0);
  draw_corner({-1.0f, -1.0f, 1.0f}, left_, 6);

  // Corner 5
  draw_corner({1.0f, 1.0f, -1.0f}, back_, 0);
  draw_corner({1.0f, 1.0f, -1.0f}, top_, 18);
  draw_corner({1.0f, 1.0f, -1.0f}, right_, 12);

  // Corner 6
  draw_corner({-1.0f, 1.0f, -1.0f}, back_, 6);
  draw_corner({-1.0f, 1.0f, -1.0f}, top_, 12);
  draw_corner({-1.0f, 1.0f, -1.0f}, left_, 18);

  // Corner 7
  draw_corner({-1.0f, -1.0f, -1.0f}, back_, 12);
  draw_corner({-1.0f, -1.0f, -1.0f}, bottom_, 18);
  draw_corner({-1.0f, -1.0f, -1.0f}, left_, 12);

  // Corner 8
  draw_corner({1.0f, -1.0f, -1.0f}, back_, 18);
  draw_corner({1.0f, -1.0f, -1.0f}, bottom_, 12);
  draw_corner({1.0f, -1.0f, -1.0f}, right_, 18);
}

void Dice::draw_face(GLuint texture_id, const std::array<float, 3> &normal,
                     const std::array<std::array<float, 3>, 24> &coords) {
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glNormal3fv(normal.data());
  glBegin(GL_TRIANGLE_FAN);
  for (int i = 0; i < 24; i++) {
    glTexCoord2fv(texture_[i].data());
    glVertex3fv(coords[i].data());
  }
  glEnd();
}

void Dice::draw_corner(const std::array<float, 3> &normal,
                       const std::array<std::array<float, 3>, 24> &coords,
                       int coords_offset) {
  glNormal3fv(normal.data());
  std::array<float, 3> corner = {normal[0] * 0.97f, normal[1] * 0.97f,
                                 normal[2] * 0.97f};
  for (int i = 0; i < 5; i++) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex3fv(corner.data());
    glVertex3fv(coords[coords_offset + i + 1].data());
    glVertex3fv(coords[coords_offset + i].data());
    glEnd();
  }
}
