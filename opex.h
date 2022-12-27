#include "runtime.h"

struct Expression {
  virtual Value eval() = 0;
  virtual ~Expression() = default;
};

struct Operator {
  virtual void exec() = 0;
  virtual ~Operator() = default;
};