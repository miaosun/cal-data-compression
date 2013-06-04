/*
 * 	FICHEIRO: LZW.cpp
 *	PROJECTO: Projecto2 CAL - Data Compression (T2)
 *  TURMA / GRUPO: Turma 2MIEIC2 / Grupo D
 *  AUTORES:
 *  - Jorge Miguel Reis
 *  - Miao Sun
 *  - Vitor Castro
 */

#include "Encoder.h"


void LZW::lerDicionario(string filename) {

	ifstream file;
	file.open(filename.c_str(), ios_base::binary);
	vector<unsigned int> aux;
	string temp1, temp2;
	typedef pair<int, string> Int_Pair;

	while (!file.eof()) {
		getline(file, temp1);
		getline(file, temp2);
		dicionarioDescompressao.insert(std::pair<int, string>(atoi(temp1.c_str()),temp2));

	}
	file.close();
}

void LZW::guardarDicionario() {

	ofstream out1; // out1 e uma variavel.
	out1.open("dicionario.txt"); // o arquivo que sera criado;


	for (map<string, int>::iterator it = dicionarioCompressao.begin(); it != dicionarioCompressao.end(); it++) {
		//	cout << (*it).first.c_str() << "-----------" << (*it).second << endl;

		//if ((*it).second != 26) {
		//		if(((*it).second == 10 || (*it).second == 13)) {
		//			out1 << (*it).second << endl;
		//			out1 << (*it).first.c_str();
		//		}
		//		else {
		out1 << (*it).second << endl;
		out1 << (*it).first.c_str() << endl;
		//		}

		//}
	}
	out1.close();
}

void LZW::descomprimir(string filename) {


	struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);

	ifstream file;
	file.open(filename.c_str(), ios_base::binary);

	vector<unsigned int> aux;
	string temp1;
	string texto = "";

	unsigned short int tmp = 1;

	while (tmp != 0) {
		file.read((char*) &tmp, sizeof(short int));
		aux.push_back(tmp);
	}

	for (map<string, int>::iterator it = dicionarioCompressao.begin(); it != dicionarioCompressao.end(); it++) {
		dicionarioDescompressao[(*it).second] = (*it).first;
	}

	for (vector<unsigned int>::iterator it = aux.begin(); it != aux.end(); it++)
	{
		int index = (*it);
		string corres = dicionarioDescompressao[index];
		texto += corres;
	}

	ofstream out1; // out e uma variavel.

	string filename2 = filename;
	filename2.resize(filename.length()-3);
	filename2= "[DCMP lzw]"+filename2+"txt";

	out1.open(filename2.c_str()); // o arquivo que sera criado;

	for (unsigned int i = 0; i < texto.size(); i++)
		out1 << texto[i];

	out1.close();

	gettimeofday(&tv2, NULL);

	printf("Tempo Total de Compressao:  = %f segundos\n",(double) (tv2.tv_usec - tv1.tv_usec) / 1000000	+ (double) (tv2.tv_sec - tv1.tv_sec));
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

	//entry contem o ficheiro tdo
	string i;
	for (string::const_iterator it = ficheiro.begin(); it != ficheiro.end(); ++it) { //percorrer a string q contem o txt
		char c = *it; //caracter da string a analisar
		//		if(c!='\n') {
		string ic = i + c; // combinacoes

		if (dicionarioCompressao.count(ic)) { //se existir no dicionario o ic...
			i = ic;

		} else {
			codigosAscii.push_back(dicionarioCompressao[i]);
			dicionarioCompressao[ic] = tamanhaDicionario;
			tamanhaDicionario += 1;
			i = string(1, c);
		}
		//		}else {
		//			i="";
		//		}
	}

	if (!i.empty())
		codigosAscii.push_back(dicionarioCompressao[i]);

	tamanho = tamanhaDicionario;

	//nome do ficheiro de saida com extensao .lzw
	string filenameOut = filename;
	filenameOut.resize(filename.length()-3);
	filenameOut=filenameOut+"lzw";

	ofstream out(filenameOut.c_str(), ios_base::binary);

	for (unsigned int i = 0; i < codigosAscii.size(); i++) {

		unsigned short int intAscii = codigosAscii[i];
		out.write((char *) &intAscii, sizeof(short int));
	}
	out << (char) 0;

	gettimeofday(&tv2, NULL);


	printf("Tempo Total de Compressao:  = %f segundos\n",
			(double) (tv2.tv_usec - tv1.tv_usec) / 1000000
			+ (double) (tv2.tv_sec - tv1.tv_sec));

	out.close();

}
