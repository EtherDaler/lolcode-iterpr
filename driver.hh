#pragma once

#include <map>
#include <string>
#include <fstream>
#include <vector>
#include "scanner.h"
#include "parser.hh"
#include "runtime.h"

struct Operator;


class Driver {
 public:
    Driver();
    std::map<std::string, int> variables;
    int result;
    int parse(const std::string& file_name);
    std::string file;


    void scan_begin();
    void scan_end();


    bool trace_parsing;
    bool trace_scanning;
    yy::location location;

    friend class Scanner;
    Scanner scanner;
    yy::parser parser;
    bool location_debug;

    void print(const Value& value);
    void addOp(Operator* oper);
    void input(Value& value);
    std::vector<Operator*> ops;
 private:
    std::ifstream stream;

};
