/*
 * Encoder.h
 *
 *  Created on: 23 de Mai de 2013
 *      Author: Reis
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <map>
#include <iostream>
#include <stdlib.h>

#include "BinaryTree.h"
#include "Palavra.h"
using namespace std;


/*
class Codec {
	string filename;
public:
	Codec(string file) {filename=file;}
	string getFilename() {return filename;}
};
 */
class HuffmanCode {
private:
	int freqs[256];
	string filename;
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

class KeywordEncoding {
private:
	vector<Palavra> palavras;
public:
	KeywordEncoding(){};
	KeywordEncoding(string filename);
	void comprimir(string filename);
	void descomprimir(string filename, string patrao);
	void insertionSort(vector<Palavra> &ps);
	void Split(vector<string> &lst, const string &input, const string &separators);
	void preProcessamento(string filename);
	void definirPatrao(string file);
	void comecaComprimir(string filename);
};

class LZW {
protected:
	int tamanho;
	map<string, int> dicionarioCompressao;
	map<int, string> dicionarioDescompressao;
public:
	LZW(string filename) {

		for (int i = 0; i < 256; i++) {
			dicionarioCompressao[string(1, i)] = i;
		}
		tamanho = 256;
	}

	void comprimir(string filename);
	void descomprimir(string filename);
	void guardarDicionario();
	void lerDicionario(string filename);
	/*void setDicCompress(map<string, int> d) {
		dicionarioCompressao = d;
	}*/
	/*map<string, int> getDicCompress() {
		return dicionarioCompressao;
	}*/
};


#endif /* ENCODER_H_ */
