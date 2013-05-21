/*
 * codec.h
 *
 *  Created on: 17 de Mai de 2013
 *      Author: Reis
 */

#ifndef CODEC_H_
#define CODEC_H_

#include <string>
#include <vector>
#include "BinaryTree.h"

using namespace std;

class Codec {
	string filename;
public:
	Codec(string file) {filename=file;}
	string getFilename() {return filename;}
};

class HuffmanCode: public Codec {
private:
	int freqs[256];
public:
	HuffmanCode(string file);
	void initFreqs();
	void calculaFreqs();
	void comprimir();
	Node* buildTree();
	void geraReprBinaria(Node* n, string s, vector<string> &v);
	void geraFicheiroCodificacao(vector<string> r);
	void lerFicheiroCodificacao(string file);
	void descomprimir();
};

#endif /* CODEC_H_ */
