/*
 * LZW.cpp
 *
 *  Created on: 17 de Mai de 2013
 *      Author: ei09131
 */

#include "Encoder.h"

#include <iostream>
#include <stdlib.h>
#include <sys/time.h>


LZW::LZW(string filename) {
	for (int i = 0; i < 256; i++) {
		dicionarioCompressao[string(1, i)] = i;
	}
	tamanho = 256;
}

void LZW::lerDicionario(string filename) {

	ifstream file;
	file.open(filename.c_str());
	vector<unsigned int> aux;
	string temp1, temp2;
	vector<string> vetor;
	typedef pair<int, string> Int_Pair;

	while (!file.eof()) {
		getline(file, temp1);

		vetor.push_back(temp1);

	}
	file.close();

	for (unsigned int i = 0; i < vetor.size() - 1; i = i + 2) {
		dicionarioDescompressao.insert(
				std::pair<int, string>(atoi(vetor[i].c_str()), vetor[i + 1])); // max efficiency inserting

		cout << "sol----" << vetor[i] << endl;
	}

}

void LZW::guardarDicionario() {

	ofstream out1; // out1 é uma variavel.
	out1.open("dicionario.txt"); // o arquivo que será criado;

	for (map<string, int>::iterator it = dicionarioCompressao.begin();
			it != dicionarioCompressao.end(); it++) {
		cout << (*it).first.c_str() << "-----------" << (*it).second << endl;
		if ((*it).second != 26) {
			out1 << (*it).second << endl;
			out1 << (*it).first.c_str() << endl;
		}

	}

	out1.close();
}

void LZW::descomprimir(string filename) {

	struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);

	ifstream file;
	file.open(filename.c_str());

	vector<unsigned int> aux;
	string temp1;
	int a;
	string texto = "";

	while (getline(file, temp1)) {

		a = atoi(temp1.c_str());
		aux.push_back(a);
	}

	for (map<string, int>::iterator it = dicionarioCompressao.begin();
			it != dicionarioCompressao.end(); it++) {
		dicionarioDescompressao[(*it).second] = (*it).first;
	}

	for (vector<unsigned int>::iterator it = aux.begin(); it != aux.end(); it++)

	{
		int index = (*it);
		string corres = dicionarioDescompressao[index];
		texto += corres;
	}

	ofstream out1; // out é uma variavel.
	out1.open("descompressaoLZW.txt"); // o arquivo que será criado;

	for (unsigned int i = 0; i < texto.size(); i++)
		out1 << texto[i];

	out1.close();

	gettimeofday(&tv2, NULL);
	printf("Tempo Total de Compressão:  = %f segundos\n",
			(double) (tv2.tv_usec - tv1.tv_usec) / 1000000
			+ (double) (tv2.tv_sec - tv1.tv_sec));
}

void LZW::comprimir(string filename) {

	struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);

	vector<int> codigosAscii;
	int tamanhaDicionario = 256;
	fstream file;
	string ficheiro = "";
	string temp;

	file.open(filename.c_str());

	while (getline(file, temp)) {
		ficheiro += temp;
		ficheiro += '\n';
	}
	file.close();

	ficheiro += '\0';

	//entry contem o ficheiro todo
	string w;
	for (string::const_iterator it = ficheiro.begin(); it != ficheiro.end();
			++it) { //percorrer a string q contem o txt
		char c = *it; //caracter da string a analisar
		string wc = w + c; // combinacoes
		cout << "string wc= " << wc << endl;
		cout << "size dic: " << dicionarioCompressao.size() << endl;

		if (dicionarioCompressao.count(wc)) { //se existir no dicionario o wc...
			cout << "entrou no if: " << wc << "                "
					<< dicionarioCompressao.count(wc) << endl;
			w = wc;

			cout << "vai sair do if: " << w << endl;
		} else {
			cout << "teste3: " << w << endl;
			cout << "teste3: " << dicionarioCompressao[w] << endl;
			cout << "dictSize: " << tamanhaDicionario << endl;
			cout << "-------------------------------- INICIO" << endl;
			cout << "teste: " << dicionarioCompressao[w] << endl;
			cout << "teste: " << w << endl;
			codigosAscii.push_back(dicionarioCompressao[w]);
			cout << "--------------------------------FIM" << endl;
			dicionarioCompressao[wc] = tamanhaDicionario;
			tamanhaDicionario += 1;
			w = string(1, c);
		}
	}

	if (!w.empty())
		codigosAscii.push_back(dicionarioCompressao[w]);

	tamanho = tamanhaDicionario;

	ofstream out; // out é uma variavel.
	out.open("saidaLZW.txt"); // o arquivo que será criado;

	for (unsigned int i = 0; i < codigosAscii.size(); i++)
		out << codigosAscii[i] << endl;

	out.close();

	gettimeofday(&tv2, NULL);

	printf("Tempo Total de Compressão:  = %f segundos\n",
			(double) (tv2.tv_usec - tv1.tv_usec) / 1000000
			+ (double) (tv2.tv_sec - tv1.tv_sec));
}

/*
int main() {

	string filename = "ola.txt";
	string resposta;

	LZW a(filename);

	a.comprimir(filename);

	a.guardarDicionario();

	cout << "Quer descomprimir?" << endl;
	cin >> resposta;

	if (resposta == "sim") {
		a.lerDicionario("dicionario.txt");
		a.descomprimir("saidaLZW.txt");
	}

	return 0;
}
 */
