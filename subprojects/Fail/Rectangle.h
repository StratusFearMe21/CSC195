#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape {
public:
  Rectangle(float w, float h);
  ~Rectangle() override {}

  float Area() override;

private:
  float m_width;
  float m_height;
};

#endif // RECTANGLE_H
