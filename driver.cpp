#include <iostream>

#include "driver.hh"
#include "parser.hh"



Driver::Driver() :
    trace_parsing(false),
    trace_scanning(false),
    location_debug(false),
    scanner(*this), parser(scanner, *this) {
    variables["one"] = 1;
    variables["two"] = 2;
}


int Driver::parse(const std::string& file_name) {
    file = file_name;
    // initialize location positions
    location.initialize(&file);
    scan_begin();
    parser.set_debug_level(trace_parsing);
    int res = parser();
    scan_end();
    return res;
}

void Driver::scan_begin() {
    scanner.set_debug(trace_scanning);
  if (file.empty () || file == "-") {
  } else {
    stream.open(file);
    std::cerr << "File name is " << file << std::endl;

    // Restart scanner resetting buffer!
    scanner.yyrestart(&stream);
  }
}

void Driver::scan_end()
{
    stream.close();
}

void Driver::print(const Value& value) {
  std::cout << value << '\n';
}

void Driver::input(Value& value) {
  std::cin >> value;
}

void Driver::addOp(Operator* oper) {
  ops.push_back(oper);
}

