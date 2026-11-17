#include<iostream>
#include<string>

using namespace std;

class Produs {
private:
	const int id;
	string denumire;
	float pret;
public:
	static const float PRET_MINIM;
	Produs() :id(0), denumire("Laptop"), pret(5000) {
	}

	Produs(int idP, string denumireP, float pretP) :id(idP), denumire(denumireP), pret(pretP) {
		if (pret < PRET_MINIM) {
			throw exception("Pret prea mic!");
		}
	}

	void afisare() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Pret: " << this->pret;
	}

	~Produs() {
	}
};

const float Produs::PRET_MINIM = 1;

void main() {
	try {
	Produs frigider(1, "Frigider", 0);
	}
	catch (exception e) {
		cout << endl << e.what();
	}

	Produs frigider(1, "Frigider", 5000);
	frigider.afisare();
}