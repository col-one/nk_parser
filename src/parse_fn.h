/*
 * parse_fn.h
 *
 *  Created on: 9 déc. 2014
 *      Author: Fanny
 */

#ifndef PARSE_FN_H_
#define PARSE_FN_H_


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

void find_node(Tokken, bool, bool, vector<PNode>, int);

Tokken get_tokken(const string);

vector<PNode> parse_nk(const char*);

void copy_line(const char*, const char*, vector<PNode>);

void remove_nodes_nk(const char*, string, string);

#endif /* PARSE_FN_H_ */
