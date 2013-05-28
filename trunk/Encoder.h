/*
 * 	FICHEIRO: Encoder.h
 *	PROJECTO: Projecto2 CAL - Data Compression (T2)
 *  TURMA / GRUPO: Turma 2MIEIC2 / Grupo D
 *  AUTORES:
 *  - Jorge Miguel Reis
 *  - Miao Sun
 *  - Vitor Castro
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
#include <sys/time.h>

#include "TreeNode.h"
#include "Palavra.h"

using namespace std;


class HuffmanCode {
private:
	int freqs[256];
	string filename;
public:
	HuffmanCode();
	void initFreqs();
	void calculaFreqs();
	void comprimir(string file);
	Node* buildTree();
	void geraReprBinaria(Node* n, string s, vector<string> &v);
	void geraFicheiroCodificacao(vector<string> r);
	//guarda frequencias para ser posivel reconstruir a avore para descompressao
	void lerFicheiroCodificacao(string file);
	void descomprimir(string codedfilename);
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
	void definirPadrao(string file);
	void comecaComprimir(string filename);
};


class LZW
{
public:
	int tamanho;
	map<string, int> dicionarioCompressao;
	map<int, string> dicionarioDescompressao;
public:
	LZW() {

		for (int i = 0; i < 256; i++) {
			dicionarioCompressao[string(1, i)] = i;
		}
		tamanho = 256;
	}
	void comprimir(string filename);
	void descomprimir(string filename);
	void guardarDicionario();
	void lerDicionario(string filename);
	void setDicCompressao(map<string, int> d) {
		dicionarioCompressao = d;
	}
	map<string, int> getDicCompressao() {
		return dicionarioCompressao;
	}
};


class Exception {
private:
	string message;
public:
	Exception( string mens ){message=mens;};
	string getMessage() { return message; };
};

#endif /* ENCODER_H_ */
