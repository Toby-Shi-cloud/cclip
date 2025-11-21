#include <cclip/cclip.hpp>
#include <iostream>

using namespace cclip::option_builder;

struct Argument {
  Option<std::string, LONG | SHORT, required> infile;
  Option<int, LONG | SHORT, shortf('L')> level = 0;
  Option<bool, LONG | SHORT> verbose = false;
  Option<std::vector<float>, LONG | SHORT> floats;
};

int main(int argc, char *argv[]) {
  auto parser = cclip::Parser<Argument>::build();
  Argument arg;
  try {
    parser.parse(argc, argv, arg);
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
    std::cout << parser.help(argv[0]) << std::endl;
    return -1;
  }
  // use arg.infile, arg.level and arg.verbose to access the argument directly.
  std::cout << "infile = " << arg.infile.get() << std::endl;
  std::cout << "level = " << arg.level << std::endl;
  std::cout << "verbose = " << arg.verbose << std::endl;
  std::cout << "floats = {";
  for (std::string_view sv = ""; auto f : arg.floats.get()) std::cout << sv << f, sv = ", ";
  std::cout << "}" << std::endl;
  return 0;
}
