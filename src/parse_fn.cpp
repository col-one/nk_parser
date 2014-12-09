/*
 * parse_fn.cpp
 *
 *  Created on: 9 déc. 2014
 *      Author: Fanny
 */
#include "parse_fn.h"
#include <vector>
using namespace std;

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
	for(int i; i<int(list_node.size()); i++){
		ifstream in_data;
		in_data.open(in_file);
		ofstream out_data;
		out_data.open(out_file);
		string line;
		int n_line = 1;
		while (getline(in_data, line))
		{
			if(n_line < list_node[i].first_line || n_line > list_node[i].last_line){
				out_data << line << endl;
			}
			n_line++;
		}
	    remove(in_file);
	    rename(out_file, in_file);
	}
}

void remove_nodes_nk(const char* nk_file, string node_name, string node_class){
	if(node_name == "" && node_class == ""){
		cerr<<"bad arguments values"<<endl;
		return;
	}
	vector<PNode> list_node = parse_nk(nk_file);
	vector<PNode> del_list;
	if(node_name != "" && node_class == ""){
		for(int i; i<int(list_node.size()); i++){
			if(list_node[i].name == node_name){
				del_list.push_back(list_node[i]);
			}
		}
	}
	if(node_name == "" && node_class != ""){
		for(int i; i<int(list_node.size()); i++){
			if(list_node[i].class_type == node_class){
				del_list.push_back(list_node[i]);
			}
		}
	}
	if(node_name != "" && node_class != ""){
		cerr<<"choose node_name or node_class"<<endl;
		return;
	}
	copy_line(nk_file, "/tmp/del_node.nk.new", del_list);
}
