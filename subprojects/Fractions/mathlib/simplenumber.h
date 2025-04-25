#ifndef FRACTION_H
#define FRACTION_H

#include <glibmm.h>

#include <giac/config.h>
#include <giac/giac.h>

namespace mathlib {
template <typename T> class SimpleNumber {
public:
  SimpleNumber<T>(const T number);

  T get() const;
  std::string print(const giac::context *contextptr);
  // friend SimpleNumber<T> simplify(SimpleNumber<T> &a, SimpleNumber<T> &b);
  // friend SimpleNumber<T> simplify3(SimpleNumber<T> &a, SimpleNumber<T> &b);
  // friend bool is_one(const SimpleNumber<T> &a);
  // friend bool is_zero(const SimpleNumber<T> &a);

  // friend SimpleNumber<T> operator+(const SimpleNumber<T> &first_term,
  //                                  const SimpleNumber<T> &second_term);
  // friend SimpleNumber<T> operator-(const SimpleNumber<T> &first_term,
  //                                  const SimpleNumber<T> &second_term);
  // friend SimpleNumber<T> operator*(const SimpleNumber<T> &first_term,
  //                                  const SimpleNumber<T> &second_term);
  // // Interestingly, giac doesn't actually need this one
  // friend SimpleNumber<T> operator/(const SimpleNumber<T> &first_term,
  //                                  const SimpleNumber<T> &second_term);
  // friend SimpleNumber<T> operator-(const SimpleNumber<T> &term);
  // friend SimpleNumber<T> pow(const SimpleNumber<T> &first_term,
  //                            const SimpleNumber<T> &second_term);

private:
  T number;
};

template <typename T> SimpleNumber<T>::SimpleNumber(T newNumber) {
  number = newNumber;
}

template <typename T> T SimpleNumber<T>::get() const { return number; }

template <typename T>
SimpleNumber<T> operator+(const SimpleNumber<T> &a, const SimpleNumber<T> &b) {
  return SimpleNumber(a.get() + b.get());
}
template <typename T>
SimpleNumber<T> operator-(const SimpleNumber<T> &a, const SimpleNumber<T> &b) {
  return SimpleNumber(a.get() - b.get());
}
template <typename T> SimpleNumber<T> operator-(const SimpleNumber<T> &term) {
  return SimpleNumber(-term.get());
}
template <typename T>
SimpleNumber<T> operator*(const SimpleNumber<T> &a, const SimpleNumber<T> &b) {
  return SimpleNumber(a.get() * b.get());
}
template <typename T>
bool operator>(const SimpleNumber<T> &a, const SimpleNumber<T> &b) {
  return a.get() > b.get();
}
template <typename T>
bool operator<(const SimpleNumber<T> &a, const SimpleNumber<T> &b) {
  return a.get() < b.get();
}
template <typename T>
bool operator==(const SimpleNumber<T> &a, const SimpleNumber<T> &b) {
  return a.get() == b.get();
}
template <typename T>
bool operator>=(const SimpleNumber<T> &a, const SimpleNumber<T> &b) {
  return a.get() >= b.get();
}
template <typename T>
bool operator<=(const SimpleNumber<T> &a, const SimpleNumber<T> &b) {
  return a.get() <= b.get();
}
template <typename T>
bool operator!=(const SimpleNumber<T> &a, const SimpleNumber<T> &b) {
  return a.get() != b.get();
}
template <typename T>
SimpleNumber<T> pow(const SimpleNumber<T> &a, const SimpleNumber<T> &b) {
  return SimpleNumber(std::pow(a.get(), b.get()));
}

template <typename T> bool is_one(const SimpleNumber<T> &a) {
  return a.get() == 1;
}
template <typename T> bool is_zero(const SimpleNumber<T> &a) {
  return a.get() == 0;
}
template <typename T> T find_gcd(T a, T b) {
  while (b != 0) {
    T temp = b;
    b = a % b;
    a = temp;
  }

  return a;
}

template <typename T>
SimpleNumber<T> simplify(SimpleNumber<T> &a, SimpleNumber<T> &b) {
  bool is_negative = b.get() < 0;
  T gcd = find_gcd(std::abs(a.get()), std::abs(b.get()));

  a = SimpleNumber<T>(a.get() / gcd);
  b = SimpleNumber<T>(b.get() / gcd);

  if (is_negative) {
    a = -a;
    b = -b;
  }

  return SimpleNumber<T>(gcd);
}

template <typename T>
inline SimpleNumber<T> simplify3(SimpleNumber<T> &a, SimpleNumber<T> &b) {
  return simplify<T>(a, b);
}
template <typename T>
std::string SimpleNumber<T>::print(const giac::context *) {
  return std::to_string(get());
}
template <typename T>
std::basic_ostringstream<wchar_t> &
operator<<(std::basic_ostringstream<wchar_t> &os,
           const SimpleNumber<T> &number) {
  os << number.get();
  return os;
}

template <typename T> double to_double(giac::Tfraction<SimpleNumber<T>> term) {
  return (double)term.num.get() / (double)term.den.get();
}
} // namespace mathlib

#endif // FRACTION_H
