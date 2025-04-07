#include <array>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

using namespace std;

// Prints the days of the week
void makeArray() {
  array<string, 7> daysOfWeek = {"Monday", "Tuesday",  "Wednesday", "Thursday",
                                 "Friday", "Saturday", "Sunday"};

  for (string day : daysOfWeek) {
    cout << day << endl;
  }
}

// Adds, removes, and prints some integers
void makeVector() {
  vector<int> ints = {5, 10, 15, 20, 25};
  ints.push_back(30);
  ints.push_back(35);
  ints.pop_back();
  ints.pop_back();

  for (int i : ints) {
    cout << i << endl;
  }
}

// Prints some fruits
void makeList() {
  list<string> fruits = {"Apple", "Bannana", "Tomato"};
  fruits.remove("Apple");

  for (string fruit : fruits) {
    cout << fruit << endl;
  }
}

// Prints some fruits and some prices
void makeMap() {
  map<string, int> fruitsMap;
  fruitsMap.insert({"apples", 5});
  fruitsMap.insert({"bannanas", 7});
  fruitsMap.insert({"tomatoes", 3});
  fruitsMap.insert({"bannanas", 8});

  for (const pair<string, int> kv : fruitsMap) {
    cout << kv.first << ": $" << kv.second << endl;
  }
}

int main() {
  makeArray();
  makeVector();
  makeList();
  makeMap();

  return 0;
}
