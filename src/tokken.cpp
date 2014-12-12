/*
 * tokken.cpp
 *
 *  Created on: Dec 10, 2014
 *      Author: colinl
 */
#include "tokken.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>

extern bool INGROUP;

void find_node(Tokken& tokken, bool& isgroup, bool& search_name,
				std::vector<PNode>& list_node, int& n_line)
{
	if(!isgroup){
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
		else if(tokken.first_word == "Group" && INGROUP == true){
			PNode node = PNode(tokken.first_word, n_line);
			list_node.push_back(node);
			isgroup = true;
			search_name = true;
		}
		else{
			return;
		}
	}
	else{
		if(tokken.first_word == "name" && search_name == true){
			list_node[list_node.size()-1].name = tokken.second_word;
			search_name = false;
			return;
		}
		else if(tokken.first_word == "end_group"){
				isgroup = false;
				search_name = false;
				list_node[list_node.size()-1].last_line = n_line;
				return;
		}
		else{
			return;
		}
	}
}

Tokken get_tokken(const std::string& line){
	std::istringstream iss(line);
	Tokken tokken;
	iss >> tokken.first_word >> tokken.second_word;
	return tokken;
}

std::vector<PNode> parse_nk(const char* file){
	std::ifstream infile;
	infile.open(file);
	std::string line;

	bool isgroup = false;
	bool search_name = false;

	std::string name;
	std::vector<PNode> list_node;
	int n_line = 1;

	while (getline(infile, line))
	{
		Tokken tokken = get_tokken(line);
		find_node(tokken, isgroup, search_name, list_node, n_line);
		n_line++;
	}
	return list_node;
}

void comment_line(const char* in_file, const char* out_file, std::vector<PNode> list_node)
{
	std::ifstream in_data;
	in_data.open(in_file);
	std::ofstream out_data;
	out_data.open(out_file);
	std::string line;
	int n_line = 1;
	std::vector<int> comment_lines;
	for(int i = 0; i<int(list_node.size()); i++){
		for(int j = list_node[i].first_line; j<=list_node[i].last_line; j++){
			comment_lines.push_back(j);
		}
	}

	while (getline(in_data, line))
	{
		std::vector<int>::iterator it = std::find(comment_lines.begin(), comment_lines.end(), n_line);
		if( it != comment_lines.end()){
			out_data << "#" << line << std::endl;
			n_line++;
		}
		else{
			out_data << line << std::endl;
			n_line++;
		}
	}
	out_data.close();
	in_data.close();
	std::ifstream in_dataf(out_file);
	std::ofstream out_dataf(in_file);
	out_dataf << in_dataf.rdbuf();
}

void remove_nodes_nk(const char* nk_file, std::string node_name, bool node_class){
	if(node_name == ""){
		std::cerr<<"bad arguments values"<<std::endl;
		return;
	}
	std::vector<PNode> list_node = parse_nk(nk_file);
	std::vector<PNode> del_list;
	for(int i = 0; i<int(list_node.size()); i++){
		if( node_class ) {
			if(list_node[i].class_type.compare(node_name) == 0){
				del_list.push_back(list_node[i]);
			}
		}
		else{
			if(list_node[i].name == node_name){
				del_list.push_back(list_node[i]);
			}
		}
	}
	comment_line(nk_file, "/tmp/del_node.nk.new", del_list);
	for(int i = 0; i<int(del_list.size()); i++){
		std::cerr<<del_list[i].class_type<< "-" << del_list[i].name <<" -- commented" <<std::endl ;
	}
}

