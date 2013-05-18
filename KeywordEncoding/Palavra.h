/*
 * Palavra.h
 *
 *  Created on: 17 de Mai de 2013
 *      Author: Miao
 */

#ifndef PALAVRA_H_
#define PALAVRA_H_

#include <string>
#include <list>

using namespace std;

class Palavra
{
private:
	string palavraOriginal;
	string palavraFinal;
	int ocorrencia;
	list<string> posicoes;

public:
	Palavra(){};
	Palavra(string palavraOriginal, int ocorrencia);
	string getPalavraOriginal();
	void setPalavraOriginal(string palavraOriginal);
	int getOcorrencia();
	void setOcorrencia(int ocorrencia);
	bool operator >(Palavra &p);

	string getPalavraFinal();
	void setPalavraFinal(string palavraFinal);

	list<string> getPosicoes();
};

Palavra::Palavra(string palavraOriginal, int ocorrencia)
{
	this->palavraOriginal = palavraOriginal;
	this->ocorrencia = ocorrencia;
	this->palavraFinal = this->palavraOriginal;
}

string Palavra::getPalavraOriginal()
{
	return this->palavraOriginal;
}

void Palavra::setPalavraOriginal(string palavraOriginal)
{
	this->palavraOriginal = palavraOriginal;
}

int Palavra::getOcorrencia()
{
	return this->ocorrencia;
}

void Palavra::setOcorrencia(int ocorrencia)
{
	this->ocorrencia = ocorrencia;
}

bool Palavra::operator >(Palavra &p)
{
	return this->ocorrencia > p.getOcorrencia();
}

string Palavra::getPalavraFinal()
{
	return this->palavraFinal;
}

void Palavra::setPalavraFinal(string palavraFinal)
{
	this->palavraFinal = palavraFinal;
}

list<string> Palavra::getPosicoes()
{
	return this->posicoes;
}

#endif /* PALAVRA_H_ */
