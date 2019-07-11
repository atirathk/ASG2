// $Id: main.cpp,v 1.9 2016-01-14 16:16:52-08 - - $

#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <unistd.h>
#include <fstream>
using namespace std;

#include "commands.h"
#include "debug.h"
#include "file_sys.h"
#include "util.h"

// scan_options
//    Options analysis:  The only option is -Dflags. 

//void scan_options(int argc, char** argv) {
//	opterr = 0;
//	for (;;) {
//		int option = getopt(argc, argv, "@:");
//		if (option == EOF) break;
//		switch (option) {
//		case '@':
//			debugflags::setflags(optarg);
//			break;
//		default:
//			complain() << "-" << static_cast<char> (option)
//				<< ": invalid option" << endl;
//			break;
//		}
//	}
//	if (optind < argc) {
//		complain() << "operands not permitted" << endl;
//	}
//}


// main -
//    Main program which loops reading commands until end of file.

int main(int argc, char** argv) {
	base_file_ptr dir;
	vector<string> sv;
	sv.push_back("This is some random stuff\n");
	sv.push_back("don't know what else to say\n");
	dir->mkfile("newFile");
	return 0;
}

//add_executable(ASG2 "testClient.cpp", "file_sys.cpp", "file_sys.h", "debug.cpp", "debug.h", "util.cpp", "util.h", "commands.cpp", "commands.h", "main.cpp")
