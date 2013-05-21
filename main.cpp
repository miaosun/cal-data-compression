/*
 * main.cpp
 *
 *  Created on: 17 de Mai de 2013
 *      Author: Reis
 */

#include "codec.h"
#include <iostream>

using namespace std;

int main() {
	HuffmanCode h("Test.txt");
	h.comprimir();
//	unsigned char a = 'b';
//	cout << (int)a << endl;
//	int n = h.getFilename().size();
//	int n2 = h.getFilename().length();
//	cout << n << "   " << n2 << endl;
	return 0;
}
