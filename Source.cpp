#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

static float TVA = 0.19;

enum marimi { XS = 1, S = 2, M = 3, L = 4, XL = 5, XXL = 6, Necunoscuta = 7 };

map<string, marimi> m = {
	{"XS", XS},
	{"S", S},
	{"M", M},
	{"L", L},
	{"XL", XL},
	{"XXL", XXL},
	{"Necunoscuta", Necunoscuta}
};

//Exceptii
class EroareMesaj :public exception
{
public:
	string mesaj;
	EroareMesaj()
	{
		this->mesaj = "";
	}
	EroareMesaj(string mesaj)
	{
		this->mesaj = mesaj;
	}
};

//Clasa produse
class Produs
{
	const int idProdus; //pentru sortari
	char* denumire;
	float pret;
	marimi marime;
	string firma;
	int nrRecenzii;
	int* recenzii; //maxim 5 stele
public:
	static int contor;
	//Constructor fara parametrii
	Produs() :idProdus(contor++)
	{
		this->denumire = new char[strlen("Necunoscuta") + 1];
		strcpy(this->denumire, "Necunoscuta");
		this->pret = 0;
		this->marime = Necunoscuta;
		this->firma = "Necunoscuta";
		this->nrRecenzii = 0;
		this->recenzii = NULL;
	}
	//Constructor cu toti parametrii
	Produs(const char* denumire, float pret, marimi marime, string firma, int nrRecenzii, int* recenzii) :idProdus(contor++)
	{
		if (strlen(denumire) > 2)
		{
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
		}
		else
		{
			this->denumire = new char[strlen("Necunoscuta") + 1];
			strcpy(this->denumire, "Necunoscuta");
		}
		if (pret > 0)
		{
			this->pret = pret;
		}
		else
		{
			this->pret = 0;
		}
		this->marime = marime;
		if (firma.size() > 2)
		{
			this->firma = firma;
		}
		else
		{
			this->firma = "Necunoscuta";
		}
		if (nrRecenzii >= 1 && recenzii != NULL)
		{
			this->nrRecenzii = nrRecenzii;
			this->recenzii = new int[this->nrRecenzii];

			for (int i = 0; i < this->nrRecenzii; i++)
			{
				if (recenzii[i] > 0 && recenzii[i] <= 5)
				{
					this->recenzii[i] = recenzii[i];
				}
				else if (recenzii[i] <= 0)
				{
					this->recenzii[i] = 1;
				}
				else if (recenzii[i] > 5)
				{
					this->recenzii[i] = 5;
				}
			}
		}
		else
		{
			this->nrRecenzii = 0;
			this->recenzii = NULL;
		}
	}

	//Getteri
	int getID()
	{
		return this->idProdus;
	}
	const char* getDenumire()
	{
		return this->denumire;
	}
	float getPret()
	{
		return this->pret;
	}
	string getMarime()
	{

		switch (this->marime)
		{
		case 1:return "XS"; break;
		case 2: return "S"; break;
		case 3: return "M"; break;
		case 4: return "L"; break;
		case 5: return "XL"; break;
		case 6: return "XXL"; break;
		case 7: return "Necunoscut"; break;
		}
	}
	string getFirma()
	{
		return this->firma;
	}
	int getNrRecenzii()
	{
		return this->nrRecenzii;
	}
	int* getRecenzii()
	{
		return this->recenzii;
	}

	//Setteri
	void setDenumire(const char* denumire)
	{
		if (this->denumire != NULL)
		{
			delete[] this->denumire;
		}
		if (strlen(denumire) > 2)
		{
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
		}
	}
	void setPret(float pret)
	{
		if (pret > 0)
		{
			this->pret = pret;
		}
	}
	void setMarime(marimi marime)
	{
		this->marime = marime;
	}
	void setFirma(string firma)
	{
		if (firma.size() > 2)
		{
			this->firma = firma;
		}
	}
	void setRecenzii(int nrRecenzii, int* recenzii)
	{
		if (this->recenzii != NULL)
		{
			delete[] this->recenzii;
		}
		if (nrRecenzii >= 1 && recenzii != NULL)
		{
			this->nrRecenzii = nrRecenzii;
			this->recenzii = new int[this->nrRecenzii];

			for (int i = 0; i < this->nrRecenzii; i++)
			{
				if (recenzii[i] > 0 && recenzii[i] <= 5)
				{
					this->recenzii[i] = recenzii[i];
				}
				else if (recenzii[i] <= 0)
				{
					this->recenzii[i] = 1;
				}
				else if (recenzii[i] > 5)
				{
					this->recenzii[i] = 5;
				}
			}
		}
	}


	//Constructor de copiere
	Produs(const Produs& p) :idProdus(p.idProdus)
	{
		if (strlen(p.denumire) > 2)
		{
			this->denumire = new char[strlen(p.denumire) + 1];
			strcpy(this->denumire, p.denumire);
		}
		else
		{
			this->denumire = new char[strlen("Necunoscuta") + 1];
			strcpy(this->denumire, "Necunoscuta");
		}
		if (p.pret > 0)
		{
			this->pret = p.pret;
		}
		else
		{
			this->pret = 0;
		}
		this->marime = p.marime;
		if (p.firma.size() > 2)
		{
			this->firma = p.firma;
		}
		else
		{
			this->firma = "Necunoscuta";
		}
		if (p.nrRecenzii >= 1 && p.recenzii != NULL)
		{
			this->nrRecenzii = p.nrRecenzii;
			this->recenzii = new int[p.nrRecenzii];

			for (int i = 0; i < p.nrRecenzii; i++)
			{
				if (p.recenzii[i] > 0 && p.recenzii[i] <= 5)
				{
					this->recenzii[i] = p.recenzii[i];
				}
				else if (p.recenzii[i] <= 0)
				{
					this->recenzii[i] = 1;
				}
				else if (p.recenzii[i] > 5)
				{
					this->recenzii[i] = 5;
				}
			}
		}
		else
		{
			this->nrRecenzii = 0;
			this->recenzii = NULL;
		}
	}

	//Operatorul =
	Produs& operator=(const Produs& p)
	{
		if (this != &p)
		{
			if (this->denumire != NULL)
			{
				delete[] this->denumire;
			}
			if (this->recenzii != NULL)
			{
				delete[] this->recenzii;
			}
			if (strlen(p.denumire) > 2)
			{
				this->denumire = new char[strlen(p.denumire) + 1];
				strcpy(this->denumire, p.denumire);
			}
			else
			{
				this->denumire = new char[strlen("Necunoscuta") + 1];
				strcpy(this->denumire, "Necunoscuta");
			}
			if (p.pret > 0)
			{
				this->pret = p.pret;
			}
			else
			{
				this->pret = 0;
			}
			this->marime = p.marime;
			if (p.firma.size() > 2)
			{
				this->firma = p.firma;
			}
			else
			{
				this->firma = "Necunoscuta";
			}
			if (p.nrRecenzii >= 1 && p.recenzii != NULL)
			{
				this->nrRecenzii = p.nrRecenzii;
				this->recenzii = new int[p.nrRecenzii];

				for (int i = 0; i < p.nrRecenzii; i++)
				{
					if (p.recenzii[i] > 0 && p.recenzii[i] <= 5)
					{
						this->recenzii[i] = p.recenzii[i];
					}
					else if (p.recenzii[i] <= 0)
					{
						this->recenzii[i] = 1;
					}
					else if (p.recenzii[i] > 5)
					{
						this->recenzii[i] = 5;
					}
				}
			}
			else
			{
				this->nrRecenzii = 0;
				this->recenzii = NULL;
			}
		}
		return *this;
	}



	/////////////////////////Metode///////////////////////////

	//Metoda de calcul pret fara TVA
	float pretFaraTva()
	{
		return this->pret - TVA * this->pret;
	}

	//Metoda de calcul recenzie medie
	float recenzieMedie()
	{
		float suma = 0;
		for (int i = 0; i < this->nrRecenzii; i++)
		{
			suma = suma + this->recenzii[i];
		}
		return suma / this->nrRecenzii;
	}



	///////////////////Operatori////////////////////

	//Operatorul << de afisare
	friend ostream& operator<<(ostream& out, const Produs& p)
	{
		out << "Id produs:" << p.idProdus << " Denumire:" << p.denumire << " Pret:" << p.pret << " Marime:";
		switch (p.marime)
		{
		case 1:out << "XS"; break;
		case 2: out << "S"; break;
		case 3: out << "M"; break;
		case 4: out << "L"; break;
		case 5: out << "XL"; break;
		case 6: out << "XXL"; break;
		case 7: out << "Necunoscuta"; break;
		}
		out << " Firma:" << p.firma << " Nr recenzii:" << p.nrRecenzii << " Recenzii:";
		for (int i = 0; i < p.nrRecenzii; i++)
		{
			out << p.recenzii[i] << ";";
		}
		return out;
	}

	//Operatorul >> de citire de la tastatura
	friend istream& operator>>(istream& in, Produs& p)
	{
		if (p.denumire != NULL)
		{
			delete[] p.denumire;
		}
		if (p.recenzii != NULL)
		{
			delete[] p.recenzii;
		}
		cout << "Introduceti denumirea produsului:";
		char aux[50];
		in >> aux;
		p.denumire = new char[strlen(aux) + 1];
		strcpy(p.denumire, aux);
		cout << "Introduceti pretul produsului:";
		in >> p.pret;
		cout << "Introduceti marimea produsului:";
		string aux2;
		cin >> aux2;
		p.marime = m[aux2];
		cout << "Introduceti firma produsului:";
		in >> p.firma;
		cout << "Introduceti numarul de recenzii al produsului:";
		in >> p.nrRecenzii;
		cout << "Introduceti recenziile produsului:";
		p.recenzii = new int[p.nrRecenzii];
		for (int i = 0; i < p.nrRecenzii; i++)
		{
			in >> p.recenzii[i];
		}
		return in;

	}

	//Operatorul pentru indexare[]
	//Returneaza o recenzie 
	int operator[](int index)
	{
		if (index >= 0 && index < this->nrRecenzii)
		{
			return this->recenzii[index];
		}
		else
		{
			throw EroareMesaj("Eroare index recenzii!");
		}
	}

	//Operatorul +(obiect+val)
	//Mareste pretul produsului
	Produs operator+(float adaosPret)
	{
		Produs copie = *this;
		copie.pret = copie.pret + adaosPret;
		return copie;
	}
	//Operatorul +(val+obiect)
	//Mareste pretul produsului
	friend Produs operator+(float adaosPret, const Produs& p)
	{
		Produs copie = p;
		copie.pret = p.pret + adaosPret;
		return copie;
	}

	//Operatorul ++ preincrementare
	//Mareste toate recenziile cu 1
	Produs& operator++()
	{
		for (int i = 0; i < this->nrRecenzii; i++)
		{
			if (this->recenzii[i] + 1 <= 5)
			{
				this->recenzii[i]++;
			}
			else
			{
				throw EroareMesaj("Eroare actualizare recenzii!");
			}
		}
		return *this;
	}
	//Operatorul ++ postincrementare
	//Mareste toate recenziile cu 1
	Produs operator++(int)
	{
		Produs copie = *this;
		for (int i = 0; i < this->nrRecenzii; i++)
		{
			if (this->recenzii[i] + 1 <= 5)
			{
				this->recenzii[i]++;
			}
			else
			{
				throw EroareMesaj("Eroare actualizare recenzii!");
			}
		}
		return copie;
	}

	//Operatorul cast la int
	//Returneaza recenzia maxima
	explicit operator int()
	{
		int max = this->recenzii[0];
		for (int i = 1; i < this->nrRecenzii; i++)
		{
			if (this->recenzii[i] > max)
			{
				max = this->recenzii[i];
			}
		}
		return max;
	}

	//Operatorul +=(adaugare recenzie)
	//Adauga o noua recenzie
	Produs& operator+=(int recenzieNoua)
	{
		Produs copie = *this;
		if (this->recenzii != NULL)
		{
			delete[] this->recenzii;
		}
		this->nrRecenzii++;
		this->recenzii = new int[this->nrRecenzii];
		for (int i = 0; i < copie.nrRecenzii; i++)
		{
			this->recenzii[i] = copie.recenzii[i];
		}
		this->recenzii[copie.nrRecenzii] = recenzieNoua;
		return *this;
	}

	//Operatorul ==
	//Verifica daca doua produse au aceeasi recenzie medie
	bool operator==(Produs& p)
	{
		float medie1 = this->recenzieMedie();
		float medie2 = p.recenzieMedie();
		return medie1 == medie2;
	}

	//Operatorul > 
	//Pentru verificarea recenziilor medii 2 cate 2
	bool operator>(Produs& p)
	{
		return this->recenzieMedie() > p.recenzieMedie();
	}

	//Operatorul <
	bool operator<(Produs& p)
	{
		return this->pret < p.getPret();
	}

	//Operatorul <=
	bool operator<=(Produs& p)
	{
		return this->recenzieMedie() <= p.recenzieMedie();
	}

	///////////////////////FISIERE//////////////////

	//Fisere text
	//Scriere in fisier text
	friend ofstream& operator<<(ofstream& file, const Produs& p)
	{
		file << p.denumire << " ";
		file << p.pret << " ";
		switch (p.marime)
		{
		case 1:file << "XS"; break;
		case 2: file << "S"; break;
		case 3: file << "M"; break;
		case 4: file << "L"; break;
		case 5: file << "XL"; break;
		case 6: file << "XXL"; break;
		case 7: file << "Necunoscuta"; break;
		}
		file << " " << p.firma << " ";
		file << p.nrRecenzii << " ";

		for (int i = 0; i < p.nrRecenzii; i++)
		{
			file << p.recenzii[i] << " ";
		}
		file << endl;
		return file;
	}
	//Citire din fisier text
	friend ifstream& operator>>(ifstream& file, Produs& p)
	{
		if (p.denumire != NULL)
		{
			delete[] p.denumire;
		}
		if (p.recenzii != NULL)
		{
			delete[] p.recenzii;
		}
		char aux[50];
		file >> aux;
		p.denumire = new char[strlen(aux) + 1];
		strcpy(p.denumire, aux);
		file >> p.pret;
		string aux2;
		file >> aux2;
		p.marime = m[aux2];
		file >> p.firma;
		file >> p.nrRecenzii;
		p.recenzii = new int[p.nrRecenzii];
		for (int i = 0; i < p.nrRecenzii; i++)
		{
			file >> p.recenzii[i];
		}
		return file;
	}

	//Fisiere binare
	//Scriere in fisier binar
	void scriereBinarProduse(fstream& file)
	{
		//char*
		int lungime1 = strlen(this->denumire);
		file.write((char*)&lungime1, sizeof(int));
		for (int i = 0; i < lungime1; i++)
		{
			file.write((char*)&this->denumire[i], sizeof(char));
		}
		//float
		file.write((char*)&this->pret, sizeof(float));
		//marimi
		file.write((char*)&this->marime, sizeof(marimi));
		//string
		int lungime2 = this->firma.size();
		file.write((char*)&lungime2, sizeof(int));
		file.write(this->firma.c_str(), lungime2);
		//int
		file.write((char*)&this->nrRecenzii, sizeof(int));
		//int*
		for (int i = 0; i < this->nrRecenzii; i++)
		{
			file.write((char*)&this->recenzii[i], sizeof(int));
		}
	}
	//Citire din fisier binar
	void citireBinarProduse(fstream& file)
	{
		if (this->denumire != NULL)
		{
			delete[] this->denumire;
		}
		if (this->recenzii != NULL)
		{
			delete[] this->recenzii;
		}
		//char*
		int lungime1;
		file.read((char*)&lungime1, sizeof(int));
		this->denumire = new char[lungime1 + 1];
		for (int i = 0; i < lungime1; i++)
		{
			file.read((char*)&this->denumire[i], sizeof(char));
		}
		this->denumire[lungime1] = '\0';
		//float
		file.read((char*)&this->pret, sizeof(float));
		//marimi
		file.read((char*)&this->marime, sizeof(marimi));
		//string
		int lungime2;
		file.read((char*)&lungime2, sizeof(int));
		string aux;
		aux.resize(lungime2);
		file.read((char*)aux.c_str(), lungime2);
		this->firma = aux;
		//int
		file.read((char*)&this->nrRecenzii, sizeof(int));
		//int*
		this->recenzii = new int[this->nrRecenzii];
		for (int i = 0; i < this->nrRecenzii; i++)
		{
			file.read((char*)&this->recenzii[i], sizeof(int));
		}
	}

	//Destructor
	~Produs()
	{
		if (this->denumire != NULL)
		{
			delete[] this->denumire;
		}
		if (this->recenzii != NULL)
		{
			delete[] this->recenzii;
		}
	}
};

//Initializare atribute statice
int Produs::contor = 1;

//Strcutura pentru data comenzii
struct Data
{
	int zi;
	int luna;
	int an;
};

//Clasa comenzi
class Comanda
{
	const int idComanda;
	Data dataComanda;
	int nrProduse;
	Produs** vectorProduse;
	char* tipTransport;
	float valoareTransport;
public:
	static int contorComenzi;
	//Constructorul fara parametrii
	Comanda() :idComanda(contorComenzi++)
	{
		this->dataComanda.zi = 1;
		this->dataComanda.luna = 1;
		this->dataComanda.an = 2020;
		this->nrProduse = 0;
		this->vectorProduse = NULL;
		this->tipTransport = new char[strlen("Necunoscut") + 1];
		strcpy(this->tipTransport, "Necunoscut");
		this->valoareTransport = 0;
	}
	//Constructorul cu toti parametrii
	Comanda(Data dataComanda, int nrProduse, Produs** vectorProduse, const char* tipTransport, float valoareTransport) :idComanda(contorComenzi++)
	{
		if (dataComanda.zi > 0 && dataComanda.zi <= 31)
		{
			this->dataComanda.zi = dataComanda.zi;
		}
		else if (dataComanda.zi <= 0)
		{
			this->dataComanda.zi = 1;
		}
		else if (dataComanda.zi > 31)
		{
			this->dataComanda.zi = 31;
		}
		if (dataComanda.luna > 0 && dataComanda.luna <= 12)
		{
			this->dataComanda.luna = dataComanda.luna;
		}
		else if (dataComanda.luna <= 0)
		{
			this->dataComanda.luna = 1;
		}
		else if (dataComanda.luna > 12)
		{
			this->dataComanda.luna = 12;
		}
		if (dataComanda.an >= 2000 && dataComanda.an <= 2020)
		{
			this->dataComanda.an = dataComanda.an;
		}
		else if (dataComanda.an < 2000)
		{
			this->dataComanda.an = 2000;
		}
		else if (dataComanda.an > 2020)
		{
			this->dataComanda.an = 2020;
		}
		if (nrProduse > 0 && vectorProduse != NULL)
		{
			this->nrProduse = nrProduse;
			this->vectorProduse = new Produs * [this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->vectorProduse[i] = new Produs(*vectorProduse[i]);
			}
		}
		else
		{
			this->nrProduse = 0;
			this->vectorProduse = NULL;
		}
		if (strcmp(tipTransport, "Curier") == 0 || strcmp(tipTransport, "curier") == 0 || strcmp(tipTransport, "CURIER") == 0)
		{
			this->tipTransport = new char[strlen(tipTransport) + 1];
			strcpy(this->tipTransport, tipTransport);
			this->valoareTransport = valoareTransport;
		}
		else if (strcmp(tipTransport, "Posta") == 0 || strcmp(tipTransport, "posta") == 0 || strcmp(tipTransport, "POSTA") == 0)
		{
			this->tipTransport = new char[strlen(tipTransport) + 1];
			strcpy(this->tipTransport, tipTransport);
			this->valoareTransport = valoareTransport;
		}
		else
		{
			this->tipTransport = new char[strlen("Necunoscut") + 1];
			strcpy(this->tipTransport, "Necunoscut");
			this->valoareTransport = 0;
		}

	}

	//Getteri
	const int getIdComanda() {
		return this->idComanda;
	}
	Data getData() {
		return this->dataComanda;
	}
	int getNrProduse() {
		return this->nrProduse;
	}
	Produs** getProdus() {
		return this->vectorProduse;
	}
	char* getTipTransport() {
		return this->tipTransport;
	}
	float getValoareTransport() {
		return this->valoareTransport;
	}

	//Setteri
	void setData(Data data) {
		if (dataComanda.zi > 0 && dataComanda.zi <= 31)
		{
			this->dataComanda.zi = dataComanda.zi;
		}

		if (dataComanda.luna > 0 && dataComanda.luna <= 12)
		{
			this->dataComanda.luna = dataComanda.luna;
		}

		if (dataComanda.an >= 2000 && dataComanda.an <= 2020)
		{
			this->dataComanda.an = dataComanda.an;
		}
	}
	void setProduse(int nrProduse, Produs** vectorProduse)
	{
		for (int i = 0; i < this->nrProduse; i++)
		{
			delete this->vectorProduse[i];
		}
		delete[] this->vectorProduse;
		if (nrProduse > 0 && vectorProduse != NULL)
		{
			this->nrProduse = nrProduse;
			this->vectorProduse = new Produs * [this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->vectorProduse[i] = new Produs(*vectorProduse[i]);
			}
		}
	}
	void setTipTransport(const char* tipTransport, float valoareTransport) {
		if (this->tipTransport != NULL)
		{
			delete[] this->tipTransport;
		}
		if (strcmp(tipTransport, "Curier") == 0 || strcmp(tipTransport, "curier") == 0 || strcmp(tipTransport, "CURIER") == 0)
		{
			this->tipTransport = new char[strlen(tipTransport) + 1];
			strcpy(this->tipTransport, tipTransport);
			this->valoareTransport = valoareTransport;
		}
		else if (strcmp(tipTransport, "Posta") == 0 || strcmp(tipTransport, "posta") == 0 || strcmp(tipTransport, "POSTA") == 0)
		{
			this->tipTransport = new char[strlen(tipTransport) + 1];
			strcpy(this->tipTransport, tipTransport);
			this->valoareTransport = valoareTransport;
		}
	}

	//Constructorul de copiere
	Comanda(const Comanda& c) :idComanda(c.idComanda)
	{
		if (c.dataComanda.zi > 0 && c.dataComanda.zi <= 31)
		{
			this->dataComanda.zi = c.dataComanda.zi;
		}
		if (c.dataComanda.luna > 0 && c.dataComanda.luna <= 12)
		{
			this->dataComanda.luna = c.dataComanda.luna;
		}
		if (c.dataComanda.an >= 2000 && c.dataComanda.an <= 2020)
		{
			this->dataComanda.an = c.dataComanda.an;
		}
		if (c.nrProduse > 0 && c.vectorProduse != NULL)
		{
			this->nrProduse = c.nrProduse;
			this->vectorProduse = new Produs * [this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->vectorProduse[i] = new Produs(*c.vectorProduse[i]);
			}
		}
		else
		{
			this->nrProduse = 0;
			this->vectorProduse = NULL;
		}
		if (strcmp(c.tipTransport, "Curier") == 0 || strcmp(c.tipTransport, "curier") == 0 || strcmp(c.tipTransport, "CURIER") == 0)
		{
			this->tipTransport = new char[strlen(c.tipTransport) + 1];
			strcpy(this->tipTransport, c.tipTransport);
			this->valoareTransport = c.valoareTransport;
		}
		else if (strcmp(c.tipTransport, "Posta") == 0 || strcmp(c.tipTransport, "posta") == 0 || strcmp(c.tipTransport, "POSTA") == 0)
		{
			this->tipTransport = new char[strlen(c.tipTransport) + 1];
			strcpy(this->tipTransport, c.tipTransport);
			this->valoareTransport = c.valoareTransport;
		}
		else
		{
			this->tipTransport = new char[strlen("Necunoscut") + 1];
			strcpy(this->tipTransport, "Necunoscut");
			this->valoareTransport = 0;
		}
	}

	//Operatorul =
	Comanda& operator=(const Comanda& c)
	{
		if (this != &c)
		{
			for (int i = 0; i < this->nrProduse; i++)
			{
				delete this->vectorProduse[i];
			}
			delete[] this->vectorProduse;
			if (this->tipTransport != NULL)
			{
				delete[] this->tipTransport;
			}
			if (c.dataComanda.zi > 0 && c.dataComanda.zi <= 31)
			{
				this->dataComanda.zi = c.dataComanda.zi;
			}
			if (c.dataComanda.luna > 0 && c.dataComanda.luna <= 12)
			{
				this->dataComanda.luna = c.dataComanda.luna;
			}
			if (c.dataComanda.an >= 2000 && c.dataComanda.an <= 2020)
			{
				this->dataComanda.an = c.dataComanda.an;
			}
			if (c.nrProduse > 0 && c.vectorProduse != NULL)
			{
				this->nrProduse = c.nrProduse;
				this->vectorProduse = new Produs * [this->nrProduse];
				for (int i = 0; i < this->nrProduse; i++)
				{
					this->vectorProduse[i] = new Produs(*c.vectorProduse[i]);
				}
			}
			else
			{
				this->nrProduse = 0;
				this->vectorProduse = NULL;
			}
			if (strcmp(c.tipTransport, "Curier") == 0 || strcmp(c.tipTransport, "curier") == 0 || strcmp(c.tipTransport, "CURIER") == 0)
			{
				this->tipTransport = new char[strlen(c.tipTransport) + 1];
				strcpy(this->tipTransport, c.tipTransport);
				this->valoareTransport = c.valoareTransport;
			}
			else if (strcmp(c.tipTransport, "Posta") == 0 || strcmp(c.tipTransport, "posta") == 0 || strcmp(c.tipTransport, "POSTA") == 0)
			{
				this->tipTransport = new char[strlen(c.tipTransport) + 1];
				strcpy(this->tipTransport, c.tipTransport);
				this->valoareTransport = c.valoareTransport;
			}
			else
			{
				this->tipTransport = new char[strlen("Necunoscut") + 1];
				strcpy(this->tipTransport, "Necunoscut");
				this->valoareTransport = 0;
			}
		}
		return *this;
	}

	/////////////////////////Metode//////////////////////
	//Metoda de calcul a valoarii comenzii fara tva
	float comandaFaraTVA()
	{
		float totalPreturi = 0;
		for (int i = 0; i < this->nrProduse; i++)
		{
			totalPreturi = totalPreturi + vectorProduse[i]->getPret();
		}
		return totalPreturi - TVA * totalPreturi;
	}
	//Metoda de calcul a valorii comenzii fara transport
	float comandaTotalaFaraTransport()
	{
		float totalPreturi = 0;
		for (int i = 0; i < this->nrProduse; i++)
		{
			totalPreturi = totalPreturi + vectorProduse[i]->getPret();
		}
		return totalPreturi;
	}
	//Metoda de calcul a valorii comenzii cu TVA si transport
	float comandaTotala()
	{
		float totalPreturi = 0;
		for (int i = 0; i < this->nrProduse; i++)
		{
			totalPreturi = totalPreturi + vectorProduse[i]->getPret();
		}
		return totalPreturi + this->valoareTransport;
	}
	//Metoda de calcul a valorii comenzii cu discount de Black Friday
	float comandaCuDiscount(float discount)
	{
		float totalPreturi = 0;
		for (int i = 0; i < this->nrProduse; i++)
		{
			totalPreturi = totalPreturi + vectorProduse[i]->getPret();
		}
		if (this->dataComanda.zi >= 10 && this->dataComanda.zi <= 25 && this->dataComanda.luna == 11)
		{
			return totalPreturi - discount * totalPreturi;
		}
		else
		{
			return totalPreturi;
		}
	}

	////////////////////////Operatori///////////////

	//Operatorul << de afisare
	friend ostream& operator<<(ostream& out, const Comanda& c)
	{
		out << "Id comanda:" << c.idComanda << " Data comanda:" << c.dataComanda.zi << ":" << c.dataComanda.luna << ":" << c.dataComanda.an << " Tip transport:" << c.tipTransport << " Cost transport:" << c.valoareTransport << endl;
		out << "Numar produse:" << c.nrProduse << endl;
		out << "Produse:" << endl;
		for (int i = 0; i < c.nrProduse; i++)
		{
			out << *c.vectorProduse[i] << endl;
		}
		return out;
	}

	//Operatorul >> de citire de la tastatura
	friend istream& operator>>(istream& in, Comanda& c)
	{
		for (int i = 0; i < c.nrProduse; i++)
		{
			delete c.vectorProduse[i];
		}
		delete[] c.vectorProduse;
		if (c.tipTransport != NULL)
		{
			delete[] c.tipTransport;
		}
		cout << "Introduceti data comenzii:" << endl;
		cout << "Introduceti zi:";
		in >> c.dataComanda.zi;
		cout << "Introduceti luna:";
		in >> c.dataComanda.luna;
		cout << "Introduceti an:";
		in >> c.dataComanda.an;
		cout << "Introduceti tip transport(posta/curier):";
		char aux[50];
		in >> aux;
		c.tipTransport = new char[strlen(aux) + 1];
		strcpy(c.tipTransport, aux);
		cout << "Introduceti costul transportului:";
		in >> c.valoareTransport;
		cout << "Introduceti numarul de produse din comanda:";
		in >> c.nrProduse;
		cout << "Introduceti produsele din comanda:" << endl;;
		c.vectorProduse = new Produs * [c.nrProduse];
		for (int i = 0; i < c.nrProduse; i++)
		{
			c.vectorProduse[i] = new Produs();
			in >> *c.vectorProduse[i];
		}
		return in;
	}

	//Operatorul de indexare[]
	//Returneaza un produs
	Produs& operator[](int index)
	{
		if (index >= 0 && index < this->nrProduse)
		{
			return *this->vectorProduse[index];
		}
		else
		{
			throw EroareMesaj("Eroare index vector produse!");
		}
	}

	//Operatorul -(obiect-valoare)
	//Reducere pentru fiecare produs daca valoarea totala a comenzii este peste 150 de lei
	Comanda operator-(float reducere)
	{
		Comanda copie = *this;
		float total = copie.comandaTotala();
		if (total >= 150)
		{
			for (int i = 0; i < copie.nrProduse; i++)
			{
				float pret = copie.vectorProduse[i]->getPret();
				pret = pret - reducere * pret / 100.0;
				copie.vectorProduse[i]->setPret(pret);
			}
		}
		else
		{
			cout << "Comanda prea mica!";
		}
		return copie;
	}

	//Operatorul --(predecrementare)
	//Scade valoarea transportului cu 1
	Comanda& operator--()
	{
		if (this->valoareTransport - 1 >= 0)
		{
			this->valoareTransport--;
		}
		return *this;
	}

	//Operatorul --(postdecrementare)
	//Scade valoarea transportului cu 1
	Comanda operator--(int)
	{
		Comanda copie = *this;
		if (this->valoareTransport - 1 >= 0)
		{
			this->valoareTransport--;
		}
		return copie;
	}

	//Operatorul cast la Produs
	//Returneaza produsul cel mai scump din comanda 
	explicit operator Produs()
	{
		float max = this->vectorProduse[0]->getPret();
		int poz = 0;
		for (int i = 1; i < this->nrProduse; i++)
		{
			if (this->vectorProduse[i]->getPret() > max)
			{
				max = this->vectorProduse[i]->getPret();
				poz = i;
			}
		}
		return *this->vectorProduse[poz];
	}

	//Operatorul +=
	//Adauga un produs in comanda
	Comanda& operator+=(Produs& p)
	{
		Comanda copie = *this;
		for (int i = 0; i < this->nrProduse; i++)
		{
			delete this->vectorProduse[i];
		}
		delete[] this->vectorProduse;
		this->nrProduse++;
		this->vectorProduse = new Produs * [this->nrProduse];
		for (int i = 0; i < copie.nrProduse; i++)
		{
			this->vectorProduse[i] = new Produs(*copie.vectorProduse[i]);
		}
		this->vectorProduse[this->nrProduse - 1] = new Produs(p);
		return *this;
	}

	//Operatorul -=
	//Elimina produs din comanda
	Comanda& operator-=(int idCautare)
	{
		int nr = 0;
		Comanda copie = *this;
		for (int i = 0; i < this->nrProduse; i++)
		{
			if (this->vectorProduse[i]->getID() == idCautare)
			{
				nr++;
			}
		}
		delete[] this->vectorProduse;
		this->nrProduse = this->nrProduse - nr;
		this->vectorProduse = new Produs * [this->nrProduse];
		int poz = 0;
		for (int i = 0; i < copie.nrProduse; i++)
		{
			if (copie.vectorProduse[i]->getID() != idCautare)
			{
				this->vectorProduse[poz] = new Produs(*copie.vectorProduse[i]);
				poz++;
			}
		}
		return *this;
	}

	//////////////////////////////FISIERE//////////////////////

	//Fisiere text
	//Scriere in fisier text
	friend ofstream& operator<<(ofstream& file, const Comanda& c)
	{
		file << c.dataComanda.zi << " ";
		file << c.dataComanda.luna << " ";
		file << c.dataComanda.an << " ";
		file << c.nrProduse << endl;
		for (int i = 0; i < c.nrProduse; i++)
		{
			file << *c.vectorProduse[i];
		}
		file << c.tipTransport << " ";
		file << c.valoareTransport << " ";
		file << endl;
		return file;
	}
	//Citire din fisier text
	friend ifstream& operator>>(ifstream& file, Comanda& c)
	{
		for (int i = 0; i < c.nrProduse; i++)
		{
			delete c.vectorProduse[i];
		}
		delete[] c.vectorProduse;
		file >> c.dataComanda.zi;
		file >> c.dataComanda.luna;
		file >> c.dataComanda.an;
		file >> c.nrProduse;
		if (c.tipTransport != NULL)
		{
			delete[] c.tipTransport;
		}
		c.vectorProduse = new Produs * [c.nrProduse];
		for (int i = 0; i < c.nrProduse; i++)
		{
			Produs paux;
			file >> paux;
			c.vectorProduse[i] = new Produs(paux);
		}
		char aux[50];
		file >> aux;
		c.tipTransport = new char[strlen(aux) + 1];
		strcpy(c.tipTransport, aux);
		file >> c.valoareTransport;
		return file;
	}

	//Destructor
	~Comanda()
	{
		for (int i = 0; i < this->nrProduse; i++)
		{
			delete this->vectorProduse[i];
		}
		delete[] this->vectorProduse;
		if (this->tipTransport != NULL)
		{
			delete[] this->tipTransport;
		}
	}
};

int Comanda::contorComenzi = 1;

//Clasa categorie abstracta
class Categorie
{
public:
	//Functii virtuale
	//Calcul numar de produse dupa o anumita firma 
	virtual int nrProduseFirma(string firmaCautata)
	{
		return 0;
	}
	//Calcul numar de produse dupa media recenziilor intr-un anumit interval
	virtual int nrProduseMedieRecenzii(int limitaInf, int limitaSup)
	{
		return 0;
	}

	//Functii virtual pure
	//Calcul produse cu marimea S
	virtual int nrProduseMarimeaS() = 0;
};

//Clasa femei derivata din categorie
class Femei :public Categorie
{
	int nrProduseFemei;
	Produs** vectorProduseFemei;
public:
	//Constructor fara parametrii
	Femei()
	{
		this->nrProduseFemei = 0;
		this->vectorProduseFemei = NULL;
	}
	//Constructorul cu toti parametrii
	Femei(int nrProduseFemei, Produs** vectorProduseFemei)
	{
		if (nrProduseFemei > 0 && vectorProduseFemei != NULL)
		{
			this->nrProduseFemei = nrProduseFemei;
			this->vectorProduseFemei = new Produs * [this->nrProduseFemei];
			for (int i = 0; i < this->nrProduseFemei; i++)
			{
				this->vectorProduseFemei[i] = new Produs(*vectorProduseFemei[i]);
			}
		}
		else
		{
			this->nrProduseFemei = 0;
			this->vectorProduseFemei = NULL;
		}
	}

	//Getteri
	int getNrProduseFemei()
	{
		return this->nrProduseFemei;
	}
	Produs** getVectorProduseFemei()
	{
		return this->vectorProduseFemei;
	}

	//Setteri
	void setProduseFemei(int nrProduseFemei, Produs** vectorProduseFemei)
	{
		for (int i = 0; i < this->nrProduseFemei; i++)
		{
			delete this->vectorProduseFemei[i];
		}
		delete[] this->vectorProduseFemei;
		if (nrProduseFemei > 0 && vectorProduseFemei != NULL)
		{
			this->nrProduseFemei = nrProduseFemei;
			this->vectorProduseFemei = new Produs * [this->nrProduseFemei];
			for (int i = 0; i < this->nrProduseFemei; i++)
			{
				this->vectorProduseFemei[i] = new Produs(*vectorProduseFemei[i]);
			}
		}
	}

	//Constructorul de copiere
	Femei(const Femei& f)
	{
		if (f.nrProduseFemei > 0 && f.vectorProduseFemei != NULL)
		{
			this->nrProduseFemei = f.nrProduseFemei;
			this->vectorProduseFemei = new Produs * [this->nrProduseFemei];
			for (int i = 0; i < this->nrProduseFemei; i++)
			{
				this->vectorProduseFemei[i] = new Produs(*f.vectorProduseFemei[i]);
			}
		}
		else
		{
			this->nrProduseFemei = 0;
			this->vectorProduseFemei = NULL;
		}
	}

	//Operatorul =
	Femei& operator=(const Femei& f)
	{
		if (this != &f)
		{
			for (int i = 0; i < this->nrProduseFemei; i++)
			{
				delete this->vectorProduseFemei[i];
			}
			delete[] this->vectorProduseFemei;
			if (f.nrProduseFemei > 0 && f.vectorProduseFemei != NULL)
			{
				this->nrProduseFemei = f.nrProduseFemei;
				this->vectorProduseFemei = new Produs * [this->nrProduseFemei];
				for (int i = 0; i < this->nrProduseFemei; i++)
				{
					this->vectorProduseFemei[i] = new Produs(*f.vectorProduseFemei[i]);
				}
			}
			else
			{
				this->nrProduseFemei = 0;
				this->vectorProduseFemei = NULL;
			}
		}
		return *this;
	}


	//////////////////////////Metode///////////////////////

	//Functii virtuale
	//Calcul numar de produse dupa o anumita firma
	int nrProduseFirma(string firmaCautata)
	{
		int nr = 0;
		for (int i = 0; i < this->nrProduseFemei; i++)
		{
			if (vectorProduseFemei[i]->getFirma() == firmaCautata)
			{
				nr++;
			}
		}
		return nr;
	}

	//Calcul numar de produse dupa media recenziilor intr-un anumit interval
	int  nrProduseMedieRecenzii(int limitaInf, int limitaSup)
	{
		int nr = 0;
		for (int i = 0; i < this->nrProduseFemei; i++)
		{
			if (limitaInf <= vectorProduseFemei[i]->recenzieMedie() && vectorProduseFemei[i]->recenzieMedie() <= limitaSup);
			{
				nr++;
			}
		}
		return nr;
	}

	//Functii virtual pure
	int nrProduseMarimeaS()
	{
		int nr = 0;
		for (int i = 0; i < this->nrProduseFemei; i++)
		{
			if (vectorProduseFemei[i]->getMarime() == "S")
			{
				nr++;
			}
		}
		return nr;
	}

	/////////////////////////////////////Operatori/////////////////////////////////

	//Operatorul << de afisare
	friend ostream& operator<<(ostream& out, const Femei& f)
	{
		out << "Numar produse femei:" << f.nrProduseFemei << endl;
		out << "Produse femei:" << endl;
		for (int i = 0; i < f.nrProduseFemei; i++)
		{
			out << *f.vectorProduseFemei[i] << endl;
		}
		return out;
	}

	//Operatorul >> de citire de la tastatura
	friend istream& operator>>(istream& in, Femei& f)
	{
		for (int i = 0; i < f.nrProduseFemei; i++)
		{
			delete f.vectorProduseFemei[i];
		}
		delete[] f.vectorProduseFemei;
		cout << "Introduceti numarul de produse femei:";
		in >> f.nrProduseFemei;
		cout << "Introduceti produsele:" << endl;;
		f.vectorProduseFemei = new Produs * [f.nrProduseFemei];
		for (int i = 0; i < f.nrProduseFemei; i++)
		{
			f.vectorProduseFemei[i] = new Produs();
			in >> *f.vectorProduseFemei[i];
		}
		return in;
	}

	//Operatorul de indexare[] 
	//Returneaza un produs
	Produs& operator[](int index)
	{
		if (index >= 0 & index < this->nrProduseFemei)
		{
			return *this->vectorProduseFemei[index];
		}
		else
		{
			throw EroareMesaj("Eroare index vector produse femei!");
		}
	}

	//Operatorul +=
	//Adauga produs
	Femei& operator+=(Produs& p)
	{
		Femei copie = *this;
		for (int i = 0; i < this->nrProduseFemei; i++)
		{
			delete this->vectorProduseFemei[i];
		}
		delete[] this->vectorProduseFemei;
		this->nrProduseFemei++;
		this->vectorProduseFemei = new Produs * [this->nrProduseFemei];
		for (int i = 0; i < copie.nrProduseFemei; i++)
		{
			this->vectorProduseFemei[i] = new Produs(*copie.vectorProduseFemei[i]);
		}
		this->vectorProduseFemei[this->nrProduseFemei - 1] = new Produs(p);
		return *this;
	}

	//Operatorul -=
	//Elimina produs din comanda
	Femei& operator-=(int idCautare)
	{
		int nr = 0;
		Femei copie = *this;
		for (int i = 0; i < this->nrProduseFemei; i++)
		{
			if (this->vectorProduseFemei[i]->getID() == idCautare)
			{
				nr++;
			}
		}
		delete[] this->vectorProduseFemei;
		this->nrProduseFemei = this->nrProduseFemei - nr;
		this->vectorProduseFemei = new Produs * [this->nrProduseFemei];
		int poz = 0;
		for (int i = 0; i < copie.nrProduseFemei; i++)
		{
			if (copie.vectorProduseFemei[i]->getID() != idCautare)
			{
				this->vectorProduseFemei[poz] = new Produs(*copie.vectorProduseFemei[i]);
				poz++;
			}
		}
		return *this;
	}

	//////////////////////////////FISIERE//////////////////////

	//Fisiere text
	//Scriere in fisier text
	friend ofstream& operator<<(ofstream& file, const Femei& f)
	{
		file << f.nrProduseFemei << endl;
		for (int i = 0; i < f.nrProduseFemei; i++)
		{
			file << *f.vectorProduseFemei[i];
		}
		return file;
	}
	//Citire din fisier text
	friend ifstream& operator>>(ifstream& file, Femei& f)
	{
		for (int i = 0; i < f.nrProduseFemei; i++)
		{
			delete f.vectorProduseFemei[i];
		}
		delete[] f.vectorProduseFemei;
		file >> f.nrProduseFemei;
		f.vectorProduseFemei = new Produs * [f.nrProduseFemei];
		for (int i = 0; i < f.nrProduseFemei; i++)
		{
			Produs paux;
			file >> paux;
			f.vectorProduseFemei[i] = new Produs(paux);
		}
		return file;
	}

	//Destructor
	~Femei()
	{
		for (int i = 0; i < this->nrProduseFemei; i++)
		{
			delete this->vectorProduseFemei[i];
		}
		delete[] this->vectorProduseFemei;

	}
};

//Clasa barbati derivata din categorie
class Barbati :public Categorie
{
	int nrProduseBarbati;
	Produs** vectorProduseBarbati;
public:
	//Constructor fara parametrii
	Barbati()
	{
		this->nrProduseBarbati = 0;
		this->vectorProduseBarbati = NULL;
	}
	//Constructor cu toti parametrii
	Barbati(int nrProduseBarbati, Produs** vectorProduseBarbati)
	{
		if (nrProduseBarbati > 0 && vectorProduseBarbati != NULL)
		{
			this->nrProduseBarbati = nrProduseBarbati;
			this->vectorProduseBarbati = new Produs * [this->nrProduseBarbati];
			for (int i = 0; i < this->nrProduseBarbati; i++)
			{
				this->vectorProduseBarbati[i] = new Produs(*vectorProduseBarbati[i]);
			}
		}
		else
		{
			this->nrProduseBarbati = 0;
			this->vectorProduseBarbati = NULL;
		}
	}

	//Getteri
	int getNrProduseBarbati()
	{
		return this->nrProduseBarbati;
	}
	Produs** getVectorProduseBarbati()
	{
		return this->vectorProduseBarbati;
	}

	//Setteri
	void setProduseBarbati(int nrProduseBarbati, Produs** vectorProduseBarbati)
	{
		for (int i = 0; i < this->nrProduseBarbati; i++)
		{
			delete this->vectorProduseBarbati[i];
		}
		delete[] this->vectorProduseBarbati;
		if (nrProduseBarbati > 0 && vectorProduseBarbati != NULL)
		{
			this->nrProduseBarbati = nrProduseBarbati;
			this->vectorProduseBarbati = new Produs * [this->nrProduseBarbati];
			for (int i = 0; i < this->nrProduseBarbati; i++)
			{
				this->vectorProduseBarbati[i] = new Produs(*vectorProduseBarbati[i]);
			}
		}
	}

	//Constructorul de copiere
	Barbati(const Barbati& b)
	{
		if (b.nrProduseBarbati > 0 && b.vectorProduseBarbati != NULL)
		{
			this->nrProduseBarbati = b.nrProduseBarbati;
			this->vectorProduseBarbati = new Produs * [this->nrProduseBarbati];
			for (int i = 0; i < this->nrProduseBarbati; i++)
			{
				this->vectorProduseBarbati[i] = new Produs(*b.vectorProduseBarbati[i]);
			}
		}
		else
		{
			this->nrProduseBarbati = 0;
			this->vectorProduseBarbati = NULL;
		}
	}

	//Operatorul =
	Barbati& operator=(const Barbati& b)
	{
		if (this != &b)
		{
			for (int i = 0; i < this->nrProduseBarbati; i++)
			{
				delete this->vectorProduseBarbati[i];
			}
			delete[] this->vectorProduseBarbati;
			if (b.nrProduseBarbati > 0 && b.vectorProduseBarbati != NULL)
			{
				this->nrProduseBarbati = b.nrProduseBarbati;
				this->vectorProduseBarbati = new Produs * [this->nrProduseBarbati];
				for (int i = 0; i < this->nrProduseBarbati; i++)
				{
					this->vectorProduseBarbati[i] = new Produs(*b.vectorProduseBarbati[i]);
				}
			}
			else
			{
				this->nrProduseBarbati = 0;
				this->vectorProduseBarbati = NULL;
			}
		}
		return *this;
	}




	//////////////////////////Metode///////////////////////

	//Functii virtuale
	//Calcul numar de produse dupa o anumita firma 
	int nrProduseFirma(string firmaCautata)
	{
		int nr = 0;
		for (int i = 0; i < this->nrProduseBarbati; i++)
		{
			if (vectorProduseBarbati[i]->getFirma() == firmaCautata)
			{
				nr++;
			}
		}
		return nr;
	}

	//Calcul numar de produse dupa media recenziilor intr-un anumit interval
	int  nrProduseMedieRecenzii(int limitaInf, int limitaSup)
	{
		int nr = 0;
		for (int i = 0; i < this->nrProduseBarbati; i++)
		{
			if (limitaInf <= vectorProduseBarbati[i]->recenzieMedie() && vectorProduseBarbati[i]->recenzieMedie() <= limitaSup);
			{
				nr++;
			}
		}
		return nr;
	}

	//Functii virtual pure
	int nrProduseMarimeaS()
	{
		int nr = 0;
		for (int i = 0; i < this->nrProduseBarbati; i++)
		{
			if (vectorProduseBarbati[i]->getMarime() == "S")
			{
				nr++;
			}
		}
		return nr;
	}

	/////////////////////////////////////Operatori/////////////////////////////////

	//Operatorul << de afisare
	friend ostream& operator<<(ostream& out, const Barbati& b)
	{
		out << "Numar produse barbati:" << b.nrProduseBarbati << endl;
		out << "Produse barbati:" << endl;
		for (int i = 0; i < b.nrProduseBarbati; i++)
		{
			out << *b.vectorProduseBarbati[i] << endl;
		}
		return out;
	}

	//Operatorul >> de citire de la tastatura
	friend istream& operator>>(istream& in, Barbati& b)
	{
		for (int i = 0; i < b.nrProduseBarbati; i++)
		{
			delete b.vectorProduseBarbati[i];
		}
		delete[] b.vectorProduseBarbati;
		cout << "Introduceti numarul de produse barbati:";
		in >> b.nrProduseBarbati;
		cout << "Introduceti produsele:" << endl;;
		b.vectorProduseBarbati = new Produs * [b.nrProduseBarbati];
		for (int i = 0; i < b.nrProduseBarbati; i++)
		{
			b.vectorProduseBarbati[i] = new Produs();
			in >> *b.vectorProduseBarbati[i];
		}
		return in;
	}

	//Operatorul de indexare[] 
	//Returneaza un produs
	Produs& operator[](int index)
	{
		if (index >= 0 & index < this->nrProduseBarbati)
		{
			return *this->vectorProduseBarbati[index];
		}
		else
		{
			throw EroareMesaj("Eroare index vector produse Barbati!");
		}
	}

	//Operatorul +=
	//Adauga produs
	Barbati& operator+=(Produs& p)
	{
		Barbati copie = *this;
		for (int i = 0; i < this->nrProduseBarbati; i++)
		{
			delete this->vectorProduseBarbati[i];
		}
		delete[] this->vectorProduseBarbati;
		this->nrProduseBarbati++;
		this->vectorProduseBarbati = new Produs * [this->nrProduseBarbati];
		for (int i = 0; i < copie.nrProduseBarbati; i++)
		{
			this->vectorProduseBarbati[i] = new Produs(*copie.vectorProduseBarbati[i]);
		}
		this->vectorProduseBarbati[this->nrProduseBarbati - 1] = new Produs(p);
		return *this;
	}

	//Operatorul -=
	//Elimina produs din comanda
	Barbati& operator-=(int idCautare)
	{
		int nr = 0;
		Barbati copie = *this;
		for (int i = 0; i < this->nrProduseBarbati; i++)
		{
			if (this->vectorProduseBarbati[i]->getID() == idCautare)
			{
				nr++;
			}
		}
		delete[] this->vectorProduseBarbati;
		this->nrProduseBarbati = this->nrProduseBarbati - nr;
		this->vectorProduseBarbati = new Produs * [this->nrProduseBarbati];
		int poz = 0;
		for (int i = 0; i < copie.nrProduseBarbati; i++)
		{
			if (copie.vectorProduseBarbati[i]->getID() != idCautare)
			{
				this->vectorProduseBarbati[poz] = new Produs(*copie.vectorProduseBarbati[i]);
				poz++;
			}
		}
		return *this;
	}

	///////////////////////////FISIERE////////////////////

	//Fisiere text
	//Scriere in fisier text
	friend ofstream& operator<<(ofstream& file, const Barbati& f)
	{
		file << f.nrProduseBarbati << endl;
		for (int i = 0; i < f.nrProduseBarbati; i++)
		{
			file << *f.vectorProduseBarbati[i];
		}
		return file;
	}
	//Citire din fisier text
	friend ifstream& operator>>(ifstream& file, Barbati& f)
	{
		for (int i = 0; i < f.nrProduseBarbati; i++)
		{
			delete f.vectorProduseBarbati[i];
		}
		delete[] f.vectorProduseBarbati;
		file >> f.nrProduseBarbati;
		f.vectorProduseBarbati = new Produs * [f.nrProduseBarbati];
		for (int i = 0; i < f.nrProduseBarbati; i++)
		{
			Produs paux;
			file >> paux;
			f.vectorProduseBarbati[i] = new Produs(paux);
		}
		return file;
	}

	//Destructor
	~Barbati()
	{
		for (int i = 0; i < this->nrProduseBarbati; i++)
		{
			delete this->vectorProduseBarbati[i];
		}
		delete[] this->vectorProduseBarbati;

	}
};

//Clasa accesorii derivata din categorie
class Home :public Categorie
{
	int nrProduseHome;
	Produs** vectorProduseHome;
public:
	//Constructor fara parametrii
	Home()
	{
		this->nrProduseHome = 0;
		this->vectorProduseHome = NULL;
	}
	//Constructor cu toti parametrii
	Home(int nrProduseHome, Produs** vectorProduseHome)
	{
		if (nrProduseHome > 0 && vectorProduseHome != NULL)
		{
			this->nrProduseHome = nrProduseHome;
			this->vectorProduseHome = new Produs * [this->nrProduseHome];
			for (int i = 0; i < this->nrProduseHome; i++)
			{
				this->vectorProduseHome[i] = new Produs(*vectorProduseHome[i]);
			}
		}
		else
		{
			this->nrProduseHome = 0;
			this->vectorProduseHome = NULL;
		}
	}

	//Getteri
	int getNrProduseHome()
	{
		return this->nrProduseHome;
	}
	Produs** getVectorProduseHome()
	{
		return this->vectorProduseHome;
	}

	//Setteri
	void setProduseHome(int nrProduseHome, Produs** vectorProduseHome)
	{
		for (int i = 0; i < this->nrProduseHome; i++)
		{
			delete this->vectorProduseHome[i];
		}
		delete[] this->vectorProduseHome;
		if (nrProduseHome > 0 && vectorProduseHome != NULL)
		{
			this->nrProduseHome = nrProduseHome;
			this->vectorProduseHome = new Produs * [this->nrProduseHome];
			for (int i = 0; i < this->nrProduseHome; i++)
			{
				this->vectorProduseHome[i] = new Produs(*vectorProduseHome[i]);
			}
		}
	}

	//Constructorul de copiere
	Home(const Home& h)
	{
		if (h.nrProduseHome > 0 && h.vectorProduseHome != NULL)
		{
			this->nrProduseHome = h.nrProduseHome;
			this->vectorProduseHome = new Produs * [this->nrProduseHome];
			for (int i = 0; i < this->nrProduseHome; i++)
			{
				this->vectorProduseHome[i] = new Produs(*h.vectorProduseHome[i]);
			}
		}
		else
		{
			this->nrProduseHome = 0;
			this->vectorProduseHome = NULL;
		}
	}

	//Operatorul =
	Home& operator=(const Home& h)
	{
		if (this != &h)
		{
			for (int i = 0; i < this->nrProduseHome; i++)
			{
				delete this->vectorProduseHome[i];
			}
			delete[] this->vectorProduseHome;
			if (h.nrProduseHome > 0 && h.vectorProduseHome != NULL)
			{
				this->nrProduseHome = h.nrProduseHome;
				this->vectorProduseHome = new Produs * [this->nrProduseHome];
				for (int i = 0; i < this->nrProduseHome; i++)
				{
					this->vectorProduseHome[i] = new Produs(*h.vectorProduseHome[i]);
				}
			}
			else
			{
				this->nrProduseHome = 0;
				this->vectorProduseHome = NULL;
			}
		}
		return *this;
	}




	//////////////////////////Metode///////////////////////

	//Functii virtuale
	//Calcul numar de produse dupa o anumita firma
	int nrProduseFirma(string firmaCautata)
	{
		int nr = 0;
		for (int i = 0; i < this->nrProduseHome; i++)
		{
			if (vectorProduseHome[i]->getFirma() == firmaCautata)
			{
				nr++;
			}
		}
		return nr;
	}

	//Calcul numar de produse dupa media recenziilor intr-un anumit interval
	int  nrProduseMedieRecenzii(int limitaInf, int limitaSup)
	{
		int nr = 0;
		for (int i = 0; i < this->nrProduseHome; i++)
		{
			if (limitaInf <= vectorProduseHome[i]->recenzieMedie() && vectorProduseHome[i]->recenzieMedie() <= limitaSup);
			{
				nr++;
			}
		}
		return nr;
	}

	//Functii virtual pure
	int nrProduseMarimeaS()
	{
		return 0;
	}


	/////////////////////////////////////Operatori/////////////////////////////////

	//Operatorul << de afisare
	friend ostream& operator<<(ostream& out, const Home& h)
	{
		out << "Numar produse home:" << h.nrProduseHome << endl;
		out << "Produse home:" << endl;
		for (int i = 0; i < h.nrProduseHome; i++)
		{
			out << *h.vectorProduseHome[i] << endl;
		}
		return out;
	}

	//Operatorul >> de citire de la tastatura
	friend istream& operator>>(istream& in, Home& h)
	{
		for (int i = 0; i < h.nrProduseHome; i++)
		{
			delete h.vectorProduseHome[i];
		}
		delete[] h.vectorProduseHome;
		cout << "Introduceti numarul de produse home:";
		in >> h.nrProduseHome;
		cout << "Introduceti produsele:" << endl;;
		h.vectorProduseHome = new Produs * [h.nrProduseHome];
		for (int i = 0; i < h.nrProduseHome; i++)
		{
			h.vectorProduseHome[i] = new Produs();
			in >> *h.vectorProduseHome[i];
		}
		return in;
	}

	//Operatorul de indexare[] 
	//Returneaza un produs
	Produs& operator[](int index)
	{
		if (index >= 0 & index < this->nrProduseHome)
		{
			return *this->vectorProduseHome[index];
		}
		else
		{
			throw EroareMesaj("Eroare index vector produse Home!");
		}
	}

	//Operatorul +=
	//Adauga produs
	Home& operator+=(Produs& p)
	{
		Home copie = *this;
		for (int i = 0; i < this->nrProduseHome; i++)
		{
			delete this->vectorProduseHome[i];
		}
		delete[] this->vectorProduseHome;
		this->nrProduseHome++;
		this->vectorProduseHome = new Produs * [this->nrProduseHome];
		for (int i = 0; i < copie.nrProduseHome; i++)
		{
			this->vectorProduseHome[i] = new Produs(*copie.vectorProduseHome[i]);
		}
		this->vectorProduseHome[this->nrProduseHome - 1] = new Produs(p);
		return *this;
	}

	//Operatorul -=
	//Elimina produs din comanda
	Home& operator-=(int idCautare)
	{
		int nr = 0;
		Home copie = *this;
		for (int i = 0; i < this->nrProduseHome; i++)
		{
			if (this->vectorProduseHome[i]->getID() == idCautare)
			{
				nr++;
			}
		}
		delete[] this->vectorProduseHome;
		this->nrProduseHome = this->nrProduseHome - nr;
		this->vectorProduseHome = new Produs * [this->nrProduseHome];
		int poz = 0;
		for (int i = 0; i < copie.nrProduseHome; i++)
		{
			if (copie.vectorProduseHome[i]->getID() != idCautare)
			{
				this->vectorProduseHome[poz] = new Produs(*copie.vectorProduseHome[i]);
				poz++;
			}
		}
		return *this;
	}

	///////////////////////////FISIERE/////////////////////

	//Fisiere text
	//Scriere in fisier text
	friend ofstream& operator<<(ofstream& file, const Home& f)
	{
		file << f.nrProduseHome << endl;
		for (int i = 0; i < f.nrProduseHome; i++)
		{
			file << *f.vectorProduseHome[i];
		}
		return file;
	}
	//Citire din fisier text
	friend ifstream& operator>>(ifstream& file, Home& f)
	{
		for (int i = 0; i < f.nrProduseHome; i++)
		{
			delete f.vectorProduseHome[i];
		}
		delete[] f.vectorProduseHome;
		file >> f.nrProduseHome;
		f.vectorProduseHome = new Produs * [f.nrProduseHome];
		for (int i = 0; i < f.nrProduseHome; i++)
		{
			Produs paux;
			file >> paux;
			f.vectorProduseHome[i] = new Produs(paux);
		}
		return file;
	}

	//Destructor
	~Home()
	{
		for (int i = 0; i < this->nrProduseHome; i++)
		{
			delete this->vectorProduseHome[i];
		}
		delete[] this->vectorProduseHome;
	}
};

//Clasa template pentru gestionarea comenzilor
template<typename COM>
class GestiuneComenzi
{
	int numarComenzi;
	COM* colectieComenzi;
public:
	//Constructorul fara parametrii
	GestiuneComenzi()
	{
		this->numarComenzi = 0;
		this->colectieComenzi = NULL;
	}

	//Constructorul cu parametrii
	GestiuneComenzi(int numarComenzi, COM* colectieComenzi)
	{
		this->numarComenzi = numarComenzi;
		this->colectieComenzi = new COM[this->numarComenzi];
		for (int i = 0; i < this->numarComenzi; i++)
		{
			this->colectieComenzi[i] = colectieComenzi[i];
		}
	}

	//Getteri
	int getNumarComenzi()
	{
		return this->numarComenzi;
	}
	COM* getColectieComenzi()
	{
		return this->colectieComenzi;
	}

	//Setteri
	void setComenzi(int nrCom, COM* colectieCom)
	{
		if (this->colectieComenzi != NULL)
		{
			delete[] this->colectieComenzi;
		}
		this->numarComenzi = nrCom;
		this->colectieComenzi = new COM[this->numarComenzi];
		for (int i = 0; i < this->numarComenzi; i++)
		{
			this->colectieComenzi[i] = colectieCom[i];
		}
	}

	//Constructorul de copiere
	GestiuneComenzi(const GestiuneComenzi& g)
	{
		this->numarComenzi = g.numarComenzi;
		this->colectieComenzi = new COM[this->numarComenzi];
		for (int i = 0; i < this->numarComenzi; i++)
		{
			this->colectieComenzi[i] = g.colectieComenzi[i];
		}
	}

	//Operatorul =
	GestiuneComenzi& operator=(const GestiuneComenzi& g)
	{
		if (this != &g)
		{
			if (this->colectieComenzi != NULL)
			{
				delete[] this->colectieComenzi;
			}
			this->numarComenzi = g.numarComenzi;
			this->colectieComenzi = new COM[this->numarComenzi];
			for (int i = 0; i < this->numarComenzi; i++)
			{
				this->colectieComenzi[i] = g.colectieComenzi[i];
			}
		}
		return *this;
	}

	//Operatorul+=
	//Adauga comanda
	GestiuneComenzi& operator+=(COM elementNou)
	{
		GestiuneComenzi copie = *this;
		delete[] this->colectieComenzi;
		this->numarComenzi++;
		this->colectieComenzi = new COM[this->numarComenzi];
		for (int i = 0; i < copie.numarComenzi; i++)
		{
			this->colectieComenzi[i] = copie.colectieComenzi[i];
		}
		this->colectieComenzi[copie.numarComenzi] = elementNou;
		return *this;
	}

	//Operatorul <<
	friend ostream& operator<<(ostream& out, const GestiuneComenzi& g)
	{
		out << "Numar comenzi:" << g.numarComenzi << endl;
		out << "Comenzi:" << endl;
		for (int i = 0; i < g.numarComenzi; i++)
		{
			out << g.colectieComenzi[i] << endl << endl;
		}
		return out;
	}

	//Metoda generare rapoarte cu valoarea totala a comenzilor
	float valoareTotalaComenzi()
	{
		float suma = 0;
		for (int i = 0; i < this->numarComenzi; i++)
		{
			suma = suma + this->colectieComenzi[i].comandaTotalaFaraTransport();
		}
		return suma;
	}

	//Fisiere text
	//Scriere in fisier text
	friend ofstream& operator<<(ofstream& file, const GestiuneComenzi& g)
	{
		file << g.numarComenzi << endl;
		for (int i = 0; i < g.numarComenzi; i++)
		{
			file << g.colectieComenzi[i] << endl;
		}
		file << endl;
		return file;
	}
	//Citire din fisier text
	friend ifstream& operator>>(ifstream& file, GestiuneComenzi& g)
	{
		if (g.colectieComenzi != NULL)
		{
			delete[] g.colectieComenzi;
		}
		file >> g.numarComenzi;
		g.colectieComenzi = new Comanda[g.numarComenzi];
		for (int i = 0; i < g.numarComenzi; i++)
		{
			file >> g.colectieComenzi[i];
		}
		return file;
	}

	//Destructorul
	~GestiuneComenzi()
	{
		if (this->colectieComenzi != NULL)
		{
			delete[] this->colectieComenzi;
		}
	}
};


//Functii template pentru sortarea in vectorul STL
template<typename clasa>
bool comparareRecenzii(clasa cls1, clasa cls2)
{
	return cls1 > cls2;
}

template<typename clasa>
bool compararePreturi(clasa cls1, clasa cls2)
{
	return cls1 < cls2;
}

template<typename clasa>
bool comparareRecenziiCresc(clasa cls1, clasa cls2)
{
	return cls1 <= cls2;
}

//Functie pentru meniu
void meniuComenzi()
{
	cout << endl << endl << endl << endl;
	cout << "-----------------------------------------------------------------" << endl;
	cout << "-\t\t        Meniu     \t\t\t\t-" << endl;
	cout << "- 1.Adauga produs in categoria femei\t\t\t\t-" << endl;
	cout << "- 2.Adauga produs in categoria barbati\t\t\t\t-" << endl;
	cout << "- 3.Adauga produs in categoria home\t\t\t\t-" << endl;
	cout << "- 4.Adauga comanda\t\t\t\t\t\t-" << endl;
	cout << "- 5.Vizualizare comenzi\t\t\t\t\t\t-" << endl;
	cout << "- 6.Creare raport text cu toate comenzile\t\t\t-" << endl;
	cout << "- 7.Vizualizare raport dupa zi\t\t\t\t\t-" << endl;
	cout << "- 8.Vizualizare raport dupa luna\t\t\t\t-" << endl;
	cout << "- 9.Vizualizare raport dupa an\t\t\t\t\t-" << endl;
	cout << "- 10.Afisare produse femei descrescator dupa recenzia medie\t-" << endl;
	cout << "- 11.Afisare produse barbati crescator dupa pret\t\t-" << endl;
	cout << "- 12.Iesire meniu\t\t\t\t\t\t-" << endl;
	cout << "-----------------------------------------------------------------" << endl;
	cout << endl << endl << endl << endl;
}


void main()
{
	//Schimbam culoarea
	system("Color E0");

	//Obiecte produs
	cout << "--------------------------Obiecte produs-------------------------" << endl << endl;

	int recenzii1[] = { 5,4 };
	int recenzii2[] = { 5,5,5 };
	int recenzii3[] = { 4,4 };
	int recenzii4[] = { 3,4,4 };
	int recenzii6[] = { 2,3,2,1 };
	//Barbati
	Produs p1("Tricou", 30, S, "H&M", 2, recenzii1);
	Produs p2("Sapca", 25, M, "Cropp", 3, recenzii2);
	Produs p3("Pulover", 125, XS, "Zara", 2, recenzii3);
	Produs p9("Bocanci", 250, XL, "Deichamnn", 3, recenzii4);
	Produs p25("Blugi", 120, L, "Bershka", 4, recenzii6);
	//Femei
	Produs p4("Rochia", 150, M, "C&A", 3, recenzii2);
	Produs p5("Cercei", 30, Necunoscuta, "Zara", 2, recenzii3);
	Produs p6("Fusta", 90, L, "Zara", 3, recenzii4);
	Produs p7("Sandale", 200, S, "Deichamnn", 3, recenzii2);
	Produs p8("Colier", 60, Necunoscuta, "Meli-Melo", 2, recenzii3);
	//Home
	Produs p10("Masa", 120, Necunoscuta, "Jysk", 2, recenzii1);
	Produs p11("Scaun", 70, Necunoscuta, "Ikea", 3, recenzii2);
	Produs p12("Oglinda-Baie", 220, Necunoscuta, "Dedeman", 2, recenzii3);
	Produs p13("Canapea", 900, XL, "Mobexpert", 3, recenzii4);
	Produs p26("Dulap", 1500, Necunoscuta, "Ikea", 3, recenzii4);

	cout << "Id:" << p1.getID() << " Denumire:" << p1.getDenumire() << " Pret:" << p1.getPret() << " Marime:" << p1.getMarime() << " Firma:" << p1.getFirma() << " Nr recenzii:" << p1.getNrRecenzii() << " Recenzii:";
	for (int i = 0; i < p1.getNrRecenzii(); i++) {
		cout << p1.getRecenzii()[i] << ";";
	}
	cout << endl << endl;

	cout << "Id:" << p2.getID() << " Denumire:" << p2.getDenumire() << " Pret:" << p2.getPret() << " Marime:" << p2.getMarime() << " Firma:" << p2.getFirma() << " Nr recenzii:" << p2.getNrRecenzii() << " Recenzii:";
	for (int i = 0; i < p2.getNrRecenzii(); i++) {
		cout << p2.getRecenzii()[i] << ";";
	}
	cout << endl << endl;

	cout << "Id:" << p3.getID() << " Denumire:" << p3.getDenumire() << " Pret:" << p3.getPret() << " Marime:" << p3.getMarime() << " Firma:" << p3.getFirma() << " Nr recenzii:" << p3.getNrRecenzii() << " Recenzii:";
	for (int i = 0; i < p3.getNrRecenzii(); i++) {
		cout << p3.getRecenzii()[i] << ";";
	}

	//Setteri
	cout << endl << endl << "------------------------Modificare produs cu id 1-----------------" << endl << endl;
	p1.setDenumire("Bluza");
	p1.setMarime(Necunoscuta);
	p1.setPret(100);
	p1.setFirma("C&A");
	int recenzii5[] = { 3,2,2,2,2 };
	p1.setRecenzii(5, recenzii5);
	cout << "Id:" << p1.getID() << " Denumire:" << p1.getDenumire() << " Pret:" << p1.getPret() << " Marime:" << p1.getMarime() << " Firma:" << p1.getFirma() << " Nr recenzii:" << p1.getNrRecenzii() << " Recenzii:";
	for (int i = 0; i < p1.getNrRecenzii(); i++) {
		cout << p1.getRecenzii()[i] << ";";
	}


	//Constructorul de copiere
	cout << endl << endl << "------------------------Constructorul de copiere-----------------" << endl << endl;
	cout << p1 << endl;
	Produs p14 = p1;
	cout << p14;

	//Operatorul =
	cout << endl << endl << "------------------------Operatorul = -----------------" << endl << endl;
	cout << p2 << endl;
	Produs p15;
	p15 = p2;
	cout << p15;

	//Metode
	cout << endl << endl << "------------------------Metode-----------------" << endl << endl;
	cout << "Pretul fara TVA al produsului p1 este:" << p1.pretFaraTva() << " lei." << endl;
	cout << "Pretul fara TVA al produsului p4 este:" << p4.pretFaraTva() << " lei." << endl;
	cout << "Pretul fara TVA al produsului p10 este:" << p10.pretFaraTva() << " lei." << endl << endl;

	cout << "Recenzia medie pentru produsul p1 este:" << p1.recenzieMedie() << " stele." << endl;
	cout << "Recenzia medie pentru produsul p4 este:" << p4.recenzieMedie() << " stele." << endl;
	cout << "Recenzia medie pentru produsul p10 este:" << p10.recenzieMedie() << " stele." << endl;


	//Operatorul << si >>
	cout << endl << endl << "------------------------Operatorul << si >>-----------------" << endl << endl;
	cout << p1 << endl << endl;
	Produs p16;
	cin >> p16;
	cout << endl << endl << p16;

	//Operatorul index[]
	cout << endl << endl << "------------------------Operatorul index[]-----------------" << endl << endl;
	int index;
	do
	{
		cout << "Introduceti pozitia dorita:";
		cin >> index;
		try
		{
			cout << "Recenzia este:" << p1[index];
			break;
		}
		catch (EroareMesaj er)
		{
			cout << er.mesaj << endl;
		}
	} while (index < 0 || index >= p1.getNrRecenzii());


	//Operatorul +(obiect+valoare)
	cout << endl << endl << "------------------------Operatorul +(obiect+valoare)-----------------" << endl << endl;
	cout << "Pret vechi:" << p1.getPret() << endl;
	p1 = p1 + 10;
	cout << "Pret nou:" << p1.getPret();

	//Operatorul +(valoare+obiect)
	cout << endl << endl << "------------------------Operatorul +(valoare+obiect)-----------------" << endl << endl;
	cout << "Pret vechi:" << p1.getPret() << endl;
	p1 = 10 + p1;
	cout << "Pret nou:" << p1.getPret();

	//Operatorul ++(preincrementare)
	cout << endl << endl << "------------------------Operatorul ++(preincrementare)-----------------" << endl << endl;
	try
	{
		++p2;
		cout << p2;
	}
	catch (EroareMesaj er)
	{
		cout << er.mesaj;
	}

	//Operatorul ++(postincrementare)
	cout << endl << endl << "------------------------Operatorul ++(postincrementare)-----------------" << endl << endl;
	try
	{
		p1++;
		cout << p1;
	}
	catch (EroareMesaj er)
	{
		cout << er.mesaj;
	}

	//Operatorul +=
	cout << endl << endl << "------------------------Operatorul +=-----------------" << endl << endl;
	p1 += 5;
	cout << p1;

	//Operatorul cast la int
	cout << endl << endl << "------------------------Operatorul cast la int-----------------" << endl << endl;
	int rez = (int)p1;
	cout << "Recenzia maxima a produsului p1 este:" << rez;

	//Operatorul ==
	cout << endl << endl << "------------------------Operatorul ==-----------------" << endl << endl;
	if (p1 == p2)
	{
		cout << "Au aceeasi recenzie medie!";
	}
	else
	{
		cout << "Nu au aceeasi recenzie medie!";
	}

	//Fisiere
	cout << endl << endl << "------------------------Fisiere----------------------" << endl << endl;

	//Fisier text
	cout << endl << endl << "------------------------Fisier text----------------------" << endl << endl;
	//Scriere in fisier text
	ofstream f("Produse.txt", ios::out);
	f << p1;
	f << p2;
	f.close();
	Produs p17;
	Produs p18;
	//Citire din fisier text
	ifstream g("produse.txt", ios::in);
	if (g.is_open())
	{
		g >> p17;
		g >> p18;
		g.close();
	}
	else
	{
		cout << "Nu exista fisierul!";
	}
	cout << p17 << endl << endl;
	cout << p18;

	//Fisier binar
	cout << endl << endl << "------------------------Fisier binar----------------------" << endl << endl;
	//Scriere in fisier binar
	fstream fisBin1("ProduseBinar.bin", ios::out | ios::binary);
	p1.scriereBinarProduse(fisBin1);
	p2.scriereBinarProduse(fisBin1);
	fisBin1.close();
	//Citire din fisier binar
	fstream fisBin2("ProduseBinar.bin", ios::in | ios::binary);
	Produs p19;
	Produs p20;
	if (fisBin2.is_open())
	{
		p19.citireBinarProduse(fisBin2);
		p20.citireBinarProduse(fisBin2);
		fisBin2.close();
	}
	else
	{
		cout << "Fisierul nu exista";
	}
	cout << p19 << endl << endl;
	cout << p20;












	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "////////////////////////////////////////////////";
	//Obiecte comanda
	cout << endl << endl << "------------------------Obiecte comanda----------------------" << endl << endl;

	Data data1;
	data1.zi = 23;
	data1.luna = 6;
	data1.an = 2019;
	Data data2;
	data2.zi = 15;
	data2.luna = 8;
	data2.an = 2019;
	Data data3;
	data3.zi = 20;
	data3.luna = 11;
	data3.an = 2019;
	Data data4;
	data4.zi = 23;
	data4.luna = 6;
	data4.an = 2018;
	Data data5;
	data5.zi = 3;
	data5.luna = 1;
	data5.an = 2020;
	Data data6;
	data6.zi = 8;
	data6.luna = 1;
	data6.an = 2020;
	Data data7;
	data7.zi = 5;
	data7.luna = 9;
	data7.an = 2020;

	Produs** vectorProduse = new Produs * [3];
	vectorProduse[0] = &p1;
	vectorProduse[1] = &p2;
	vectorProduse[2] = &p3;
	Produs** vectorProduse2 = new Produs * [4];
	vectorProduse2[0] = &p1;
	vectorProduse2[1] = &p2;
	vectorProduse2[2] = &p3;
	vectorProduse2[3] = &p3;
	Produs** vectorProduse3 = new Produs * [2];
	vectorProduse3[0] = &p3;
	vectorProduse3[1] = &p9;
	Produs** vectorProduse4 = new Produs * [3];
	vectorProduse4[0] = &p6;
	vectorProduse4[1] = &p10;
	vectorProduse4[2] = &p11;
	Produs** vectorProduse5 = new Produs * [5];
	vectorProduse5[0] = &p9;
	vectorProduse5[1] = &p6;
	vectorProduse5[2] = &p7;
	vectorProduse5[3] = &p10;
	vectorProduse5[4] = &p11;
	Produs** vectorProduse6 = new Produs * [4];
	vectorProduse6[0] = &p12;
	vectorProduse6[1] = &p9;
	vectorProduse6[2] = &p8;
	vectorProduse6[3] = &p2;

	Comanda c1(data7, 3, vectorProduse, "Curier", 20);
	Comanda c4(data1, 2, vectorProduse3, "Curier", 15);
	Comanda c5(data2, 3, vectorProduse4, "Posta", 7);
	Comanda c15(data6, 5, vectorProduse5, "Curier", 13);
	Comanda c16(data1, 4, vectorProduse6, "Curier", 15);


	cout << "Id comanda:" << c1.getIdComanda() << " Data comanda:" << c1.getData().zi << "." << c1.getData().luna << "." << c1.getData().an << " Tip transport:" << c1.getTipTransport() << " Cost transport:" << c1.getValoareTransport();
	cout << endl;
	cout << "Numar produse:" << c1.getNrProduse() << " ";
	cout << endl << "Produse:" << endl;
	for (int i = 0; i < c1.getNrProduse(); i++)
	{
		cout << "Id:" << c1.getProdus()[i]->getID() << " Denumire:" << c1.getProdus()[i]->getDenumire() << " Pret:" << c1.getProdus()[i]->getPret() << " Marime:" << c1.getProdus()[i]->getMarime() << " Firma:" << c1.getProdus()[i]->getFirma() << " Nr recenzii:" << c1.getProdus()[i]->getNrRecenzii() << " Recenzii:";
		for (int j = 0; j < c1.getProdus()[i]->getNrRecenzii(); j++) {
			cout << c1.getProdus()[i]->getRecenzii()[j] << ";";
		}
		cout << endl;
	}

	//Setteri
	cout << endl << endl << "------------------------Modificare comanda cu id 1----------------------" << endl << endl;
	c1.setData(data2);
	c1.setProduse(4, vectorProduse2);
	c1.setTipTransport("Posta", 15);
	cout << "Id comanda:" << c1.getIdComanda() << " Data comanda:" << c1.getData().zi << "." << c1.getData().luna << "." << c1.getData().an << " Tip transport:" << c1.getTipTransport() << " Cost transport:" << c1.getValoareTransport();
	cout << endl;
	cout << "Numar produse:" << c1.getNrProduse() << " ";
	cout << endl << "Produse:" << endl;
	for (int i = 0; i < c1.getNrProduse(); i++)
	{
		cout << "Id:" << c1.getProdus()[i]->getID() << " Denumire:" << c1.getProdus()[i]->getDenumire() << " Pret:" << c1.getProdus()[i]->getPret() << " Marime:" << c1.getProdus()[i]->getMarime() << " Firma:" << c1.getProdus()[i]->getFirma() << " Nr recenzii:" << c1.getProdus()[i]->getNrRecenzii() << " Recenzii:";
		for (int j = 0; j < c1.getProdus()[i]->getNrRecenzii(); j++) {
			cout << c1.getProdus()[i]->getRecenzii()[j] << ";";
		}
		cout << endl;
	}

	//Constructorul de copiere
	cout << endl << endl << "------------------------Constructorul de copiere-----------------" << endl << endl;
	cout << c1 << endl << endl;
	Comanda c2 = c1;
	cout << c2;

	//Operatorul =
	cout << endl << endl << "------------------------Operatorul = -----------------" << endl << endl;
	Comanda c3;
	c3 = c1;
	cout << c3;

	//Metode
	cout << endl << endl << "------------------------Metode-----------------" << endl << endl;
	cout << "Valoarea comenzii c1 fara TVA este:" << c1.comandaFaraTVA() << " lei." << endl;
	cout << "Valoarea comenzii c4 fara TVA este:" << c4.comandaFaraTVA() << " lei." << endl;
	cout << "Valoarea comenzii c5 fara TVA este:" << c5.comandaFaraTVA() << " lei." << endl << endl;

	cout << "Valoarea totala cu transport a comenzii c1 este:" << c1.comandaTotala() << " lei" << endl;
	cout << "Valoarea totala cu transport a comenzii c4 este:" << c4.comandaTotala() << " lei" << endl;
	cout << "Valoarea totala cu transport a comenzii c5 este:" << c5.comandaTotala() << " lei" << endl << endl;

	cout << "Valoarea comenzii c1 cu discount de Black Friday este:" << c1.comandaCuDiscount(0.2) << " lei." << endl;
	cout << "Valoarea comenzii c4 cu discount de Black Friday este:" << c4.comandaCuDiscount(0.3) << " lei." << endl;
	cout << "Valoarea comenzii c5 cu discount de Black Friday este:" << c5.comandaCuDiscount(0.4) << " lei." << endl;

	//Operatorul << si >>
	cout << endl << endl << "------------------------Operatorul << si >>-----------------" << endl << endl;
	cin >> c3;
	cout << endl << endl << c3;

	//Operatorul index[]
	cout << endl << endl << "------------------------Operatorul index[]-----------------" << endl << endl;
	int index1;
	do
	{
		cout << "Introduceti pozitia dorita:";
		cin >> index1;
		try
		{
			cout << "Produsul este:" << c1[index1];
			break;
		}
		catch (EroareMesaj er)
		{
			cout << er.mesaj << endl;
		}
	} while (index1 < 0 || index1 >= c1.getNrProduse());


	//Operatorul -(obiect-valoare)
	cout << endl << endl << "------------------------Operatorul -(obiect-valoare)-----------------" << endl << endl;
	cout << endl << "Comanda c1 inainte de reducere" << endl << c1 << endl << endl;
	c1 = c1 - 10;
	cout << endl << "Comanda c1 dupa reducere" << endl << c1;

	//Operatorul --(predecrementare)
	cout << endl << endl << "------------------------Operatorul --(predecrementare)-----------------" << endl << endl;
	cout << "Valoarea transportului inainte de reducere:" << c1.getValoareTransport() << endl;
	cout << "Valoarea transportului inainte de reducere:" << c2.getValoareTransport() << endl;
	c1 = --c2;
	cout << "Valoarea transportului dupa reducere:" << c1.getValoareTransport() << endl;
	cout << "Valoarea transportului dupa reducere:" << c2.getValoareTransport() << endl;

	//Operatorul --(postdecrementare)
	cout << endl << endl << "------------------------Operatorul --(postdecrementare)-----------------" << endl << endl;
	cout << "Valoarea transportului inainte de reducere:" << c1.getValoareTransport() << endl;
	cout << "Valoarea transportului inainte de reducere:" << c2.getValoareTransport() << endl;
	c1 = c2--;
	cout << "Valoarea transportului dupa reducere:" << c1.getValoareTransport() << endl;
	cout << "Valoarea transportului dupa reducere:" << c2.getValoareTransport() << endl;

	//Operatorul cast la Produs
	cout << endl << endl << "------------------------Operatorul cast la Produs-----------------" << endl << endl;
	Produs rez1 = (Produs)c1;
	cout << "Produsul cel mai scump din comanda c1 este:" << endl;
	cout << rez1;

	//Operatorul +=
	cout << endl << endl << "------------------------Operatorul +=-----------------" << endl << endl;
	c1 += p1;
	cout << c1;

	//Operatorul -=
	cout << endl << endl << "------------------------Operatorul -=-----------------" << endl << endl;
	c1 -= 1;
	cout << c1;

	//Fisiere
	cout << endl << endl << "------------------------Fisiere----------------------" << endl << endl;

	//Fisier text
	cout << endl << endl << "------------------------Fisier text----------------------" << endl << endl;
	//Scriere in fisier text
	ofstream h("Comenzi.txt", ios::out);
	h << c1;
	h << c4;
	h.close();
	ifstream j("Comenzi.txt", ios::in);
	Comanda c6;
	Comanda c7;
	if (j.is_open())
	{
		j >> c6;
		j >> c7;
		j.close();
	}
	else
	{
		cout << "Nu exista fisierul!";
	}
	cout << c6 << endl;
	cout << c7 << endl;













	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "////////////////////////////////////////////////";
	//Obiecte categoria femei
	cout << endl << endl << "------------------------Obiecte categoria femei----------------------" << endl << endl;
	Produs** vectorProduseFemei1 = new Produs * [4];
	vectorProduseFemei1[0] = &p4;
	vectorProduseFemei1[1] = &p5;
	vectorProduseFemei1[2] = &p6;
	vectorProduseFemei1[3] = &p7;

	Femei f1(4, vectorProduseFemei1);
	cout << "Numar produse categoria femei:" << f1.getNrProduseFemei() << endl;
	cout << "Produse:" << endl;
	for (int i = 0; i < f1.getNrProduseFemei(); i++)
	{
		cout << "Id:" << f1.getVectorProduseFemei()[i]->getID() << " Denumire:" << f1.getVectorProduseFemei()[i]->getDenumire() << " Pret:" << f1.getVectorProduseFemei()[i]->getPret() << " Marime:" << f1.getVectorProduseFemei()[i]->getMarime() << " Firma:" << f1.getVectorProduseFemei()[i]->getFirma() << " Nr recenzii:" << f1.getVectorProduseFemei()[i]->getNrRecenzii() << " Recenzii:";
		for (int j = 0; j < f1.getVectorProduseFemei()[i]->getNrRecenzii(); j++) {
			cout << f1.getVectorProduseFemei()[i]->getRecenzii()[j] << ";";
		}
		cout << endl;
	}

	cout << endl << endl << "------------------------Modificare categoria femei----------------------" << endl << endl;
	Femei f2;
	Produs** vectorProduseFemei2 = new Produs * [5];
	vectorProduseFemei2[0] = &p4;
	vectorProduseFemei2[1] = &p5;
	vectorProduseFemei2[2] = &p6;
	vectorProduseFemei2[3] = &p7;
	vectorProduseFemei2[4] = &p8;
	f2.setProduseFemei(5, vectorProduseFemei2);
	cout << "Numar produse categoria femei:" << f2.getNrProduseFemei() << endl;
	cout << "Produse:" << endl;
	for (int i = 0; i < f2.getNrProduseFemei(); i++)
	{
		cout << "Id:" << f2.getVectorProduseFemei()[i]->getID() << " Denumire:" << f2.getVectorProduseFemei()[i]->getDenumire() << " Pret:" << f2.getVectorProduseFemei()[i]->getPret() << " Marime:" << f2.getVectorProduseFemei()[i]->getMarime() << " Firma:" << f2.getVectorProduseFemei()[i]->getFirma() << " Nr recenzii:" << f2.getVectorProduseFemei()[i]->getNrRecenzii() << " Recenzii:";
		for (int j = 0; j < f2.getVectorProduseFemei()[i]->getNrRecenzii(); j++) {
			cout << f2.getVectorProduseFemei()[i]->getRecenzii()[j] << ";";
		}
		cout << endl;
	}

	//Constructorul de copiere
	cout << endl << endl << "------------------------Constructorul de copiere-----------------" << endl << endl;
	cout << f1 << endl << endl;
	Femei f3 = f1;
	cout << f3;

	//Operatorul =
	cout << endl << endl << "------------------------Operatorul = -----------------" << endl << endl;
	Femei f4;
	f4 = f1;
	cout << f4;

	//Metode(functii virtuale)
	cout << endl << endl << "------------------------Metode(functii virtuale)-----------------" << endl << endl;
	cout << "Numarul de produse de la firma Zara este:" << f1.nrProduseFirma("Zara") << endl;
	cout << "Numar de produse cu recenzia medie intre 4 si 5:" << f1.nrProduseMedieRecenzii(4, 5) << endl;

	//Metode(functii virtual pure)
	cout << endl << endl << "------------------------Metode(functii virtual pure)-----------------" << endl << endl;
	cout << "Numarul de produse cu marimea s:" << f1.nrProduseMarimeaS() << endl;

	//Operatorul << si >>
	cout << endl << endl << "------------------------Operatorul << si >>-----------------" << endl << endl;
	cin >> f4;
	cout << endl << endl << f4;

	//Operatorul index[]
	cout << endl << endl << "------------------------Operatorul index[]-----------------" << endl << endl;
	int index2;
	do
	{
		cout << "Introduceti pozitia dorita:";
		cin >> index2;
		try
		{
			cout << "Produsul este:" << f1[index2];
			break;
		}
		catch (EroareMesaj er)
		{
			cout << er.mesaj << endl;
		}
	} while (index2 < 0 || index2 >= f1.getNrProduseFemei());


	//Operatorul +=
	cout << endl << endl << "------------------------Operatorul +=-----------------" << endl << endl;
	f1 += p1;
	cout << f1;

	//Operatorul -=
	cout << endl << endl << "------------------------Operatorul -=-----------------" << endl << endl;
	f1 -= 1;
	cout << f1;

	//Fisiere
	cout << endl << endl << "------------------------Fisiere----------------------" << endl << endl;

	//Fisier text
	cout << endl << endl << "------------------------Fisier text----------------------" << endl << endl;
	//Scriere in fisier text
	ofstream fis1("Femei.txt", ios::out);
	fis1 << f1;
	fis1.close();
	//Citire din fisier text
	Femei f5;
	ifstream fis2("Femei.txt", ios::in);
	if (fis2.is_open())
	{
		fis2 >> f5;
		fis2.close();
	}
	else
	{
		cout << "Fisierul nu exista!";
	}
	cout << f5;












	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "////////////////////////////////////////////////";
	//Obiecte categoria barbati
	cout << endl << endl << "------------------------Obiecte categoria barbati----------------------" << endl << endl;
	Produs** vectorProduseBarbati1 = new Produs * [5];
	vectorProduseBarbati1[0] = &p1;
	vectorProduseBarbati1[1] = &p2;
	vectorProduseBarbati1[2] = &p3;
	vectorProduseBarbati1[3] = &p1;
	vectorProduseBarbati1[4] = &p9;
	Barbati b1(5, vectorProduseBarbati1);
	cout << "Numar produse categoria barbati:" << b1.getNrProduseBarbati() << endl;
	cout << "Produse:" << endl;
	for (int i = 0; i < b1.getNrProduseBarbati(); i++)
	{
		cout << "Id:" << b1.getVectorProduseBarbati()[i]->getID() << " Denumire:" << b1.getVectorProduseBarbati()[i]->getDenumire() << " Pret:" << b1.getVectorProduseBarbati()[i]->getPret() << " Marime:" << b1.getVectorProduseBarbati()[i]->getMarime() << " Firma:" << b1.getVectorProduseBarbati()[i]->getFirma() << " Nr recenzii:" << b1.getVectorProduseBarbati()[i]->getNrRecenzii() << " Recenzii:";
		for (int j = 0; j < b1.getVectorProduseBarbati()[i]->getNrRecenzii(); j++) {
			cout << b1.getVectorProduseBarbati()[i]->getRecenzii()[j] << ";";
		}
		cout << endl;
	}

	cout << endl << endl << "------------------------Modificare categoria barbati----------------------" << endl << endl;
	Barbati b2;
	Produs** vectorProduseBarbati2 = new Produs * [4];
	vectorProduseBarbati2[0] = &p1;
	vectorProduseBarbati2[1] = &p2;
	vectorProduseBarbati2[2] = &p3;
	vectorProduseBarbati2[3] = &p9;
	b2.setProduseBarbati(4, vectorProduseBarbati2);
	cout << "Numar produse categoria barbati:" << b2.getNrProduseBarbati() << endl;
	cout << "Produse:" << endl;
	for (int i = 0; i < b2.getNrProduseBarbati(); i++)
	{
		cout << "Id:" << b2.getVectorProduseBarbati()[i]->getID() << " Denumire:" << b2.getVectorProduseBarbati()[i]->getDenumire() << " Pret:" << b2.getVectorProduseBarbati()[i]->getPret() << " Marime:" << b2.getVectorProduseBarbati()[i]->getMarime() << " Firma:" << b2.getVectorProduseBarbati()[i]->getFirma() << " Nr recenzii:" << b2.getVectorProduseBarbati()[i]->getNrRecenzii() << " Recenzii:";
		for (int j = 0; j < b2.getVectorProduseBarbati()[i]->getNrRecenzii(); j++) {
			cout << b2.getVectorProduseBarbati()[i]->getRecenzii()[j] << ";";
		}
		cout << endl;
	}

	//Constructorul de copiere
	cout << endl << endl << "------------------------Constructorul de copiere-----------------" << endl << endl;
	cout << b1 << endl << endl;
	Barbati b3 = b1;
	cout << b3;

	//Operatorul =
	cout << endl << endl << "------------------------Operatorul = -----------------" << endl << endl;
	Barbati b4;
	b4 = b1;
	cout << b4;

	//Metode(functii virtuale)
	cout << endl << endl << "------------------------Metode(functii virtuale)-----------------" << endl << endl;
	cout << "Numarul de produse de la firma Nike este:" << b1.nrProduseFirma("Nike") << endl;
	cout << "Numar de produse cu recenzia medie intre 3 si 5:" << b1.nrProduseMedieRecenzii(3, 5) << endl;

	//Metode(functii virtual pure)
	cout << endl << endl << "------------------------Metode(functii virtual pure)-----------------" << endl << endl;
	cout << "Numarul de produse cu marimea s:" << b1.nrProduseMarimeaS() << endl;

	//Operatorul << si >>
	cout << endl << endl << "------------------------Operatorul << si >>-----------------" << endl << endl;
	cin >> b4;
	cout << endl << endl << b4;

	//Operatorul index[]
	cout << endl << endl << "------------------------Operatorul index[]-----------------" << endl << endl;
	int index3;
	do
	{
		cout << "Introduceti pozitia dorita:";
		cin >> index3;
		try
		{
			cout << "Produsul este:" << b1[index3];
			break;
		}
		catch (EroareMesaj er)
		{
			cout << er.mesaj << endl;
		}
	} while (index3 < 0 || index3 >= b1.getNrProduseBarbati());


	//Operatorul +=
	cout << endl << endl << "------------------------Operatorul +=-----------------" << endl << endl;
	b1 += p1;
	cout << b1;

	//Operatorul -=
	cout << endl << endl << "------------------------Operatorul -=-----------------" << endl << endl;
	b1 -= 2;
	cout << b1;

	//Fisiere
	cout << endl << endl << "------------------------Fisiere----------------------" << endl << endl;

	//Fisier text
	cout << endl << endl << "------------------------Fisier text----------------------" << endl << endl;
	//Scriere in fisier text
	ofstream fis3("Barbati.txt", ios::out);
	fis3 << b1;
	fis3.close();
	//Citire din fisier text
	Barbati b5;
	ifstream fis4("Barbati.txt", ios::in);
	if (fis4.is_open())
	{
		fis4 >> b5;
		fis4.close();
	}
	else
	{
		cout << "Fisierul nu exista!";
	}
	cout << b5;











	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "////////////////////////////////////////////////";
	//Obiecte categoria home
	cout << endl << endl << "------------------------Obiecte categoria home----------------------" << endl << endl;
	Produs** vectorProduseHome1 = new Produs * [3];
	vectorProduseHome1[0] = &p10;
	vectorProduseHome1[1] = &p11;
	vectorProduseHome1[2] = &p12;
	Home h1(3, vectorProduseHome1);
	cout << "Numar produse categoria home:" << h1.getNrProduseHome() << endl;
	cout << "Produse:" << endl;
	for (int i = 0; i < h1.getNrProduseHome(); i++)
	{
		cout << "Id:" << h1.getVectorProduseHome()[i]->getID() << " Denumire:" << h1.getVectorProduseHome()[i]->getDenumire() << " Pret:" << h1.getVectorProduseHome()[i]->getPret() << " Marime:" << h1.getVectorProduseHome()[i]->getMarime() << " Firma:" << h1.getVectorProduseHome()[i]->getFirma() << " Nr recenzii:" << h1.getVectorProduseHome()[i]->getNrRecenzii() << " Recenzii:";
		for (int j = 0; j < h1.getVectorProduseHome()[i]->getNrRecenzii(); j++) {
			cout << h1.getVectorProduseHome()[i]->getRecenzii()[j] << ";";
		}
		cout << endl;
	}

	cout << endl << endl << "------------------------Modificare categoria home----------------------" << endl << endl;
	Produs** vectorProduseHome2 = new Produs * [4];
	vectorProduseHome2[0] = &p10;
	vectorProduseHome2[1] = &p11;
	vectorProduseHome2[2] = &p12;
	vectorProduseHome2[3] = &p13;
	Home h2;
	h2.setProduseHome(4, vectorProduseHome2);
	cout << "Numar produse categoria home:" << h2.getNrProduseHome() << endl;
	cout << "Produse:" << endl;
	for (int i = 0; i < h2.getNrProduseHome(); i++)
	{
		cout << "Id:" << h2.getVectorProduseHome()[i]->getID() << " Denumire:" << h2.getVectorProduseHome()[i]->getDenumire() << " Pret:" << h2.getVectorProduseHome()[i]->getPret() << " Marime:" << h2.getVectorProduseHome()[i]->getMarime() << " Firma:" << h2.getVectorProduseHome()[i]->getFirma() << " Nr recenzii:" << h2.getVectorProduseHome()[i]->getNrRecenzii() << " Recenzii:";
		for (int j = 0; j < h2.getVectorProduseHome()[i]->getNrRecenzii(); j++) {
			cout << h2.getVectorProduseHome()[i]->getRecenzii()[j] << ";";
		}
		cout << endl;
	}

	//Constructorul de copiere
	cout << endl << endl << "------------------------Constructorul de copiere-----------------" << endl << endl;
	cout << h1 << endl << endl;
	Home h3 = h1;
	cout << h3;

	//Operatorul =
	cout << endl << endl << "------------------------Operatorul = -----------------" << endl << endl;
	Home h4;
	h4 = h1;
	cout << h4;

	//Metode(functii virtuale)
	cout << endl << endl << "------------------------Metode(functii virtuale)-----------------" << endl << endl;
	cout << "Numarul de produse de la firma Jysk este:" << h1.nrProduseFirma("Jysk") << endl;
	cout << "Numar de produse cu recenzia medie intre 4 si 5:" << h1.nrProduseMedieRecenzii(4, 5) << endl;

	//Metode(functii virtual pure)
	cout << endl << endl << "------------------------Metode(functii virtual pure)-----------------" << endl << endl;
	cout << "Numarul de produse cu marimea s:" << h1.nrProduseMarimeaS() << endl;

	//Operatorul << si >>
	cout << endl << endl << "------------------------Operatorul << si >>-----------------" << endl << endl;
	cin >> h4;
	cout << endl << endl << h4;

	//Operatorul index[]
	cout << endl << endl << "------------------------Operatorul index[]-----------------" << endl << endl;
	int index4;
	do
	{
		cout << "Introduceti pozitia dorita:";
		cin >> index4;
		try
		{
			cout << "Produsul este:" << h1[index4];
			break;
		}
		catch (EroareMesaj er)
		{
			cout << er.mesaj << endl;
		}
	} while (index4 < 0 || index4 >= h1.getNrProduseHome());


	//Operatorul +=
	cout << endl << endl << "------------------------Operatorul +=-----------------" << endl << endl;
	h1 += p10;
	cout << h1;

	//Operatorul -=
	cout << endl << endl << "------------------------Operatorul -=-----------------" << endl << endl;
	h1 -= 11;
	cout << h1;

	//Fisiere
	cout << endl << endl << "------------------------Fisiere----------------------" << endl << endl;

	//Fisier text
	cout << endl << endl << "------------------------Fisier text----------------------" << endl << endl;
	//Scriere in fisier text
	ofstream fis5("Home.txt", ios::out);
	fis5 << h1;
	fis5.close();
	//Citire din fisier text
	Home h5;
	ifstream fis6("Home.txt", ios::in);
	if (fis6.is_open())
	{
		fis6 >> h5;
		fis6.close();
	}
	else
	{
		cout << "Fisierul nu exista!";
	}
	cout << h5;











	cout << endl << endl << "-----------------------------------------Latebinding--------------------------------" << endl << endl;
	Categorie* pc1;
	Femei* pf = new Femei(f1);
	pc1 = pf;
	cout << "Numarul de produse de la firma Zara este:" << pc1->nrProduseFirma("Zara") << endl;
	cout << "Numarul de produse de la firma Zara este:" << pf->nrProduseFirma("Zara") << endl << endl;

	Categorie* pc2;
	Barbati* pb = new Barbati(b1);
	pc2 = pb;
	cout << "Numar de produse cu recenzia medie intre 4 si 5 este:" << pc2->nrProduseMedieRecenzii(4, 5) << endl;
	cout << "Numar de produse cu recenzia medie intre 4 si 5 este:" << pb->nrProduseMedieRecenzii(4, 5) << endl << endl;

	Categorie* pc3;
	Home* ph = new Home(h1);
	pc3 = ph;
	cout << "Numar de produse cu marimea S:" << pc3->nrProduseMarimeaS() << endl;
	cout << "Numar de produse cu marimea S:" << ph->nrProduseMarimeaS() << endl;













	//Clasa template
	cout << endl << endl << "-----------------------------------Clasa template - generare rapoarte---------------------------" << endl << endl;
	cout << endl << endl << "-----------------------------------------  Colectie comenzi --------------------------------" << endl << endl;
	Comanda* vectorComenzi1 = new Comanda[3];
	vectorComenzi1[0] = c1;
	vectorComenzi1[1] = c4;
	vectorComenzi1[2] = c5;
	GestiuneComenzi<Comanda> raport1(3, vectorComenzi1);
	cout << raport1 << endl << endl;

	cout << endl << endl << "--------------------------Generare raport total comenzi dupa o anumita data--------------------------" << endl << endl;
	//Generare raport total comenzi dupa o anumita data
	int* data = new int[3];
	cout << "Introduceti ziua dorita:";
	cin >> data[0];
	cout << "Introduceti luna dorita:";
	cin >> data[1];
	cout << "Introduceti anul dorit:";
	cin >> data[2];
	float total = 0;
	string numeFisier = "raportComenzi" + to_string(data[0]) + to_string(data[1]) + to_string(data[2]) + ".txt";
	ofstream file1(numeFisier, ios::out);
	for (int i = 0; i < raport1.getNumarComenzi(); i++)
	{
		if (raport1.getColectieComenzi()[i].getData().zi == data[0] && raport1.getColectieComenzi()[i].getData().luna == data[1] && raport1.getColectieComenzi()[i].getData().an == data[2])
		{
			file1 << raport1.getColectieComenzi()[i];
			cout << raport1.getColectieComenzi()[i] << endl << endl;
			total = total + raport1.getColectieComenzi()[i].comandaTotalaFaraTransport();
		}
	}
	if (total > 0)
	{
		cout << "Valoarea totala a comenzilor din data:" << data[0] << "-" << data[1] << "-" << data[2] << " este:" << total;
	}
	else
	{
		cout << "Nu s-au gasit comenzi pentru data:" << data[0] << "-" << data[1] << "-" << data[2];
	}
	file1 << "Valoarea totala a comenzilor pentru data:" << data[0] << "-" << data[1] << "-" << data[2] << " este:" << total;
	file1.close();


	cout << endl << endl << "--------------------------Generare raport total comenzi dupa o anumita luna din an--------------------------" << endl << endl;
	//Generare raport total comenzi dupa o anumita luna din an
	int* data15 = new int[2];
	cout << "Introduceti luna cautata: ";
	cin >> data15[0];
	cout << "Introduceti an cautat: ";
	cin >> data15[1];
	float total1 = 0;
	string numeFisier1 = "raportComenzi" + to_string(data15[0]) + to_string(data15[1]) + ".txt";
	ofstream file2(numeFisier1, ios::out);
	for (int i = 0; i < raport1.getNumarComenzi(); i++)
	{
		if (raport1.getColectieComenzi()[i].getData().luna == data15[0] && raport1.getColectieComenzi()[i].getData().an == data15[1])
		{
			file2 << raport1.getColectieComenzi()[i];
			cout << raport1.getColectieComenzi()[i] << endl << endl;
			total1 = total1 + raport1.getColectieComenzi()[i].comandaTotalaFaraTransport();
		}
	}
	if (total1 > 0)
	{
		cout << "Valoarea totala a comenzilor din luna " << data15[0] << " si anul " << data15[1] << " este:" << total1;
	}
	else
	{
		cout << "Nu s-au gasit comenzi din luna " << data15[0] << " si anul " << data15[1];
	}
	file2 << "Valoarea totala a comenzilor pentru luna " << data15[0] << " si anul " << data15[1] << " este:" << total1;
	file2.close();


	cout << endl << endl << "-----------------------------Generare raport total comenzi pentru an---------------------------" << endl << endl;
	//Generare raport total comenzi pentru an
	int* data16 = new int[1];
	cout << "Introduceti an cautat: ";
	cin >> data16[0];
	float total2 = 0;
	string numeFisier2 = "raportComenzi" + to_string(data16[0]) + ".txt";
	ofstream file3(numeFisier2, ios::out);
	for (int i = 0; i < raport1.getNumarComenzi(); i++)
	{
		if (raport1.getColectieComenzi()[i].getData().an == data16[0])
		{
			file3 << raport1.getColectieComenzi()[i];
			cout << raport1.getColectieComenzi()[i] << endl << endl;
			total2 = total2 + raport1.getColectieComenzi()[i].comandaTotalaFaraTransport();
		}
	}
	if (total2 > 0)
	{
		cout << "Valoarea totala a comenzilor din anul " << data16[0] << " este:" << total2;
	}
	else
	{
		cout << "Nu s-au gasit comenzi din anul " << data16[0];
	}
	file3 << "Valoarea totala a comenzilor pentru anul " << data16[0] << " este:" << total2;
	file3.close();















	//STL
	cout << endl << endl << "----------------------------------------- STL --------------------------------" << endl << endl;
	//Femei
	vector<Produs> vectorFemei1;
	for (int i = 0; i < f1.getNrProduseFemei(); i++)
	{
		vectorFemei1.push_back(*f1.getVectorProduseFemei()[i]);
	}

	cout << endl << endl << "----------------------------------------- Produse femei inainte de sortare --------------------------------" << endl << endl;
	vector<Produs>::iterator it;
	for (it = vectorFemei1.begin(); it != vectorFemei1.end(); it++)
	{
		cout << *it << endl << endl;
	}

	cout << endl << endl << "--------------------------------- Produse femei sortare dupa recenzia medie descrescator --------------------------" << endl << endl;
	sort(vectorFemei1.begin(), vectorFemei1.end(), comparareRecenzii<Produs>);
	for (it = vectorFemei1.begin(); it != vectorFemei1.end(); it++)
	{
		cout << *it << endl << endl;
	}

	//Barbati
	vector<Produs> vectorBarbati1;
	for (int i = 0; i < b1.getNrProduseBarbati(); i++)
	{
		vectorBarbati1.push_back(*b1.getVectorProduseBarbati()[i]);
	}

	cout << endl << endl << "----------------------------------------- Produse barbati inainte de sortare --------------------------------" << endl << endl;
	vector<Produs>::iterator it1;
	for (it1 = vectorBarbati1.begin(); it1 != vectorBarbati1.end(); it1++)
	{
		cout << *it1 << endl << endl;
	}

	cout << endl << endl << "----------------------------------------- Produse barbati sortare crescator dupa pret --------------------------------" << endl << endl;
	sort(vectorBarbati1.begin(), vectorBarbati1.end(), compararePreturi<Produs>);
	for (it1 = vectorBarbati1.begin(); it1 != vectorBarbati1.end(); it1++)
	{
		cout << *it1 << endl << endl;
	}











	Produs** vectFem = new Produs * [5];
	vectFem[0] = &p4;
	vectFem[1] = &p5;
	vectFem[2] = &p6;
	vectFem[3] = &p7;
	vectFem[4] = &p8;
	Femei f15(5, vectFem);

	Produs** vectBar = new Produs * [5];
	vectBar[0] = &p1;
	vectBar[1] = &p2;
	vectBar[2] = &p3;
	vectBar[3] = &p9;
	vectBar[4] = &p25;
	Barbati b15(5, vectBar);

	Produs** vectHom = new Produs * [5];
	vectHom[0] = &p10;
	vectHom[1] = &p11;
	vectHom[2] = &p12;
	vectHom[3] = &p13;
	vectHom[4] = &p26;
	Home h15(5, vectHom);

	Comanda* vectorComenzi2 = new Comanda[5];
	vectorComenzi2[0] = c1;
	vectorComenzi2[1] = c4;
	vectorComenzi2[2] = c5;
	vectorComenzi2[3] = c15;
	vectorComenzi2[4] = c16;
	GestiuneComenzi<Comanda> gc1(5, vectorComenzi2);

	//Meniu
	int meniu;
	do
	{
		meniuComenzi();
		cout << "Introduceti comanda din meniu: ";
		cin >> meniu;
		if (meniu == 1)
		{
			system("cls");
			cout << "Introduceti produsul de femei!" << endl << endl;
			Produs* pf = new Produs();
			cin >> *pf;
			f15 += *pf;
			cout << endl << "Produsul a fost adaugat!";
		}
		if (meniu == 2)
		{
			system("cls");
			cout << "Introduceti produsul de barbati!" << endl << endl;
			Produs* pb = new Produs();
			cin >> *pb;
			b15 += *pb;
			cout << endl << "Produsul a fost adaugat!";
		}
		if (meniu == 3)
		{
			system("cls");
			cout << "Introduceti produsul home!" << endl << endl;
			Produs* ph = new Produs();
			cin >> *ph;
			h15 += *ph;
			cout << endl << "Produsul a fost adaugat!";
		}
		if (meniu == 4)
		{
			system("cls");
			cout << "Introduceti noua comanda!" << endl << endl;
			Comanda pc;
			cin >> pc;
			gc1 += pc;
			cout << endl << "Comanda a fost adaugata!";
		}
		if (meniu == 5)
		{
			system("cls");
			cout << "Comenzile sunt:" << endl << endl;
			cout << gc1;
		}
		if (meniu == 6)
		{
			system("cls");
			GestiuneComenzi<Comanda> gc2;
			cout << "Se creeaza raport text cu toate comenzile!" << endl;
			string numeFisier15 = "raportComenzi.txt";
			ofstream file15(numeFisier15, ios::out);
			file15 << gc1;
			file15.close();
			cout << "Raportul a fost creat!" << endl;
			ifstream file16(numeFisier15, ios::in);
			file16 >> gc2;
			file16.close();
			cout << "Raportul este:" << endl << endl;
			cout << gc2;
		}
		if (meniu == 7)
		{
			system("cls");
			int* data = new int[3];
			cout << "Introduceti ziua dorita:";
			cin >> data[0];
			cout << "Introduceti luna dorita:";
			cin >> data[1];
			cout << "Introduceti anul dorit:";
			cin >> data[2];
			float total = 0;
			string numeFisier = "raportComenzi" + to_string(data[0]) + to_string(data[1]) + to_string(data[2]) + ".txt";
			ofstream file1(numeFisier, ios::out);
			cout << endl << "Raportul este:" << endl << endl;
			for (int i = 0; i < gc1.getNumarComenzi(); i++)
			{
				if (gc1.getColectieComenzi()[i].getData().zi == data[0] && gc1.getColectieComenzi()[i].getData().luna == data[1] && gc1.getColectieComenzi()[i].getData().an == data[2])
				{
					file1 << gc1.getColectieComenzi()[i];
					cout << gc1.getColectieComenzi()[i] << endl << endl;
					total = total + gc1.getColectieComenzi()[i].comandaTotalaFaraTransport();
				}
			}
			if (total > 0)
			{
				cout << "Valoarea totala a comenzilor din data:" << data[0] << "-" << data[1] << "-" << data[2] << " este:" << total;
			}
			else
			{
				cout << "Nu s-au gasit comenzi pentru data:" << data[0] << "-" << data[1] << "-" << data[2];
			}
			file1 << "Valoarea totala a comenzilor pentru data:" << data[0] << "-" << data[1] << "-" << data[2] << " este:" << total;
			file1.close();
		}
		if (meniu == 8)
		{
			system("cls");
			int* data5 = new int[2];
			cout << "Introduceti luna cautata: ";
			cin >> data5[0];
			cout << "Introduceti an cautat: ";
			cin >> data5[1];
			float total1 = 0;
			string numeFisier1 = "raportComenzi" + to_string(data5[0]) + to_string(data5[1]) + ".txt";
			ofstream file2(numeFisier1, ios::out);
			cout << endl << "Raportul este:" << endl << endl;
			for (int i = 0; i < gc1.getNumarComenzi(); i++)
			{
				if (gc1.getColectieComenzi()[i].getData().luna == data5[0] && gc1.getColectieComenzi()[i].getData().an == data5[1])
				{
					file2 << gc1.getColectieComenzi()[i];
					cout << gc1.getColectieComenzi()[i] << endl << endl;
					total1 = total1 + gc1.getColectieComenzi()[i].comandaTotalaFaraTransport();
				}
			}
			if (total1 > 0)
			{
				cout << "Valoarea totala a comenzilor din luna " << data5[0] << " si anul " << data5[1] << " este:" << total1;
			}
			else
			{
				cout << "Nu s-au gasit comenzi din luna " << data5[0] << " si anul " << data5[1];
			}
			file2 << "Valoarea totala a comenzilor pentru luna " << data5[0] << " si anul " << data5[1] << " este:" << total1;
			file2.close();
		}
		if (meniu == 9)
		{
			system("cls");
			int* data6 = new int[1];
			cout << "Introduceti an cautat: ";
			cin >> data6[0];
			float total2 = 0;
			string numeFisier2 = "raportComenzi" + to_string(data6[0]) + ".txt";
			ofstream file3(numeFisier2, ios::out);
			cout << endl << "Raportul este:" << endl << endl;
			for (int i = 0; i < gc1.getNumarComenzi(); i++)
			{
				if (gc1.getColectieComenzi()[i].getData().an == data6[0])
				{
					file3 << gc1.getColectieComenzi()[i];
					cout << gc1.getColectieComenzi()[i] << endl << endl;
					total2 = total2 + gc1.getColectieComenzi()[i].comandaTotalaFaraTransport();
				}
			}
			if (total2 > 0)
			{
				cout << "Valoarea totala a comenzilor din anul " << data6[0] << " este:" << total2;
			}
			else
			{
				cout << "Nu s-au gasit comenzi din anul " << data6[0];
			}
			file3 << "Valoarea totala a comenzilor pentru anul " << data6[0] << " este:" << total2;
			file3.close();
		}
		if (meniu == 10)
		{
			system("cls");
			cout << "Produsele au fost sortate descrescator in functie de recenzia medie!" << endl << endl;
			vector<Produs> vectorFemei15;
			for (int i = 0; i < f15.getNrProduseFemei(); i++)
			{
				vectorFemei15.push_back(*f15.getVectorProduseFemei()[i]);
			}
			vector<Produs>::iterator it15;
			sort(vectorFemei15.begin(), vectorFemei15.end(), comparareRecenzii<Produs>);
			for (it15 = vectorFemei15.begin(); it15 != vectorFemei15.end(); it15++)
			{
				cout << *it15 << endl << endl;
			}
		}
		if (meniu == 11)
		{
			system("cls");
			cout << "Produsele au fost sortate crescator in functie de preturi!" << endl << endl;
			vector<Produs> vectorBarbati15;
			for (int i = 0; i < b15.getNrProduseBarbati(); i++)
			{
				vectorBarbati15.push_back(*b15.getVectorProduseBarbati()[i]);
			}
			vector<Produs>::iterator it15;
			sort(vectorBarbati15.begin(), vectorBarbati15.end(), compararePreturi<Produs>);
			for (it15 = vectorBarbati15.begin(); it15 != vectorBarbati15.end(); it15++)
			{
				cout << *it15 << endl << endl;
			}
		}
		if (meniu == 12)
		{
			system("cls");
			cout << "La revedere!";
		}
	} while (meniu > 0 && meniu < 12);
}