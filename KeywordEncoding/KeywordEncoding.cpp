/*
 * KeywordEncoding.cpp
 *
 *  Created on: 17 de Mai de 2013
 *      Author: Miao
 */

#include "Palavra.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

void insertionSort(vector<Palavra> &ps)
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

void Split(vector<string>& lst, const string& input, const string& separators, bool remove_empty = true)
{
	ostringstream word;
	for (size_t n = 0; n < input.size(); ++n)
	{
		if (string::npos == separators.find(input[n]))
			word << input[n];
		else
		{
			if (!word.str().empty() || !remove_empty)
				lst.push_back(word.str());
			word.str("");
		}
	}
	if (!word.str().empty() || !remove_empty)
		lst.push_back(word.str());
}

vector<Palavra> preProcesamento(string filename)
{
	vector<Palavra> palavras;
	ifstream file;
	string line;
	file.open(filename.c_str());

	vector<string> vs;
	while(!file.eof())
	{
		getline(file, line);
		Split(vs, line, ", . : ; ? ! - _ | < >", true);

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
	return palavras;
}

void definirPatrao(string filename, vector<Palavra> &palavras)
{
	vector<string> caracterEspeciais;
	caracterEspeciais.push_back("%");
	caracterEspeciais.push_back("#");
	caracterEspeciais.push_back("$");
	caracterEspeciais.push_back("&");
	caracterEspeciais.push_back("|");
	string f_patrao = filename + ".ptr";
	ofstream patrao(f_patrao.c_str());
	for(unsigned int i=0; i<caracterEspeciais.size(); i++)
	{
		palavras[i].setPalavraFinal(caracterEspeciais[i]);
		patrao<<palavras[i].getPalavraOriginal()<<"|"<<palavras[i].getPalavraFinal()<<endl;
	}
	palavras.resize(caracterEspeciais.size());
	patrao.close();
}

void encoding(string filename, vector<Palavra> &palavras)
{
	ifstream file;
	string line;
	file.open(filename.c_str());
	size_t pos;
	string filename2 = "[CMP] " + filename;
	ofstream encod(filename2.c_str());

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
	}
	file.close();
	encod.close();
}

void decoding(string filename, string patrao)
{
	ifstream file, f_ptr;
	file.open(filename.c_str());
	f_ptr.open(patrao.c_str());

	size_t pos;
	string line;
	vector<Palavra> ptrs;
	while(!f_ptr.eof())
	{
		getline(f_ptr, line);
		if(line.size() == 0) break;
		size_t pos = line.find("|");
		Palavra *p = new Palavra(line.substr(0, pos), line.substr(pos+1));
		ptrs.push_back(*p);
		delete(p);
	}

	string filename2 = "[DCMP] " + filename;
	ofstream decod(filename2.c_str());

	while(!file.eof())
	{
		getline(file, line);
		for(unsigned int i=0; i<ptrs.size(); i++)
		{
			while((pos = line.find(ptrs[i].getPalavraFinal())) != line.npos)
			{
				size_t p_length = ptrs[i].getPalavraFinal().length();
				line.replace(pos, p_length, ptrs[i].getPalavraOriginal());
			}
		}
		if(decod.is_open())
			decod<<line<<endl;
	}
	file.close();
	decod.close();
	f_ptr.close();
}

int main()
{
	vector<Palavra> palavras;
	string filename, filename2, patrao;
	cout<<"Insere o nome do ficheiro quer fazer compressao: "<<endl;
	getline(cin, filename);
	palavras = preProcesamento(filename);
	definirPatrao(filename,palavras);

	cout<<"Encoding..."<<endl;
	encoding(filename, palavras);
	cout<<"Done encoding, file Test.txt.cmp is created"<<endl;

	cout<<"Insere o nome do ficheiro quer fazer decompressao: "<<endl;
	getline(cin, filename2);
	cout<<"Insere o patrao desse ficheiro: "<<endl;
	getline(cin, patrao);
	decoding(filename2, patrao);
	cout<<"Done decoding, file Test.txt2 is created"<<endl;
	return 0;
}
