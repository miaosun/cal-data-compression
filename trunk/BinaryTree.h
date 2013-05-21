/*
 * BinaryTree.h
 *
 *  Created on: 20 de Mai de 2013
 *      Author: Reis
 */

#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include <string>

using namespace std;

struct caracter {
	unsigned char caracter;
	string bin;
};


class Node {
	bool leaf;
	int freq;
	unsigned char caracter;
	Node *right, *left;
public:
	Node();
	Node(unsigned char c, int f);
	//void addNode(Node* n);
	void setRight(Node* r);
	void setLeft(Node* l);
	Node* getRight();
	Node* getLeft();
	int getFreq();
	unsigned char getCaracter();
	bool isLeaf();
};


#endif /* BINARYTREE_H_ */
