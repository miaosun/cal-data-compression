/*
 * KeywordEncoding.cpp
 *
 *  Created on: 17 de Mai de 2013
 *      Author: Miao
 */

#include "codec.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

KeywordEncoding::KeywordEncoding(string filename)
{
	preProcessamento(filename);
	definirPatrao(filename);
}

void KeywordEncoding::insertionSort(vector<Palavra> &ps)
{
	for (unsigned int p = 1; p < ps.size(); p++)
	{
		Palavra tmp = ps[p];
		int j;
		for (j = p; j > 0 && tmp.getOcorrencia() > ps[j-1].getOcorrencia(); j--)
			ps[j] = ps[j-1];
		ps[j] = tmp;
	}
}

void KeywordEncoding::Split(vector<string>& lst, const string& input, const string& separators)
{
	ostringstream word;
	for (size_t n = 0; n < input.size(); ++n)
	{
		if (string::npos == separators.find(input[n]))
			word << input[n];
		else
		{
			if (!word.str().empty())
				lst.push_back(word.str());
			word.str("");
		}
	}
	if (!word.str().empty())
		lst.push_back(word.str());
}

void KeywordEncoding::preProcessamento(string filename)
{
	ifstream file;
	string line;
	file.open(filename.c_str());

	vector<string> vs;
	while(!file.eof())
	{
		getline(file, line);
		Split(vs, line, ", . : ; ? ! - _ | < >");

		for(unsigned int i=0; i<vs.size(); i++)
		{
			if(palavras.empty())
			{
				Palavra *p = new Palavra(vs[i], 1);
				palavras.push_back(*p);
				delete(p);
			}
			else
			{
				bool encontrou = false;
				for(unsigned int j=0; j<palavras.size(); j++)
				{
					if(palavras[j].getPalavraOriginal() == vs[i])
					{
						encontrou = true;
						palavras[j].setOcorrencia(palavras[j].getOcorrencia()+1);
						break;
					}
				}
				if(encontrou != true)
				{
					Palavra *p = new Palavra(vs[i], 1);
					palavras.push_back(*p);
					delete(p);
				}
			}
		}
		vs.clear();
	}
	file.close();
	insertionSort(palavras);
}

void KeywordEncoding::definirPatrao(string filename)
{
	vector<string> caracterEspeciais;
	caracterEspeciais.push_back("%");
	caracterEspeciais.push_back("#");
	caracterEspeciais.push_back("$");
	caracterEspeciais.push_back("&");
	caracterEspeciais.push_back("|");
	string f_patrao = filename + ".key";
	ofstream patrao(f_patrao.c_str());
	for(unsigned int i=0; i<caracterEspeciais.size(); i++)
	{
		palavras[i].setPalavraFinal(caracterEspeciais[i]);
		patrao<<palavras[i].getPalavraOriginal()<<"|"<<palavras[i].getPalavraFinal()<<endl;
	}
	palavras.resize(caracterEspeciais.size());
	patrao.close();
}

void KeywordEncoding::comprimir(string filename)
{
	ifstream file;
	string line;
	file.open(filename.c_str());
	size_t pos;
	string filename2 = "[CMP]" + filename;
	ofstream encod(filename2.c_str());

	if(file.is_open())
	{
		while(!file.eof())
		{
			getline(file, line);
			for(unsigned int i=0; i<palavras.size(); i++)
			{
				while((pos = line.find(palavras[i].getPalavraOriginal())) != line.npos)
				{
					size_t p_length = palavras[i].getPalavraOriginal().length();
					//if(pos>0 && line[pos-1]==' ' && line[pos+p_length]==' ')  //para evitar substituir substring da palavra
					line.replace(pos, p_length, palavras[i].getPalavraFinal());
					//else break;
				}
			}
			if(encod.is_open())
				encod<<line<<endl;
			else
			{
				cout<<"Nao conseguiu abrir ficheiro "<<filename2<<" !! Tenta novamente!"<<endl;
				return;
			}
		}
		file.close();
		encod.close();
	}
	else
	{
		cout<<"Nao conseguiu abrir ficheiro "<<filename<<" !! Tenta novamente!"<<endl;
		return;
	}
}

void KeywordEncoding::descomprimir(string filename, string patrao)
{
	ifstream file, f_key;
	file.open(filename.c_str());
	f_key.open(patrao.c_str());

	size_t pos;
	string line;
	vector<Palavra> keys;

	if(f_key.is_open())
	{
		while(!f_key.eof())
		{
			getline(f_key, line);
			if(line.size() == 0) break;
			size_t pos = line.find("|");
			Palavra *p = new Palavra(line.substr(0, pos), line.substr(pos+1));
			keys.push_back(*p);
			delete(p);
		}
		f_key.close();
	}
	else
	{
		cout<<"Patrao desse ficheiro nao encontrado, tenta novamente!!"<<endl;
		return;
	}

	string filename2 = "[DCMP]" + filename;
	ofstream decod(filename2.c_str());
	cout<<"\na descomprimir..."<<endl;

	if(file.is_open())
	{
		while(!file.eof())
		{
			getline(file, line);
			for(unsigned int i=0; i<keys.size(); i++)
			{
				while((pos = line.find(keys[i].getPalavraFinal())) != line.npos)
				{
					size_t p_length = keys[i].getPalavraFinal().length();
					line.replace(pos, p_length, keys[i].getPalavraOriginal());
				}
			}
			if(decod.is_open())
				decod<<line<<endl;
			else
			{
				cout<<"Nao conseguiu abrir ficheiro "<<filename2<<" !!  Tenta novamente!"<<endl;
				return;
			}

		}
		decod.close();
		file.close();
	}
	else
	{
		cout<<"Nao conseguiu abrir ficheiro "<<filename<<" !!  Tenta novamente!"<<endl;
		return;
	}

	cout<<"feita descompressao, ficheiro "<<filename2<<" foi creado"<<endl;
}

void KeywordEncoding::comecaComprimir(string filename)
{
	preProcessamento(filename);
	definirPatrao(filename);
	cout<<"\na comprimir..."<<endl;
	comprimir(filename);
	cout<<"feita compressao, ficheiro "<<"[CMP]"+filename<<" foi creado"<<endl;
}
/*
int main()
{
	vector<Palavra> palavras;
	string filename, filename2, patrao;
	cout<<"Insere o nome do ficheiro quer fazer compressao: "<<endl;
	getline(cin, filename);

	palavras = preProcesamento(filename);
	definirPatrao(filename,palavras);

	cout<<"comprimir..."<<endl;
	comprimir(filename, palavras);
	cout<<"Done comprimir, file Test.txt.cmp is created"<<endl;

	cout<<"Insere o nome do ficheiro quer fazer decompressao: "<<endl;
	getline(cin, filename2);
	cout<<"Insere o patrao desse ficheiro: "<<endl;
	getline(cin, patrao);
	descomprimir(filename2, patrao);
	cout<<"Done descomprimir, file Test.txt2 is created"<<endl;
	return 0;
}*/

