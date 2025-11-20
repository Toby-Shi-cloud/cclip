# CCLIP

CCLIP stands for Compile-Time CLI Parser

## Quick Start

To use CCLIP, you only need to include `cclip/cclip.hpp` and define a argument struct!
```cpp
#include <cclip/cclip.hpp>

struct Argument {
    std::string infile;
    int level = 0;
    bool verbose = false;
};

int main(int argc, char *argv[]) {
    auto parser = cclip::build_parser<Argument>();
    Argument arg;
    try {
        parser.parse(argc, argv, arg);
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        std::cout << parser.help() << std::endl;
        return -1;
    }
    // use arg.infile, arg.level and arg.verbose to access the argument directly.
}
```

## Motivation

Suppose we need to parse cli agruments to a struct, e.g.
```cpp
struct Argument {
    std::string infile;
    std::string outfile;
    int arg1, arg2;
    bool opt1, opt2;
    //...
};
```
Existing cli parsers often have two approachs to do so:

1. Create a instance of `struct Argument` and then build the parser with certain actions. e.g.
```cpp
// @see: https://github.com/muellan/clipp
using namespace clipp;

auto cli = (
    value("input file", arg.infile),
    option("-r", "--recursive").set(arg.rec).doc("convert files recursively"),
    option("-o") & value("output file", arg.outfile),
    option("-utf16").set(arg.utf16).doc("use UTF-16 encoding")
);

if(!parse(argc, argv, cli)) cout << make_man_page(cli, argv[0]);
```
2. Build the parser first, use `parser["name"]` to access the arguments parsed, and convert to `struct Argument`. e.g.
```cpp
// @see https://github.com/p-ranav/argparse
argparse::ArgumentParser program("program_name");

program.add_argument("value")
    .help("display the square of a given integer")
    .scan<'i', int>();

try {
    program.parse_args(argc, argv);
} catch (const std::exception& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
}

return Argument{.value = program.get<int>("value")};
```

Both of the two appoachs need to write names of arguments at least twice!

Let see another appoach provide by [rust clap](https://docs.rs/clap/latest/clap/):
```rust
use clap::Parser;

/// Simple program to greet a person
#[derive(Parser, Debug)]
#[command(version, about, long_about = None)]
struct Args {
    /// Name of the person to greet
    #[arg(short, long)]
    name: String,

    /// Number of times to greet
    #[arg(short, long, default_value_t = 1)]
    count: u8,
}

fn main() {
    let args = Args::parse();

    for _ in 0..args.count {
        println!("Hello {}!", args.name);
    }
}
```

The users only need to define the struct!
Though Rust have proc-macro, c++ have much more flexible macro and **reflection**!
