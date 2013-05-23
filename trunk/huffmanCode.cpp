/*
 * huffmanCode.cpp
 *
 *  Created on: 17 de Mai de 2013
 *      Author: Reis
 */


#include <iostream>
#include <vector>
#include <fstream>
#include "Encoder.h"
#include "BinaryTree.h"

using namespace std;

bool compareNodes(Node* n1, Node* n2) {
	return n1->getFreq()<n2->getFreq();
}

HuffmanCode::HuffmanCode(string file) {
	filename=file;
	initFreqs();
}

void HuffmanCode::initFreqs() {
	for(unsigned int i=0; i<256; i++)
		freqs[i]=0;
}

void HuffmanCode::calculaFreqs() {
	int c;
	ifstream file(filename.c_str());
	if(file.is_open()) {
		while(!file.eof()) {
			if(c!=EOF) {
				c=file.get();
				freqs[c]++;
			}
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
		parent->setFreq(btree[0]->getFreq()+btree[1]->getFreq());
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
	string f = filename;
	f.resize(filename.length()-3);
	f=f+"huffc";
	ofstream codfile(f.c_str());
	if(codfile.is_open()) {
		for(unsigned int i=0; i<256; i++) {
			if(freqs[i]>0)
				codfile << (char) i << "|" << r[i] << endl;
		}
		codfile.close();
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
	string f = filename;
	f.resize(filename.length()-3);
	f=f+"huff";
	int c;
	ifstream file(filename.c_str());
	ofstream codedfile(f.c_str(),ios_base::binary);


	if(file.is_open() && codedfile.is_open()) {
		while(!file.eof()) {
			c=file.get();
			if(c!=EOF) {
				codedfile << repr[c];
				cout << repr[c] << endl;
			}
		}
		file.close();
		codedfile.close();
	}
}

void HuffmanCode::lerFicheiroCodificacao(string file) {

}

void HuffmanCode::descomprimir() {

}
