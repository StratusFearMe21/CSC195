#include <assert.h>
#include <iostream>
#include <random>

using namespace std;

struct Person {
  char name[32];
  int id;
};

void square(int i) { i = i * i; }
void square_ref(int &i) { i = i * i; }
void double_int(int *const i) { *i *= 2; }

int main() {
  random_device generator;
  uniform_int_distribution<int> distribution(2, 10);
  // ** REFERENCE **
  //
  // declare an int variable and set the value to some number (less than 10)
  int someNumber = distribution(generator);
  // declare an int reference and set it to the int variable above
  int &someNumberRef = someNumber;

  // output the int variable
  cout << someNumber << endl;

  // set the int reference to some number
  int oldNumber = someNumber;
  int randomNumber = distribution(generator);
  while (randomNumber == oldNumber) {
    randomNumber = distribution(generator);
  }
  someNumberRef = randomNumber;
  // output the int variable
  cout << someNumber << endl;
  // what happened to the int variable when the reference was changed? (insert
  // answer)
  assert(oldNumber != someNumber);
  cout << "someNumber changed" << endl;

  // output the address of the int variable
  cout << &someNumber << endl;
  // output the address of the int reference
  cout << &someNumberRef << endl;
  // are the addresses the same or different? (insert answer)
  assert((uintptr_t)&someNumber == (uintptr_t)&someNumberRef);
  cout << "someNumber at same address as someNumberRef" << endl;

  // ** REFERENCE PARAMETER **
  //
  // create a function above main() called Square that takes in an int parameter
  // in the function, multiply the int parameter by itself and assign it back to
  // the parameter (i = i * i)
  void square(int i);
  // call the Square function with the int variable
  // created in the REFERENCE section
  oldNumber = someNumber;
  square(someNumberRef);

  // output the int variable to the console
  cout << someNumber << endl;

  // !! notice how the variable has not changed
  assert(oldNumber == someNumber);
  // this is because we only passed
  // the value to the function !! change the Square function to take a int
  // reference
  void square_ref(int &i);
  oldNumber = someNumber;
  cout << oldNumber << endl;
  square_ref(someNumberRef);
  cout << oldNumber << endl;
  // !! notice how the calling variable has now changed, this is because we
  // 'passed by reference' !!
  assert(oldNumber != someNumber);
  // !! when a function takes a reference parameter, any changes to the
  // parameter changes the calling variable ""

  // ** POINTER VARIABLE **
  //
  // declare an int pointer, set it to nullptr (it points to nothing)
  int *pointer = nullptr;
  // set the int pointer to the address of the int variable created in the
  pointer = &someNumber;
  // REFERENCE section

  // output the value of the pointer
  cout << pointer << endl;
  // what is this address that the pointer is pointing to? (insert answer)
  assert((uintptr_t)pointer == (uintptr_t)&someNumberRef);
  cout << "`pointer` is pointing to the same address as `someNumberRef`"
       << endl;
  // output the value of the object the pointer is pointing to (dereference the
  // pointer)
  cout << *pointer << endl;

  // ** POINTER PARAMETER **
  //
  // create a function above main() called Double that takes in an int pointer
  // parameter. In the function, multiply the int pointer parameter by 2 and
  // assign it back to the parameter (i = i * 2)
  // !! make sure to dereference the pointer to set the value and not set the
  // address !! call the Double function with the pointer created in the POINTER
  // VARIABLE section
  void double_int(int *const i);
  oldNumber = someNumber;
  double_int(pointer);

  // output the dereference pointer
  cout << *pointer << endl;
  // output the int variable created in the REFERENCE section
  cout << &someNumber << endl;
  // did the int variable's value change when using the pointer?
  assert(oldNumber != someNumber);
  cout << "The int variable's value changed" << endl;
}
