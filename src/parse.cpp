
//============================================================================
// Name        : parse.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "tokken.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
bool INGROUP;

int main(int argc, char* argv[])
{
	INGROUP = true;

	std::string typen = "-node";
	std::string typena = "-name";
	std::string typein = "-ingroup";

	const char* path = argv[1];
	std::string node = argv[2];
	std::string arg = argv[3];

	std::ifstream file(argv[1]);
	if(!file){
		std::cerr<<"Can't open file"<<std::endl;
		std::cerr<<"Abort"<<std::endl;
		return 0;
	}

	struct stat results;
	stat(argv[1], &results);
	if (results.st_mode & S_IRUSR)
	    std::cerr << "Read permission only"<<std::endl;
		std::cerr<<"Abort"<<std::endl;
		return 0;

	if(argc > 4){
		std::string argg = argv[4];
		if(!argg.compare(typein)){
			INGROUP = false;
		}
		else{
			std::cerr<<"At 3, Bad flag, use -ingroup"<<std::endl;
			std::cerr<<"Abort"<<std::endl;
			return 0;
		}
	}

	bool type = false;

	if(!arg.compare(typen)){
		type = true;
	}
	else if(!arg.compare(typena)){
		type = false;
	}
	else{
		std::cerr<<"At 2, Bad flag, use -node or -name"<<std::endl;
		std::cerr<<"Abort"<<std::endl;
		return 0;
	}


	remove_nodes_nk(path, node, type);
	return 1;
}
