/*
 * LZW.cpp
 *
 *  Created on: 17 de Mai de 2013
 *      Author: ei09131
 */

#include "Encoder.h"

map<string, int> dicionarioLZW;

void LZW::lerDicionario(string filename) {

	ifstream file;
	file.open(filename.c_str(), ios_base::binary);
	vector<unsigned int> aux;
	string temp1, temp2;
	//vector<string> vetor;
	typedef pair<int, string> Int_Pair;

	while (!file.eof()) {
		getline(file, temp1);
		getline(file, temp2);
		cout<<"temp1 "<<temp1;
		cout<<"temp2"<<temp2;
		//vetor.push_back(temp1);
		dicionarioDescompressao.insert(std::pair<int, string>(atoi(temp1.c_str()),temp2));
	}

	file.close();

	//for(int i=0; i<vetor.size();i++)
	//	cout<<"cenaaas"<<vetor[i]<<endl;

	//	for (unsigned int i = 0; i < vetor.size() - 1; i = i + 2) {
	//		dicionarioDescompressao.insert(std::pair<int, string>(atoi(vetor[i].c_str()), vetor[i + 1])); // max efficiency inserting
	//	}

	map<int, string>::iterator pos;

	for (pos = dicionarioDescompressao.begin();	pos != dicionarioDescompressao.end(); ++pos)
	{
		cout << endl;
		cout << "Key dicionarioDescompressao: " << pos->first << endl;
		cout << "Value dicionarioDescompressao:" << pos->second << endl;
	}

	cout<<dicionarioCompressao.size();

}

void LZW::guardarDicionario() {

	ofstream out1; // out1 é uma variavel.
	out1.open("dicionario.txt"); // o arquivo que será criado;
	//ofstream out1("dicionario.txt");

	for (map<string, int>::iterator it = dicionarioCompressao.begin(); it != dicionarioCompressao.end(); it++) {
		cout << (*it).first.c_str() << "-----------" << (*it).second << endl;

		//if ((*it).second != 26) {
		if(((*it).second == 10 || (*it).second == 13)) {
			out1 << (*it).second << endl;
			out1 << (*it).first.c_str();
		}
		else {
			out1 << (*it).second << endl;
			out1 << (*it).first.c_str() << endl;
		}

		//}
	}
	out1.close();
}

void LZW::descomprimir(string filename) {

	dicionarioLZW = getDicCompressao();

	cout<<dicionarioDescompressao.size();

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

	ofstream out1; // out é uma variavel.
	out1.open("descompressaoLZW.txt"); // o arquivo que será criado;

	for (unsigned int i = 0; i < texto.size(); i++)
		out1 << texto[i];

	out1.close();

	gettimeofday(&tv2, NULL);

	printf("Tempo Total de Compressão:  = %f segundos\n",(double) (tv2.tv_usec - tv1.tv_usec) / 1000000	+ (double) (tv2.tv_sec - tv1.tv_sec));
}


void LZW::comprimir(string filename) {

	system("cls");
	cout << "A comprimir ficheiro..." << endl;

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
	string w;
	for (string::const_iterator it = ficheiro.begin(); it != ficheiro.end(); ++it) { //percorrer a string q contem o txt
		char c = *it; //caracter da string a analisar
		if(c!='\n') {
			string wc = w + c; // combinacoes

			if (dicionarioCompressao.count(wc)) { //se existir no dicionario o wc...
				w = wc;
			} else {
				codigosAscii.push_back(dicionarioCompressao[w]);
				dicionarioCompressao[wc] = tamanhaDicionario;
				tamanhaDicionario += 1;
				w = string(1, c);
			}
		}
		else {
			w="";
		}
	}

	if (!w.empty())
		codigosAscii.push_back(dicionarioCompressao[w]);

	tamanho = tamanhaDicionario;

	//dicionarioLZW = getDicCompress();

	string filenameOut = "saidaLZW.txt";
	ofstream out(filenameOut.c_str(), ios_base::binary);

	for (unsigned int i = 0; i < codigosAscii.size(); i++) {

		unsigned short int intAscii = codigosAscii[i];
		out.write((char *) &intAscii, sizeof(short int));
	}
	out << (char) 0;

	gettimeofday(&tv2, NULL);

	printf("Tempo Total de Compressão:  = %f segundos\n",
			(double) (tv2.tv_usec - tv1.tv_usec) / 1000000
			+ (double) (tv2.tv_sec - tv1.tv_sec));

	out.close();

}


/*
int main() {

	string filename = "ola.txt";
	string resposta;

	LZW a(filename);



	//a.comprimir(filename);

	//dicionarioLZW = a.getDicCompressao();

	//a.guardarDicionario();

	cout << "Quer descomprimir?" << endl;
	cin >> resposta;

	if (resposta == "sim") {
		LZW b(filename);
		a.lerDicionario("dicionario.txt");
		a.setDicCompressao(dicionarioLZW);
		a.descomprimir("saidaLZW.txt");
	}

	return 0;
}

 */
