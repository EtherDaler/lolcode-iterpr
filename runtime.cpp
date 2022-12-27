#include "runtime.h"
#include <iostream>

struct Sum {
  static int calc(int a, int b) {
    return a + b;
  }

  static float calc(float a, float b) {
    return a + b;
  }
};

struct Minus {
  static int calc(int a, int b) {
    return a - b;
  }

  static float calc(float a, float b) {
    return a - b;
  }
};

struct Mul {
  static int calc(int a, int b) {
    return a * b;
  }

  static float calc(float a, float b) {
    return a * b;
  }
};

struct Div {
  static int calc(int a, int b) {
    return a / b;
  }

  static float calc(float a, float b) {
    return a / b;
  }
};

struct Mod {
  static int calc(int a, int b) {
    return a % b;
  }
};

struct Max {
  static int calc(int a, int b) {
    return std::max(a, b);
  }

  static float calc(float a, float b) {
    return std::max(a, b);
  }
};

struct Min {
  static int calc(int a, int b) {
    return std::min(a, b);
  }

  static float calc(float a, float b) {
    return std::min(a, b);
  }
};

struct And {
  static int calc(int a, int b) {
    return a != 0 && b != 0;
  }
};

struct Or {
  static int calc (int a, int b) {
    return a != 0 || b != 0;
  }
};

///////////////////////////////////////////////////////////////////////////////

Value::Value(int i): integer(new int(i)) { }
Value::Value(float f): flt(new float(f)) { }
Value::Value(const std::string& s): str(new std::string(s)) { }
Value::Value(const Value& value) {
  copyFrom(value);
}

Value& Value::operator=(const Value& other) {
  if (this != &other) {
    copyFrom(other);
  }
  return *this;
}

Value Value::operator+(const Value& other) const {
  return execute<Sum>(other);
}

Value Value::operator-(const Value& other) const {
  return execute<Minus>(other);
}

Value Value::operator*(const Value& other) const {
  return execute<Mul>(other);
}

Value Value::operator/(const Value& other) const {
  return execute<Div>(other);
}

Value Value::operator%(const Value& other) const {
  return execute<Mod>(other);
}

Value Value::min(const Value& other) const {
  return execute<Min>(other);
}
Value Value::max(const Value& other) const {
  return execute<Max>(other);
}

Value Value::operator&&(const Value& other) const {
  return execute<And>(other);
}

Value Value::operator||(const Value& other) const {
  return execute<Or>(other);
}

Value Value::operator!() const {
  if (integer) {
    return !integer;
  }
  if (str) {
    return str->empty();
  }
  return Value();
}

Value::~Value() {
  delete integer;
  delete flt;
  delete str;
}

static int toInt(std::string* data) {
  if (data->empty()) {
    return 0;
  }
  return std::stoi(*data);
}

static float toFloat(std::string* data) {
  if (data->empty()) {
    return 0;
  }
  return std::stof(*data);
}

template <class T>
Value Value::execute(const Value& value) const {
  if (integer) {
    if (value.integer) {
      return Value(T::calc(*integer, *value.integer));
    }
    else if (value.flt) {
      return Value(T::calc((float) *integer, *value.flt));
    }
    else {
      return Value(T::calc(*integer, toInt(value.str)));
    }
  } else if (flt) {
    if (value.flt) {
      return Value(T::calc(*flt, *value.flt));
    }
    else if (value.integer) {
      return Value(T::calc(*flt, (float) *value.integer));
    }
    else {
      return Value(T::calc(*flt, toFloat(value.str)));
    }
  } else if (str && value.str) {
    return Value(T::calc(toInt(str), toInt(value.str)));
  }
  else {
    return value + *this;
  }
}

void Value::copyFrom(const Value& value) {
  if (value.integer) {
    integer = new int(*value.integer);
  }
  if (value.flt) {
    flt = new float(*value.flt);
  }
  if (value.str) {
    str = new std::string(*value.str);
  }
}

std::ostream& operator<<(std::ostream& os, const Value& value) {
  if (value.integer) {
    return os << *value.integer;
  }
  if (value.flt) {
    return os << *value.flt;
  }
  if (value.str) {
    return os << *value.str;
  }
  return os;
}

std::istream& operator>>(std::istream& stream, Value& value) {
  if (value.integer) {
    return stream >> *value.integer;
  }
  if (value.flt) {
    return stream >> *value.flt;
  }
  if (value.str) {
    return stream >> *value.str;
  }
  return stream;
}

Value::operator bool() const {
  if (integer) {
    return *integer;
  }  
  if (str) {
    return !str->empty();
  }
  return false;
}

Runtime::~Runtime() {
  std::cout << "\nStack:\n";
  for (auto& v : vars) {
    std::cout << v.first << " = " << v.second << '\n';
  }
}
