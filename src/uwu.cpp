#include "parser.h"
#include "lexer.h"
#include "lexerUtils.h"
#include "llvm/Support/raw_os_ostream.h"

#include <iostream>
#include <string>
#include <fstream>


int main(int argc, char **argv) {

  if (argc != 2) {
    std::cout << "Usage : uwu <filename>" << std::endl;
    return -1;
  }

  naruto::sModule = llvm::make_unique<llvm::Module>("module", naruto::sContext);
  std::vector<naruto::Lex> stream = naruto::naruto_lexize_file(argv[1]);

  naruto::ASTRoot f;
  f.parse(stream, 0);
  // f.print();
  f.generate();

  std::string filename = argv[1];
  auto base = filename.substr(0, filename.length() - 3);


  std::string llvm_file = base + "ll";

  std::ofstream std_file_stream(llvm_file);
  llvm::raw_os_ostream file_stream(std_file_stream);
  naruto::sModule->print(file_stream, nullptr);
}
