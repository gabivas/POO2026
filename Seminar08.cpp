#include<iostream>
#include<string>

using namespace std;

class ExceptieCustom : public exception {
public:
	ExceptieCustom(const char* mesaj) : exception(mesaj){}
};

class Produs {
protected:
	const int id;
	string denumire;
	float pret;
public:
	static const float PRET_MINIM;
	Produs() :id(0), denumire("Laptop"), pret(5000) {
	}

	Produs(int idP, string denumireP, float pretP) :id(idP), denumire(denumireP), pret(pretP) {
		if (pret < PRET_MINIM) {
			throw ExceptieCustom("Pret prea mic!");
		}
	}

	virtual void afisare() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Pret: " << this->pret;
	}

	~Produs() {
	}

	virtual float getProcentReducere() = 0;
};

const float Produs::PRET_MINIM = 1;

class ProdusRedus : public Produs {
private:
	float precentReducere;
public:
	ProdusRedus() :Produs(){
		this->precentReducere = 0;
	}

	ProdusRedus(int idP, string denumireP, float pretP, float procentReducereP) 
		:Produs(idP, denumireP, pretP) {
		this->precentReducere = procentReducereP;
	}

	void afisare() {
		this->Produs::afisare();
		cout << endl << "Procent reducere: " << this->precentReducere;
	}

	float getProcentReducere() {
		return this->precentReducere;
	}

};

class Operatie {
public:
	virtual int adunare(int a, int b) = 0;
	virtual int scadere(int a, int b) = 0;
	//virtual int inmultire(int a, int b) = 0;
	//virtual float impartire(int a, int b) = 0;  
};

class Calculator : public Operatie {
public:
	Calculator() {}

	int adunare(int a, int b) {
		return a + b;
	}

	int scadere(int a, int b) {
		return a - b;
	}
};

void main() {
	//try {
	//Produs frigider(1, "Frigider", 0);
	//}
	//catch (exception e) {
	//	cout << endl << e.what();
	//}

	//Produs frigider(1, "Frigider", 5000);
	//frigider.afisare();

	//ProdusRedus telefon(2, "Apple Iphone 18", 6500, 10);
	//telefon.afisare();

	Produs* vectorProduse[3];

	vectorProduse[0] = new ProdusRedus(1, "Paine", 4, 10);
	vectorProduse[1] = new ProdusRedus(2, "Zahar", 4, 10);
	vectorProduse[2] = new ProdusRedus(3, "Suc", 10, 10);

	for (int i = 0; i < 3; i++) {
		vectorProduse[i]->afisare();
		delete vectorProduse[i];
	}

	Produs* pProdus = new ProdusRedus();
	pProdus->afisare();
	delete pProdus;

	Operatie* calcul = new Calculator();
	cout << endl << "Adunare: " << calcul->adunare(4, 7);

	delete calcul;
}