#include "Student.h"
#include <iostream>
using namespace std;

class Person {
public:
  float weight;
  int age;

  void f() {}
};

int main() {
  Student student;
  student.SetName("Raymond");
  student.Write();

  Person person;
  person.age = 19;

  unsigned int i = -23;
  cout << i << endl;
  cout << sizeof(i) << endl;
  cout << sizeof(Person) << endl;

  char c = 'A';
  cout << &i << endl;

  f();

  cout << "Hello, World!" << endl;
  cout << "Git is now tracking this project!" << endl;

  return 0;
}
