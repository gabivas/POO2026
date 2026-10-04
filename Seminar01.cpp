#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

using namespace std;

struct Casa {
	int nr;
	char* adresa;
	char* proprietar;
};

void afisareCasa(Casa c);

float calculMedieNumereIntregi(int vector[], int dim) {
	int suma = 0;
	for (int i = 0; i < dim; i++) {
		suma += vector[i];
	}

	if (dim > 0) {
		return suma / dim;
	}
}

void main() {
	cout << endl << "Hello grupa 1049!";
	Casa c;
	c.nr = 10;
	c.adresa = new char[strlen("Eminescu") + 1];
	strcpy(c.adresa, "Eminescu");
	c.proprietar = new char[strlen("PopescuIon") + 1];
	strcpy(c.proprietar, "PopescuIon");

	afisareCasa(c);
	int vector[] = { 10, 20, 30, 40, 50 };
	int dim = 5;

	cout << endl << "Media este: " <<
		calculMedieNumereIntregi(vector, dim);

	//dezalocari - altfel memory leaks
	delete[] c.adresa;
	delete[] c.proprietar;
}

void afisareCasa(Casa c) {
	cout << endl << "Casa aflata la adresa "<< c.adresa << 
		", numarul " << c.nr << " are proprietar pe " 
		<< c.proprietar <<"!";
}