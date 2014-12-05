
//============================================================================
// Name        : parse.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include <locale>
#include <boost/foreach.hpp>

using namespace std;

class Tokken {
public :
	string first_word;
	string second_word;
	Tokken(){}
	Tokken(string fword) : first_word(fword){}
	Tokken(string fword, string sword) : first_word(fword), second_word(sword){}
};

class PNode {
public :
	string name;
	int first_line;
	int last_line;
	PNode(){}
	PNode(string name) : name(name){}
};

void find_node(const string& line, string& node, bool& isgroup, bool& search_name, vector<string>& list_node){
	istringstream iss(line);
	Tokken tokken;
	iss >> tokken.first_word >> tokken.second_word;
	if(!isgroup){
		if(tokken.second_word == "{" && tokken.first_word != "Group"){
			node = tokken.first_word;
			list_node.push_back(node);
		}
		if(tokken.first_word == "Group"){
			isgroup = true;
			search_name = true;
		}
	}
	if(tokken.first_word == "end_group"){
		isgroup = false;
		search_name = false;
	}
}

void work_group(const string& line, bool& search_name, string& name){
	istringstream iss(line);
	Tokken tokken;
	iss >> tokken.first_word >> tokken.second_word;
	if(tokken.first_word == "name" && search_name == true){
		search_name = false;
		name = tokken.second_word;
	}
}

int main() {

	string node;
	ifstream infile;
	infile.open("/u/colinl/testnk.nk");
	string line;
	bool isgroup = false;
	bool search_name;
	string name;
	vector<string> list_name;
	vector<string> list_node;

	while (getline(infile, line))
	{
			find_node(line, node, isgroup, search_name, list_node);
			if(isgroup){
				work_group(line, search_name, name);
				list_name.push_back(name);
			}
	}
	set<string> set_name(list_name.begin(), list_name.end());
	BOOST_FOREACH(string element, set_name) {
		list_node.push_back(element);
	}
	for(int i; i<int(list_node.size()); i++){
		cout<<list_node[i]<<endl;
	}
}
