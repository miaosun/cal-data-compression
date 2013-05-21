/*
 * huffmanCode.cpp
 *
 *  Created on: 17 de Mai de 2013
 *      Author: Reis
 */


#include <iostream>
#include <vector>
#include <fstream>
#include "codec.h"
#include "BinaryTree.h"

using namespace std;

bool compareNodes(Node* n1, Node* n2) {
	return n1->getFreq()<n2->getFreq();
}

HuffmanCode::HuffmanCode(string file) : Codec(file) {
	initFreqs();
}

void HuffmanCode::initFreqs() {
	for(unsigned int i=0; i<256; i++)
		freqs[i]=0;
}

void HuffmanCode::calculaFreqs() {
	int c;
	ifstream file(getFilename().c_str());
	if(file.is_open()) {
		while(!file.eof()) {
			c=file.get();
			freqs[c]++;
		}
		file.close();
	}
}

Node* HuffmanCode::buildTree() {
	//cria vector nós
	vector<Node*> btree;
	for(unsigned int i=0; i<256; i++) {
		if (freqs[i]>0) {
			Node* n = new Node((unsigned char) i, freqs[i]);
			btree.push_back(n);
		}
	}
	sort(btree.begin(),btree.end(),compareNodes);

	while (btree.size() > 1) {
		Node* parent= new Node();
		parent->setLeft(btree[0]);
		parent->setRight(btree[1]);
		btree.erase(btree.begin());
		btree.erase(btree.begin());
		btree.push_back(parent);
		sort(btree.begin(),btree.end(),compareNodes);
	}
	return btree[0];
}

void HuffmanCode::geraReprBinaria(Node* n, string s, vector<string> &v) {
	if(n->isLeaf()) {
		cout << "leaf" << (int)n->getCaracter() << endl;
		v[(int)n->getCaracter()]=s;
	}
	else {
		if(n->getLeft()!=NULL)
			geraReprBinaria(n->getLeft(),s+"0",v);
		if(n->getRight()!=NULL)
			geraReprBinaria(n->getRight(),s+"1",v);
	}
}

void HuffmanCode::geraFicheiroCodificacao(vector<string> r) {
	string f = this->getFilename();
	int n = f.length();
	//n=n-3;
	cout << f << " " << n<< endl;
	string f2 = f.substr(0,n-2);//+"huffc";
	cout << "nome" << endl;
	ofstream cfile(f.c_str());
	cout << "aqui" << endl;
	if(cfile.is_open()) {
		for(unsigned int i=0; i<r.size(); i++) {
			if(freqs[i]>0)
				cfile << (char)freqs[i] << r[i] << endl;
		}
		cfile.close();
	}
	else
		cout << "Erro na escrita do ficheiro de informação da codificacao!" << endl;

}

void HuffmanCode::comprimir() {
	calculaFreqs();
	Node* root = buildTree();
	cout << "Arvore criada" << endl;
	vector<string> repr(256,"");
	//gera vector com as representações
	geraReprBinaria(root,"",repr);
	cout << "Repr binaria" << endl;
	geraFicheiroCodificacao(repr);
	cout << "Ficheiro cod" << endl;
	string f = (getFilename().substr(0,getFilename().length()-3))+"huff";

	int c;
	ifstream file(getFilename().c_str());
	ofstream codedfile(f.c_str());
	if(file.is_open() && codedfile.is_open()) {
		while(!file.eof()) {
			c=file.get();
			codedfile << repr[c];
		}
		file.close();
		codedfile.close();
	}
}

void HuffmanCode::lerFicheiroCodificacao(string file) {

}

void HuffmanCode::descomprimir() {

}
