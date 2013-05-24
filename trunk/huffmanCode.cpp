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

#define MASK 0x80

using namespace std;

bool compareNodes(Node* n1, Node* n2) {
	return n1->getFreq() < n2->getFreq();
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
	vector<Node*> btree; //vector nós (arvore)
	for(unsigned int i=0; i<256; i++) {
		if (freqs[i]>0) {
			Node* n = new Node((unsigned char) i, freqs[i]);
			btree.push_back(n);
		}
	}
	sort(btree.begin(),btree.end(),compareNodes); //ordena por ordem crescente de frequencias

	while (btree.size() > 1) {
		Node* parent= new Node(); // novo nó
		parent->setLeft(btree[0]);
		parent->setRight(btree[1]);
		parent->setFreq(btree[0]->getFreq()+btree[1]->getFreq()); //soma frequencias das folhas
		btree.erase(btree.begin());
		btree.erase(btree.begin());
		btree.push_back(parent); //insere novo nó no vector
		sort(btree.begin(),btree.end(),compareNodes); //reordena vector
	}
	return btree[0];
}

void HuffmanCode::geraReprBinaria(Node* n, string s, vector<string> &v) {
	if(n->isLeaf()) {
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
	f=f+"hfc";
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
	int c;
	string temp;
	vector<unsigned char> codBinaria;
	vector<string> repr(256,"");

	calculaFreqs(); //calcula frequencias
	Node* root = buildTree(); //constroi árvore

	geraReprBinaria(root,"",repr); //gera vector com as representações
	geraFicheiroCodificacao(repr); //gera ficheiro com a codificacao utilizada

	//nome do ficheiro de saida com extensao .hf
	string codedFilename = filename;
	codedFilename.resize(filename.length()-3);
	codedFilename=codedFilename+"hf";

	//cria uma string de '0's e '1's com as representacoes dos caracteres do texto
	ifstream originalFile(filename.c_str());
	if(originalFile.is_open()) {
		while(!originalFile.eof()) {
			c=originalFile.get();
			if(c!=EOF) {
				temp+=repr[c];
			}
		}
		originalFile.close();

		//cria codificacao binaria para tdo o texto (vector com elementos de 8bits)
		for(unsigned int i=0; i<temp.size();i=i+8) {
			unsigned char byte=0;
			for(unsigned int j=0; j<8;j++) {
				byte=byte<<1;
				if(i+j < temp.size() && temp[i+j]=='1')
					byte=byte|1;
			}
			codBinaria.push_back(byte);
		}
	}

	cout << "A comprimir ficheiro..." << endl;

	//grava a informacao codificada (binaria) no ficheiro de saida
	ofstream codedfile(codedFilename.c_str(),ios_base::binary);
	for (unsigned int k=0;k<codBinaria.size();k++) {
		char out=codBinaria[k];
		codedfile.write(&out,1);
	}
	codedfile << (char) 0;

	cout << "Ficheiro Comprimido!" << endl;
}

void HuffmanCode::lerFicheiroCodificacao(string file) {

}

void HuffmanCode::descomprimir() {
	Node *root = buildTree(); //ALTERAR!!!
	string f="testDEC.txt";
	string cfilename="test.hf";
	ifstream codedfile(cfilename.c_str(),ios_base::binary);

	cout << "A descomprimir..." << endl;

	if(codedfile.is_open()) {
		ofstream decodedfile(f.c_str());
		if(decodedfile.is_open()) {
			Node* actualNode=root;
			char codchar=-1;
			char byte;
			while(codchar!='\0' && !codedfile.eof()) {
				codedfile.read(&byte,sizeof(char));
				for(unsigned int i=0; i<8; i++) {
					if((byte&MASK)==0x00) // caso 0, desce p filho esquerdo
						actualNode=actualNode->getLeft();
					else
						if((byte&MASK)==MASK) //caso 1, desce para filho direito
							actualNode=actualNode->getRight();

					if(actualNode->isLeaf()) { //se for uma folha, chegou-se a um caracter
						decodedfile << actualNode->getCaracter();
						actualNode=root;
					}
					byte=byte<<1;
				}
			}
			decodedfile.close();
		}
		else {
			cout << "Impossivel criar ficheiro de descodificacao!" << endl;
			return;
		}
		codedfile.close();
	}
	else {
		cout << "Impossivel abrir ficheiro codificado!" << endl;
		return;
	}
	cout << "Ficheiro descomprimido!" << endl;
}
