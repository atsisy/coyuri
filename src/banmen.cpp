#include "../include/type.hpp"
#include <iostream>

BANMEN::BANMEN(){
	banmen = new KOMA_TYPE *[9];
      for(int i = 0;i < 9;i++)
		banmen[i] = new KOMA_TYPE[9];
}

BANMEN::~BANMEN(){
	for(int i = 0;i < 9;i++)
		delete[] banmen[i];
}

KOMA_TYPE BANMEN::get_type(int x, int y){
	return banmen[x][y];
}

void BANMEN::set_type(int x, int y, KOMA_TYPE type){
	banmen[x][y] = type;
}

void BANMEN::copy_banmen(BANMEN *original){
	for(int x = 0;x < 9;x++){
		for(int y = 0;y < 9;y++){
			banmen[x][y] = original->get_type(x, y);
		}
	}
}

Point BANMEN::find_koma(KOMA_TYPE type){
	for(int x = 0;x < 9;x++)
		for(int y = 0;y < 9;y++)
			if(banmen[x][y] == type) return Point(x, y);

	/*
	 *見つからないときは(-1, -1)を返す
	 */
	return Point(-1, -1);
}

Node::~Node(){
	if(!children.empty()){
		for(Node *child : children){
			delete child->get_banmen();
		}
	}
}

Node::Node(BANMEN *ban, Node *pare){
	banmen = ban;
	parent = pare;
}

BANMEN *Node::get_banmen(){
	return banmen;
}

std::vector<Node *> *Node::get_children(){
	return &children;
}

int Node::get_evalue(){
	return evalue;
}

void Node::set_evalue(int value){
	evalue = value;
}

void destroy_tree(Node *root){
	for(Node *node : *root->get_children()){
		if(node->get_children()->empty()){
			std::cout << "delete\n";
			delete node->get_banmen();
		}else{
			destroy_tree(node);
		}
	}
}
