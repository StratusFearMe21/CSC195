#include "Circle.h"

Circle::Circle(float r) { m_radius = r; }

float Circle::Area() { return 3.14f * m_radius * m_radius; }

void Circle::SetRadius(float radius) { m_radius = radius; }

float Circle::GetRadius() { return m_radius; }
