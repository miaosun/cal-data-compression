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

//Classe responsavel pela codificacao utilizando o algoritmo HuffmanCode
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

//Classe responsavel pela codificacao utilizando o algoritmo KeywordEncoding
class KeywordEncoding {
private:
	//Vetor que guarda as palavras lidas do ficheiro
	vector<Palavra> palavras;
public:
	KeywordEncoding(){};
	KeywordEncoding(string filename);
	//Metodo comprimir
	//Metodo que permite comprimir o ficheiro de texto escolhido pelo utilizador
	void comprimir(string filename);
	//Metodo Descomprimir
	//Metodo que permite descomprimir o ficheiro de texto 
	void descomprimir(string filename, string patrao);
	void insertionSort(vector<Palavra> &ps);
	void Split(vector<string> &lst, const string &input, const string &separators);
	void preProcessamento(string filename);
	void definirPadrao(string file);
	void comecaComprimir(string filename);
};

//Classe responsavel pela conversao usando o algoritmo LZW
class LZW
{
public:	
	int tamanho;
	//Hash Map utilizada para o processo de compressao
	map<string, int> dicionarioCompressao;
	//Hash Map utilizada para o processo de descompressao
	map<int, string> dicionarioDescompressao;
public:
	//Construtor
	//Aquando da criacao de um objeto do tipo LZW, preenche-se a Hashmap Compressao com todos os simbolos do alfabeto
	LZW() {

		for (int i = 0; i < 256; i++) {
			dicionarioCompressao[string(1, i)] = i;
		}
		tamanho = 256;
	}
	//Metodo comprimir
	//Este metodo utilizando o nome do ficheiro introduzido pelo utilizador, cria um ficheiro de saida ja comprimido
	void comprimir(string filename);
	//Metodo descomprimir
	//Este metodo utilizando o nome do ficheiro comprimido introduzido pelo utilizador, cria um ficheiro de saida descomprimido e identico ao inicial
	void descomprimir(string filename);
	//Metodo guardarDicionario
	//Este metodo guarda num ficheiro de texto o dicionario armazenado na Hash Map dicionarioCompressao
	void guardarDicionario();
	//Metodo lerDicionario
	//Este metodo carrega para a HashMap dicionarioDescompressao o conteudo do ficheiro de texto criado pelo metodo guardarFicheiro
	void lerDicionario(string filename);
	//Metodo setDicCompressao
	//Este metodo seta a HashMap dicionarioCompressao
	void setDicCompressao(map<string, int> d) {
		dicionarioCompressao = d;
	}
	//Metodo getDicCompressao
	//Este metodo retorna a HashMap dicionarioCompressao
	map<string, int> getDicCompressao() {
		return dicionarioCompressao;
	}
};

//Classe que permite lancar excepcoes
class Exception {
private:
	string message;
public:
	Exception( string mens ){message=mens;};
	string getMessage() { return message; };
};

#endif /* ENCODER_H_ */
