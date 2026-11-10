#include<iostream>
#include<string>

using namespace std;

enum Zona { CENTRALA = 1, PERIFERICA = 2 };

class Cofetarie {
private:
	const int id;
	float chirie;
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
		this->chirie = 0;
		this->zona = PERIFERICA;
		this->vectorConsumatie = nullptr;
	}

	Cofetarie(int id, float chirie, string denumire, Zona zona, int nrLocuri, float* vectorConsumatie)
		:id(id) {
		this->denumire = denumire;
		this->chirie = chirie;
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
		this->chirie = c.chirie;
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
		this->chirie = c.chirie;
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
		cout << endl << "Chirie: " << this->chirie << " euro";
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

	void operator+=(float chirieDeAdunat) {
		this->chirie += chirieDeAdunat;
	}

	//operatorul negatie
	bool operator!() {
		return this->chirie > 0;
	}

	//operatorul functie
	float operator()(float valoareDeAdaugat)
	{
		return this->chirie + valoareDeAdaugat;
	}

	//operatorul index
	float& operator[](int index) {
		if (index >= 0 && index < this->nrLocuri) {
			return this->vectorConsumatie[index];
		}
		else {
			throw exception();
		}
	}

	//operator << / operator de afisare
	friend void operator<<(ostream& out, Cofetarie cof) {
		out << endl << "Operator de afisare: ";
		out << endl << "Id: " << cof.id;
		out << endl << "Denumire: " << cof.denumire;
		out << endl << "Chirie: " << cof.chirie;
		out << endl << "Zona: ";
		if (cof.zona == CENTRALA) out << "CENTRALA";
		if (cof.zona == PERIFERICA) out << "PERIFERICA";
		out << endl << "Nr locuri: " << cof.nrLocuri;
		if (cof.vectorConsumatie != nullptr) {
			out << endl << "Vector consumatie: ";
			for (int i = 0; i < cof.nrLocuri - 1; i++) {
				out << cof.vectorConsumatie[i] << " grame, ";
			}
			out << cof.vectorConsumatie[cof.nrLocuri - 1] << " grame.";
		}
	}

	friend void operator>>(istream& in, Cofetarie& cof);

	//postincrementare
	Cofetarie operator++(int) {
		Cofetarie copie = *this;
		this->chirie++;

		return copie;
	}

	//preincrementare
	Cofetarie operator++() {
		this->chirie++;
		return *this;
	}

	//cast explicit
	explicit operator int() {
		return this->nrLocuri;
	}
};

int Cofetarie::nrCofetarii = 0;

void operator>>(istream& in, Cofetarie& cof) {
	cout << endl << "Chirie: ";
	in >> cof.chirie;

	cout << endl << "Denumire: ";
	in >> cof.denumire;

	cout << endl << "Zona: ";
	int zona;
	in >> zona;

	if (zona == 1) cof.zona = CENTRALA;
	if (zona == 2) cof.zona = PERIFERICA;

	cout << endl << "Nr locuri: ";
	in >> cof.nrLocuri;

	cout << endl << "Vector consumatie: ";

	if (cof.vectorConsumatie != nullptr) {
		delete[] cof.vectorConsumatie;
		cof.vectorConsumatie = nullptr;
	}

	cof.vectorConsumatie = new float[cof.nrLocuri];
	for (int i = 0; i < cof.nrLocuri; i++) {
		cout << endl << "vectorConsumatie[" << i << "]: ";
		in >> cof.vectorConsumatie[i];
	}
}

void main() {
	Cofetarie cNedelya;
	cNedelya.afisareCofetarie();

	float* vectorConsumatie = new float[3] {35, 27, 41};
	Cofetarie* pMinimal = new Cofetarie(7, 800, "Minimal", CENTRALA, 3, vectorConsumatie);
	pMinimal->afisareCofetarie();

	cout << endl << "Am construit " << Cofetarie::nrCofetarii << " cofetarii!";

	delete pMinimal;
}