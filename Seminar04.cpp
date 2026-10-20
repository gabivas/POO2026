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
};

int Cofetarie::nrCofetarii = 0;

void main() {
	Cofetarie cNedelya;
	cNedelya.afisareCofetarie();
	try {
		cNedelya.setNrLocuri(2);
	}
	catch (int cod) {
		cout << endl << cod;
	}
	catch (const char* mesaj) {
		cout << endl << mesaj;
	}
	catch (...) {
		cout << endl << "Nr locuri negativ!";
	}
	cout << endl << "Noul numar de locuri este: "
		<< cNedelya.getNrLocuri();

	cNedelya.setVectorConsumatie(new float[3] {28.5, 29.4, 32.6}, 3);
	float* vector = cNedelya.getVectorConsumatie();

	cout << endl << "Noile preturi sunt: ";
	for (int i = 0; i < 3; i++)
	{
		cout << vector[i] << " lei, ";
	}
	cNedelya.afisareCofetarie();

	delete[] vector;

	float* vectorConsumatie = new float[3] {35, 27, 41};
	Cofetarie* pMinimal = new Cofetarie(7, "Minimal", 3, vectorConsumatie);
	pMinimal->afisareCofetarie();
	delete pMinimal;

	cout << endl << "Am construit " << Cofetarie::nrCofetarii << " cofetarii!";

}