#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <type_traits>
#include <functional>

struct Value {
  int* integer = nullptr; // int value
  float* flt = nullptr;   // float value
  std::string* str = nullptr;  // string value

  Value() = default;
  Value(int i);
  Value(float f);
  Value(const std::string& s);
  Value(const Value& other);

  Value& operator=(const Value& other);
  Value operator+(const Value& other) const;
  Value operator-(const Value& other) const;
  Value operator*(const Value& other) const;
  Value operator/(const Value& other) const;
  Value operator%(const Value& other) const;
  Value operator&&(const Value& other) const;
  Value operator||(const Value& other) const;

  Value operator!() const;

  Value min(const Value& other) const;
  Value max(const Value& other) const;

  explicit operator bool() const;

  ~Value();

  friend std::ostream& operator<<(std::ostream& os, const Value& value);
  friend std::istream& operator>>(std::istream& stream, Value& value);
private:
  template <class T>
  Value execute(const Value& value) const;
  void copyFrom(const Value& value);
};

class Runtime {
public:
  ~Runtime();
  std::unordered_map<std::string, Value> vars;
};