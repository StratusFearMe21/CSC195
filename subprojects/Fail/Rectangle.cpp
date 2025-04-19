#include "Rectangle.h"

Rectangle::Rectangle(float w, float h) {
  m_width = w;
  m_height = h;
}

float Rectangle::Area() { return m_width * m_height; }
