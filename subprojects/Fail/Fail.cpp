#include <iostream>
#include <vector>

#include "Circle.h"
#include "Rectangle.h"
#include "Shape.h"

using namespace std;

int main_f() {
  vector<Shape *> shapes;

  Circle *c = new Circle(1.0f);
  c->SetRadius(3.0f);
  Rectangle *r = new Rectangle(4.0f, 5.0f);

  shapes.push_back(c);
  shapes.push_back(r);

  for (size_t i = 0; i < shapes.size(); i++) {
    cout << "Area: " << shapes[i]->Area() << endl;
    // TODO: If shape is a circle, print radius
    Circle *circle = dynamic_cast<Circle *>(shapes[i]);
    if (circle != nullptr) {
      cout << "Radius: " << circle->GetRadius() << endl;
    }
  }

  // FIXME: Getting memory leak! Delete all shapes.
  for (size_t i = 0; i < shapes.size(); i++) {
    delete shapes[i];
  }

  return 0;
}

int main(int, char **) {
  // LSan has trouble detecting memory leaks in the
  // main function, so we move it's contents to a
  // separate function and call it here.
  main_f();
  return 0;
}
