/*
 * 	FICHEIRO: TreeNode.h
 *	PROJECTO: Projecto2 CAL - Data Compression (T2)
 *  TURMA / GRUPO: Turma 2MIEIC2 / Grupo D
 *  AUTORES:
 *  - Jorge Miguel Reis
 *  - Miao Sun
 *  - Vitor Castro
 */

#ifndef TREENODE_H_
#define TREENODE_H_

#include <string>

using namespace std;

class Node {
	bool leaf;
	int freq;
	unsigned char caracter;
	Node *right, *left;
public:
	Node();
	Node(unsigned char c, int f);
	void setRight(Node* r);
	void setLeft(Node* l);
	void setFreq(int f);
	Node* getRight();
	Node* getLeft();
	int getFreq();
	unsigned char getCaracter();
	bool isLeaf();
};
#endif /* TREENODE_H_ */
