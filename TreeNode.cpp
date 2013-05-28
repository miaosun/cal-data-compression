/*
 * 	FICHEIRO: TreeNode.cpp
 *	PROJECTO: Projecto2 CAL - Data Compression (T2)
 *  TURMA / GRUPO: Turma 2MIEIC2 / Grupo D
 *  AUTORES:
 *  - Jorge Miguel Reis
 *  - Miao Sun
 *  - Vitor Castro
 */

#include "TreeNode.h"

Node::Node(): right(0), left(0) {
	freq=0;
	leaf=false;
}

Node::Node(unsigned char c, int f): right(0), left(0) {
	caracter=c;
	freq=f;
	leaf=true;
}

Node* Node::getRight() {
	return right;
}
void Node::setRight(Node* n) {
	right = n;
}
Node* Node::getLeft() {
	return left;
}
void Node::setLeft(Node* n) {
	left=n;
}
int Node::getFreq() {
	return freq;
}
void Node::setFreq(int f) {
	freq=f;
}
unsigned char Node::getCaracter() {
	return caracter;
}
bool Node::isLeaf() {
	return leaf;
}
