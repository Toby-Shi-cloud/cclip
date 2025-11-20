#include <cclip/cclip.hpp>
#include <iostream>

struct Argument {
  std::string infile;
  int level = 0;
  bool verbose = false;
  std::vector<float> floats;
};

int main(int argc, char *argv[]) {
  auto parser = cclip::Parser<Argument>::build()
                    .set_alias("infile", 'i')
                    .require('i')
                    .set_alias("level", 'L')
                    .set_alias("verbose", 'v')
                    .set_alias("floats", 'f');
  Argument arg;
  try {
    parser.parse(argc, argv, arg);
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
    std::cout << parser.help() << std::endl;
    return -1;
  }
  // use arg.infile, arg.level and arg.verbose to access the argument directly.
  std::cout << "infile = " << arg.infile << std::endl;
  std::cout << "level = " << arg.level << std::endl;
  std::cout << "verbose = " << arg.verbose << std::endl;
  std::cout << "floats = {";
  for (std::string_view sv = ""; auto f : arg.floats) std::cout << sv << f, sv = ", ";
  std::cout << "}" << std::endl;
  return 0;
}
