/*
 * Palavra.cpp
 *
 *  Created on: 21 de Mai de 2013
 *      Author: Miao
 */

#include "Palavra.h"

Palavra::Palavra(string palavraOriginal, int ocorrencia)
{
	this->palavraOriginal = palavraOriginal;
	this->ocorrencia = ocorrencia;
	this->palavraFinal = this->palavraOriginal;
}

Palavra::Palavra(string palavraOriginal, string palavraFinal)
{
	this->palavraOriginal = palavraOriginal;
	this->palavraFinal = palavraFinal;
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
	if(this->ocorrencia == p.getOcorrencia())
		return this->palavraOriginal.length() > p.getPalavraOriginal().length();
	else
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

