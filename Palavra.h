/*
 * Palavra.h
 *
 *  Created on: 17 de Mai de 2013
 *      Author: Miao
 */

#ifndef PALAVRA_H_
#define PALAVRA_H_

#include <string>

using namespace std;

class Palavra
{
private:
	string palavraOriginal;
	string palavraFinal;
	int ocorrencia;

public:
	Palavra(){};
	Palavra(string palavraOriginal, int ocorrencia);
	Palavra(string palavraOriginal, string palavraFinal);
	string getPalavraOriginal();
	void setPalavraOriginal(string palavraOriginal);
	int getOcorrencia();
	void setOcorrencia(int ocorrencia);
	bool operator >(Palavra &p);
	string getPalavraFinal();
	void setPalavraFinal(string palavraFinal);
};

#endif /* PALAVRA_H_ */
