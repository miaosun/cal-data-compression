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

#endif /* CODEC_H_ */
