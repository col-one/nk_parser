
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
	string class_type;
	string name;
	int first_line;
	int last_line;
	PNode(){}
	PNode(string class_type, int fline) : class_type(class_type), first_line(fline){}
};

void find_node(Tokken& tokken, bool& isgroup, bool& search_name,
		vector<PNode>& list_node, int& n_line){
	if(tokken.second_word == "{" && tokken.first_word != "Group"){
		PNode node = PNode(tokken.first_word, n_line);
		list_node.push_back(node);
	}
	else if(tokken.first_word == "}"){
		if(list_node.empty()){
			return;
		}
		else{
			list_node[list_node.size()-1].last_line = n_line;
		}
	}
	else if(tokken.first_word == "name"){
		list_node[list_node.size()-1].name = tokken.second_word;
	}
	else if(tokken.first_word == "Group"){
		isgroup = true;
		search_name = true;
	}
	else if(tokken.first_word == "end_group"){
		isgroup = false;
		search_name = false;
	}
	else{
		return;
	}
}

Tokken get_tokken(const string& line){
	istringstream iss(line);
	Tokken tokken;
	iss >> tokken.first_word >> tokken.second_word;
	return tokken;
}

/*
void work_group(const string& line, bool& search_name, string& name){
	istringstream iss(line);
	Tokken tokken;
	iss >> tokken.first_word >> tokken.second_word;
	if(tokken.first_word == "name" && search_name == true){
		search_name = false;
		name = tokken.second_word;
	}
}
*/
vector<PNode> parse_nk(const char* file){
	ifstream infile;
	infile.open(file);
	string line;

	bool isgroup = false;
	bool search_name;

	string name;
	vector<PNode> list_node;
	int n_line = 1;

	while (getline(infile, line))
	{
		Tokken tokken = get_tokken(line);
		find_node(tokken, isgroup, search_name, list_node, n_line);
		n_line++;
	}
	return list_node;
}

void copy_line(const char* in_file, const char* out_file, vector<PNode> list_node)
{

	int offset_line = 0;
	for(int i = 0; i<int(list_node.size()); i++){

		ifstream in_data;
		in_data.open(in_file);
		ofstream out_data;
		out_data.open(out_file);

		string line;
		int n_line = 1;
		while (getline(in_data, line))
		{
			if(n_line < (list_node[i].first_line - offset_line) || n_line > (list_node[i].last_line - offset_line)){
				out_data << line << endl;
			}
			n_line++;
		}
		offset_line += list_node[i].last_line - list_node[i].first_line;
		out_data.close();
		in_data.close();
	    remove(in_file);
	    rename(out_file, in_file);
	    //remove(out_file);
	}
}
//void remove_nodes_nk(const char* nk_file, string node_name="", bool node_class=true);
void remove_nodes_nk(const char* nk_file, string node_name, bool node_class){
	if(node_name == ""){
		cerr<<"bad arguments values"<<endl;
		return;
	}
	vector<PNode> list_node = parse_nk(nk_file);
	vector<PNode> del_list;
	for(int i = 0; i<int(list_node.size()); i++){
		//if( node_class ) {
			if(list_node[i].class_type.compare(node_name) == 0){
				del_list.push_back(list_node[i]);
			}
		//}
		//else{
			//if(list_node[i].name == node_name){
				//del_list.push_back(list_node[i]);
			//}
		//}
	}
	for(int i = 0; i<int(del_list.size()); i++){
		cerr<<del_list[i].class_type;
	}
	copy_line(nk_file, "/u/colinl/del_node.nk.new", del_list);
}

int main(int argc, char *argv[])
{
	remove_nodes_nk("/u/colinl/testnk.nk", string("Reformat"), true);
	return 1;
}
