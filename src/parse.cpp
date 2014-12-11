
//============================================================================
// Name        : parse.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "tokken.h"
#include <iostream>

int main(int argc, char* argv[])
{
	std::string node = argv[2];
	std::string typen = "-node";
	std::string arg = argv[3];
	bool type = false;
	if(arg.compare(typen)){
		type = true;
	}
	std::cerr<<type;
	const char* path = argv[1];
	remove_nodes_nk(path, node, !type);
	return 1;
}
