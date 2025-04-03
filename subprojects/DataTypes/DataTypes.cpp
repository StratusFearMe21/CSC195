#include <crossline.h>
#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

const float TAX = 0.1f;

#define PROMPT(prompt, output)                                                 \
  for (;;) {                                                                   \
    std::istringstream strm;                                                   \
    char buf[256];                                                             \
    strm.rdbuf()->pubsetbuf(buf, sizeof(buf));                                 \
    crossline_readline(prompt, buf, sizeof(buf));                              \
    if (strm >> output) {                                                      \
      break;                                                                   \
    } else {                                                                   \
      cout << "The value entered wasn't valid" << endl;                        \
    }                                                                          \
  }

int main() {
  crossline_prompt_color_set(CROSSLINE_FGCOLOR_GREEN);

  string name = "";
  char initial = '\0';
  short age = -1;
  bool isAdult = -1;
  unsigned int zipcode = 0;
  float wage = -1.0;
  short daysWorked = -1;
  float hoursWorkedPerDay[7] = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0};

  PROMPT("Enter first name: ", name);
  PROMPT("Enter initial of last name: ", initial);
  PROMPT("Enter age: ", age);
  PROMPT("Enter zipcode: ", zipcode);
  PROMPT("Enter hourly wage: ", wage);
  PROMPT("Enter number of days worked (max 7): ", daysWorked);

  isAdult = (age >= 18); // Determine adulthood status
  float totalHours = 0;  // Initialize total hours to 0

  for (int i = 0; i < daysWorked; i++) {
    cout << "Enter hours worked for day " << (i + 1) << ": ";
    cin >> hoursWorkedPerDay[i];

    totalHours += hoursWorkedPerDay[i]; // Accumulate total hours
  }

  float grossIncome = totalHours * wage;
  float taxAmount = grossIncome * TAX;
  float netIncome = grossIncome - taxAmount;

  cout << "\nEmployee Payroll Summary\n";
  cout << "-------------------------\n";
  cout << "Name: " << name << " " << initial << ".\n";
  cout << "Age: " << age << " (Adult: " << (isAdult ? "Yes" : "No") << ")\n";
  cout << "Zipcode: " << zipcode << "\n";
  cout << "Hourly Wage: $" << wage << " per hour\n";
  cout << "Total Hours Worked: " << totalHours << " hours\n";
  cout << "Gross Income: $" << grossIncome << "\n";
  cout << "Tax Amount: $" << taxAmount << "\n";
  cout << "Net Income: $" << netIncome << "\n";
}
