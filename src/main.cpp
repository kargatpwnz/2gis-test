#include <iostream>
#include <fstream>

#include <boost/program_options.hpp>
#include <getopt.h>

#include "tree.h"

namespace opt = boost::program_options;

int main(int argc, char * argv[]) {
	std::string input_file;
	std::string output_file;

	opt::options_description desc("App options");

	desc.add_options()
			(",i", opt::value<std::string>(&input_file)->required(), "input file")
			(",o", opt::value<std::string>(&output_file)->required(), "output file")
			(",h", "help message");

	opt::variables_map vm;
	opt::store(opt::parse_command_line(argc, argv, desc), vm);

	if (vm.count("-h")) {
		std::cout << desc << std::endl;
		return 0;
	}

	try {
		opt::notify(vm);
	}
	catch (const opt::required_option & e) {
		std::cerr << "Error: " << e.what() << "\n\n";
		std::cerr << desc << std::endl;
		return -1;
	}

	Tree tree;

	std::ifstream in_stream(input_file);
	tree.Deserialize(in_stream);

	tree.PrintTree();

	std::ofstream stream(output_file);
	tree.Serialize(stream);

	return 0;
}
