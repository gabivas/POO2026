#include<iostream>
#include<string>

using namespace std;

class Cofetarie {
private:
	const int id;
	string denumire;
	int nrLocuri;
	float* vectorConsumatie;
public:
	static int nrCofetarii;
	Cofetarie() :id(++nrCofetarii) {
		//id = 0;
		//denumire = "Default";
		this->denumire = "Default";
		this->nrLocuri = 0;
		this->vectorConsumatie = nullptr;
	}

	Cofetarie(int id, string denumire, int nrLocuri, float* vectorConsumatie)
		:id(id) {
		this->denumire = denumire;
		this->nrLocuri = nrLocuri;
		this->vectorConsumatie = new float[nrLocuri];
		for (int i = 0; i < this->nrLocuri; i++) {
			this->vectorConsumatie[i] = vectorConsumatie[i];
		}
		nrCofetarii++;
	}

	void afisareCofetarie() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Nr locuri: " << this->nrLocuri;
		if (this->nrLocuri > 0) {
			cout << endl << "Consumatie per locuri: ";
			for (int i = 0; i < this->nrLocuri - 1; i++) {
				cout << this->vectorConsumatie[i] << ", ";
			}
			cout << this->vectorConsumatie[this->nrLocuri - 1] << ".";

		}
	}

	~Cofetarie() {
		if (this->vectorConsumatie != nullptr) {
			delete[] this->vectorConsumatie;
		}
	}

};

int Cofetarie::nrCofetarii = 0;

void main() {
	Cofetarie cNedelya;
	cNedelya.afisareCofetarie();

	float* vectorConsumatie = new float[3] {35, 27, 41};
	Cofetarie* pMinimal = new Cofetarie(7, "Minimal", 3, vectorConsumatie);
	pMinimal->afisareCofetarie();
	delete pMinimal;

	cout << endl << "Am construit " << Cofetarie::nrCofetarii << " cofetarii!";

}