/*
 * 	FICHEIRO: KeywordEncoding.cpp
 *	PROJECTO: Projecto2 CAL - Data Compression (T2)
 *  TURMA / GRUPO: Turma 2MIEIC2 / Grupo D
 *  AUTORES:
 *  - Jorge Miguel Reis
 *  - Miao Sun
 *  - Vitor Castro
 */

#include "Encoder.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

KeywordEncoding::KeywordEncoding(string filename)
{
	preProcessamento(filename);
	definirPadrao(filename);
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

void KeywordEncoding::definirPadrao(string filename)
{
	vector<string> caracterEspeciais;
	caracterEspeciais.push_back("%");
	caracterEspeciais.push_back("#");
	caracterEspeciais.push_back("$");
	caracterEspeciais.push_back("&");
	caracterEspeciais.push_back("|");
	caracterEspeciais.push_back("�");
	caracterEspeciais.push_back("\\");
	caracterEspeciais.push_back("�");
	caracterEspeciais.push_back("_");
	caracterEspeciais.push_back("^");
	caracterEspeciais.push_back("`");
	caracterEspeciais.push_back("�");
	caracterEspeciais.push_back("~");
	caracterEspeciais.push_back("�");
	string f_patrao = filename + ".key";
	ofstream patrao(f_patrao.c_str());

	size_t n_carEspecial = caracterEspeciais.size();
	int j=0;
	for(unsigned int i=0; i<n_carEspecial; i++)
	{
		while(palavras.size() > n_carEspecial && palavras[j].getPalavraOriginal().length() < 4)
			palavras.erase(palavras.begin()+j);

		palavras[i].setPalavraFinal(caracterEspeciais[i]);
		j++;
		patrao<<palavras[i].getPalavraOriginal()<<"|"<<palavras[i].getPalavraFinal()<<endl;
	}
	if(palavras.size() > n_carEspecial)
		palavras.resize(n_carEspecial);
}

void KeywordEncoding::comprimir(string filename)
{
	ifstream file;
	string line;
	file.open(filename.c_str());
	size_t pos;

	//nome do ficheiro de saida com extensao .hf
	string filename2 = filename;
	filename2.resize(filename.length()-3);
	filename2=filename2+"ke";

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
		cout<<"Padrao de codificacao desse ficheiro nao encontrado, tenta novamente!!"<<endl<<endl;
		return;
	}

	string filename2 = filename;
	filename2.resize(filename.length()-2);
	filename2= "[DCMP ke]"+filename2+"txt";

	ofstream decod(filename2.c_str());
	cout<< endl << "a descomprimir..." <<endl;

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
				if(file.eof())
					break;
				else
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

	cout<<"feita descompressao, ficheiro "<<filename2<<" foi criado"<<endl<<endl;
}

void KeywordEncoding::comecaComprimir(string filename)
{
	struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);

	cout << "A comprimir ficheiro..." << endl << endl;

	preProcessamento(filename);
	definirPadrao(filename);
	comprimir(filename);

	//cout<<"feita compressao, ficheiro "<<"[CMP]"+filename<<" foi criado"<<endl<<endl;
	cout << "Ficheiro Comprimido!" << endl << endl;

	gettimeofday(&tv2, NULL);

	printf("Tempo Total de Compressao:  = %f segundos\n",
			(double) (tv2.tv_usec - tv1.tv_usec) / 1000000
			+ (double) (tv2.tv_sec - tv1.tv_sec));
}
