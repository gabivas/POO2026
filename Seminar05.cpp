#include<iostream>
#include<string>

using namespace std;

enum Zona { CENTRALA = 1, PERIFERICA = 2};

class Cofetarie {
private:
	const int id;
	string denumire;
	Zona zona;
	int nrLocuri;
	float* vectorConsumatie;
public:
	static int nrCofetarii;
	Cofetarie() :id(++nrCofetarii) {
		//id = 0;
		//denumire = "Default";
		this->denumire = "Default";
		this->nrLocuri = 0;
		this->zona = PERIFERICA;
		this->vectorConsumatie = nullptr;
	}

	Cofetarie(int id, string denumire, Zona zona, int nrLocuri, float* vectorConsumatie)
		:id(id) {
		this->denumire = denumire;
		this->zona = zona;
		this->nrLocuri = nrLocuri;
		this->vectorConsumatie = new float[nrLocuri];
		for (int i = 0; i < this->nrLocuri; i++) {
			this->vectorConsumatie[i] = vectorConsumatie[i];
		}
		nrCofetarii++;
	}

	Cofetarie(const Cofetarie& c) :id(++nrCofetarii) {
		this->denumire = c.denumire;
		this->nrLocuri = c.nrLocuri;
		this->zona = c.zona;

		if (c.vectorConsumatie != nullptr) {
			this->vectorConsumatie = new float[c.nrLocuri];
			for (int i = 0; i < c.nrLocuri; i++) {
				this->vectorConsumatie[i] = c.vectorConsumatie[i];
			}
		}
		else {
			this->vectorConsumatie = nullptr;
		}
	}

	void operator=(const Cofetarie& c) {
		this->denumire = c.denumire;
		this->nrLocuri = c.nrLocuri;
		this->zona = c.zona;

		if (this->vectorConsumatie != nullptr) {
			delete[] this->vectorConsumatie;
			this->vectorConsumatie = nullptr;
		}

		if (c.vectorConsumatie != nullptr) {
			this->vectorConsumatie = new float[c.nrLocuri];
			for (int i = 0; i < c.nrLocuri; i++) {
				this->vectorConsumatie[i] = c.vectorConsumatie[i];
			}
		}
		else {
			this->vectorConsumatie = nullptr;
		}
	}

	void afisareCofetarie() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Nr locuri: " << this->nrLocuri;
		cout << endl << "Zona: ";
		if (this->zona == 1) {
			cout << "CENTRALA";
		}
		else {
			cout << "PERIFERICA";
		}

		if (this->nrLocuri > 0) {
			cout << endl << "Consumatie per locuri: ";
			for (int i = 0; i < this->nrLocuri - 1; i++) {
				cout << this->vectorConsumatie[i] << ", ";
			}
			cout << this->vectorConsumatie[this->nrLocuri - 1] << ".";
		}
	}

	//get si set pentru nrLocuri
	int getNrLocuri() {
		return this->nrLocuri;
	}

	void setNrLocuri(int nrLocuriNou) {
		if (nrLocuriNou >= 0) {
			this->nrLocuri = nrLocuriNou;
		}
		else {
			//throw exception();
			//throw 404;
			throw "Valoare negativa";
		}
	}

	//get si set pentru vectorConsumatie (pointer)
	float* getVectorConsumatie() {
		//return this->vectorConsumatie; --ASA NU
		float* vectorConsumatieNou = new float[this->nrLocuri];
		for (int i = 0; i < this->nrLocuri; i++)
		{
			vectorConsumatieNou[i] = this->vectorConsumatie[i];
		}
		return vectorConsumatieNou;
	}

	void setVectorConsumatie(float* vector, int nrL) {
		setNrLocuri(nrL);

		if (this->vectorConsumatie != nullptr) {
			delete[] this->vectorConsumatie;
		}

		this->vectorConsumatie = new float[this->nrLocuri];
		for (int i = 0; i < this->nrLocuri; i++)
		{
			this->vectorConsumatie[i] = vector[i];
		}

		delete[] vector;
	}

	~Cofetarie() {
		if (this->vectorConsumatie != nullptr) {
			delete[] this->vectorConsumatie;
		}
	}

	bool operator<(const Cofetarie& c) {
		return this->nrLocuri < c.nrLocuri;
	}
};

int Cofetarie::nrCofetarii = 0;

void main() {
	Cofetarie cNedelya;
	cNedelya.afisareCofetarie();

	float* vectorConsumatie = new float[3] {35, 27, 41};
	Cofetarie* pMinimal = new Cofetarie(7, "Minimal", CENTRALA, 3, vectorConsumatie);
	pMinimal->afisareCofetarie();

	Cofetarie cRomana = *pMinimal;
	cRomana.afisareCofetarie();

	cNedelya = *pMinimal;
	cNedelya.afisareCofetarie();

	cout << endl << "Am construit " << Cofetarie::nrCofetarii << " cofetarii!";

	if (cNedelya < cRomana) {
		cout << endl << "Cofetaria Nedelya are mai putine locuri!";
	}
	else {
		cout << endl << "Cofetaria Romana are mai putine locuri!";
	}

	delete pMinimal;
}