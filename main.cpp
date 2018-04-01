#include <iostream>
#include <fstream>
#include <getopt.h>

#include "tree.h"

int main(int argc, char* argv[]) {
  std::string input_file;
  std::string output_file;

  if (argc < 5) {
    std::cout << "-i      input  file" << std::endl;
    std::cout << "-o      output file" << std::endl;
    return 0;
  }

  int opt;
  while ( (opt = getopt(argc, argv, "i:o:")) != -1 ) {
    switch (opt) {
      case 'i':
        input_file = optarg;
        break;
      case 'o':
        output_file = optarg;
        break;
      default:
        std::cout << "-i      input  file" << std::endl;
        std::cout << "-o      output file" << std::endl;
        return 0;
    }
  }

  Tree tree;

  std::ifstream in_stream(input_file);
  tree.Deserialize(in_stream);

  tree.PrintTree();

  std::ofstream stream(output_file);
  tree.Serialize(stream);

  return 0;
}