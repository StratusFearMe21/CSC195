#include "Employee.h"
#include <limits>

#define PROMPT(prompt, output)                                                 \
  for (;;) {                                                                   \
    std::cout << prompt;                                                       \
    if (std::cin >> output) {                                                  \
      break;                                                                   \
    } else {                                                                   \
      std::cout << "The value entered wasn't valid" << std::endl;              \
      std::cin.clear();                                                        \
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');      \
    }                                                                          \
  }

const float Employee::TAX = 0.1f; // Define TAX (10%)

void Employee::Read() {
  PROMPT("Enter name: ", name);
  PROMPT("Enter age: ", age);
  PROMPT("Enter zipcode: ", zipcode);
  PROMPT("Enter hourly wage: ", wage);
  PROMPT("Enter total hours worked this week: ", hoursWorked);
}

void Employee::Write() {
  float weeklyGross = wage * hoursWorked;
  float weeklyTax = weeklyGross * TAX;
  float weeklyNet = weeklyGross - weeklyTax;
  float yearlyGross = weeklyGross * 52;
  float yearlyNet = yearlyGross - (yearlyGross * TAX);

  std::cout << "\nEmployee Payroll Summary\n";
  std::cout << "-------------------------\n";
  std::cout << "Name: " << name << "\n";
  std::cout << "Age: " << age << "\n";
  std::cout << "Zipcode: " << zipcode << "\n";
  std::cout << "Hourly Wage: $" << wage << "\n";
  std::cout << "Hours Worked: " << hoursWorked << "\n";
  std::cout << "Weekly Gross Pay: $" << weeklyGross << "\n";
  std::cout << "Weekly Net Pay: $" << weeklyNet << "\n";
  std::cout << "Yearly Gross Pay: $" << yearlyGross << "\n";
  std::cout << "Yearly Net Pay: $" << yearlyNet << "\n";
}
