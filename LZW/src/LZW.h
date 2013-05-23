/*
 * LZW.h
 *
 *  Created on: 17 de Mai de 2013
 *      Author: ei09131
 */

#ifndef LZW_H_
#define LZW_H_

#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <stdlib.h>

using namespace std;
typedef unsigned char byte;

class LZW

{

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

#endif /* LZW_H_ */
