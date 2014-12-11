/*
 * tokken.h
 *
 *  Created on: Dec 10, 2014
 *      Author: colinl
 */

#ifndef TOKKEN_H_
#define TOKKEN_H_
#include <string>
#include <vector>


class Tokken {
public :
	std::string first_word;
	std::string second_word;
	Tokken(){}
	Tokken(std::string fword) : first_word(fword){}
	Tokken(std::string fword, std::string sword) : first_word(fword), second_word(sword){}
};

class PNode {
public :
	std::string class_type;
	std::string name;
	int first_line;
	int last_line;
	PNode(){}
	PNode(std::string class_type, int fline) : class_type(class_type), first_line(fline){}
};

void find_node(Tokken&, bool&, bool&, std::vector<PNode>&, int&);
Tokken get_tokken(const std::string&);
std::vector<PNode> parse_nk(const char*);
void comment_line(const char*, const char*, std::vector<PNode>);
void remove_nodes_nk(const char*, std::string, bool);

#endif /* TOKKEN_H_ */

