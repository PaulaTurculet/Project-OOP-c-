#include <iostream>
#include <cstring>
using namespace std;


template <class T>

class Produs{

	protected:
		T pret;
		char * nume;


	public:
		Produs();
		Produs(T, const char*);
		Produs(const char*);

		template<class U>
		friend istream& operator>>(istream&, Produs<U>&);

		virtual void citeste(istream&){}
		void adaugaTip(const char*);

		T getPret();
		char* getNume();
};

class TipFel{

	virtual int calculeazaSuma() = 0;
};
template <class T>
Produs<T>::Produs(T pret, const char* nume){
	this->pret = pret;
	int len = strlen(nume);
	this->nume = new char[len + 1];
	strcpy(this->nume, nume);
}
template <class T>
Produs<T>::Produs(const char* nume){
	int len = strlen(nume);
	this->nume = new char[len + 1];
	strcpy(this->nume, nume);
}
template <class T>
Produs<T>::Produs(){}
template <class T>
istream& operator>>(istream& in, Produs<T>& obj){
	obj.citeste(in);
	return in;
}
template <class T>
T Produs<T>::getPret(){
	return pret;
}

template <class T>
char* Produs<T>::getNume(){
	return nume;
}

template <class T>
void Produs<T>::adaugaTip(const char* tip){
	strcat(nume, tip);
}
template <class T>
class FelPrincipal : public TipFel{

	private:
		Produs<T>** felPrincipal;
		int numarProduse;

	public:
		FelPrincipal();

		template<class U>
		friend istream& operator>>(istream&, FelPrincipal<U>&);
		virtual int calculeazaSuma();
};

template <class T>
class Frigarui : public Produs<T>{

	public:
		Frigarui();
};
template <class T>
class Tocana : public Produs<T>{

	public:
		Tocana();
};
template <class T>
class Vita : public Produs<T>{

	protected:
		bool facut;

	public:
		//Vita(float);
        Vita(T);
		virtual void citeste(istream&);
};
template <class T>
class ChateaubriandStroganoff : public Vita<T>{

	public:
		ChateaubriandStroganoff();
};
template <class T>
class ChateaubriandFile : public Vita<T>{

	public:
		ChateaubriandFile();
};
template <class T>
class Garnitura : public Produs<T>{

	public:
		Garnitura(T, const char*);
};
template <class T>
class CartofiPrajiti : public Garnitura<T>{

	public:
		CartofiPrajiti();
};
template <class T>
class CartofiPiure : public Garnitura<T>{

	public:
		CartofiPiure();
};
template <class T>
class OrezSarbesc : public Garnitura<T>{

	public:
		OrezSarbesc();
};

template <class T>
FelPrincipal<T>::FelPrincipal(){
	numarProduse = 2;
	felPrincipal = new Produs<T>*[numarProduse];
	felPrincipal[0] = felPrincipal[1] = nullptr;
}
template <class T>
int FelPrincipal<T>::calculeazaSuma(){

	int sum = 0;

	for (int i = 0; i < numarProduse; ++i){
		if (felPrincipal[i] != nullptr){
			T pret = felPrincipal[i]->getPret();
			cout << felPrincipal[i]->getNume() << " " << pret << endl;
			sum += pret;
		}
	}

	return sum;
}
template <class T>
istream& operator>>(istream& in, FelPrincipal<T>& obj){

	cout << "fel principal?(d/n)";
	char answ;
	in >> answ;

	if (answ == 'd'){
		cout << "pui/vita?";
		in >> answ;
		if (answ == 'p'){
			cout << "frigarui/tocana?";
			in >> answ;
			if (answ == 'f'){
				obj.felPrincipal[0] = new Frigarui<T>();
			}
			else{
				obj.felPrincipal[0] = new Tocana<T>();
			}
		}
		else{
			cout << "stroganoff/file?";
			in >> answ;
			if (answ == 's'){
				obj.felPrincipal[0] = new ChateaubriandStroganoff<T>();
				char aux[11];
				strcpy(aux, "stroganoff");
				obj.felPrincipal[0]->adaugaTip(aux);
			}
			else{
				obj.felPrincipal[0] = new ChateaubriandFile<T>();
				char aux[4];
				strcpy(aux, "file");
				obj.felPrincipal[0]->adaugaTip(aux);
			}
			in >> (*obj.felPrincipal[0]);
		}

		cout << "cartofi/orez?";
		in >> answ;
		if (answ == 'c'){
			cout << "fierti/prajiti?";
			in >> answ;
			if (answ == 'f'){
				obj.felPrincipal[1] = new CartofiPiure<T>();
				char aux[8];
				strcpy(aux, "fierti");
				obj.felPrincipal[1]->adaugaTip(aux);
			}
			else{
				obj.felPrincipal[1] = new CartofiPrajiti<T>();
				char aux[9];
				strcpy(aux, "prajiti");
				obj.felPrincipal[1]->adaugaTip(aux);
			}
		}
		else{
			obj.felPrincipal[1] = new OrezSarbesc<T>();
		}
	}

	return in;
}
template <class T>
Frigarui<T>::Frigarui() : Produs<T>(15, "Frigarui"){}

template <class T>
Tocana<T>::Tocana() : Produs<T>(20, "Tocana"){}

template <class T>
Vita<T>::Vita(T pret) : Produs<T> (pret, "Chateaubriand"){}

template <class T>
ChateaubriandStroganoff<T>::ChateaubriandStroganoff() : Vita<T>(20){}
template <class T>
ChateaubriandFile<T>::ChateaubriandFile() : Vita<T>(25){}
template <class T>
Garnitura<T>::Garnitura(T pret, const char* nume) : Produs<T>(pret, nume){}
template <class T>
CartofiPrajiti<T>::CartofiPrajiti() : Garnitura<T>(5, "Cartofi"){}
template <class T>
CartofiPiure<T>::CartofiPiure() : Garnitura<T>(4, "Cartofi"){}
template <class T>
OrezSarbesc<T>::OrezSarbesc() : Garnitura<T>(6, "Orez sarbesc"){}
template <class T>
void Vita<T>::citeste(istream& in){

	cout << "sa fie bine facuta?(d/n)";
	char answ;
	in >> answ;
	if (answ == 'd'){
		this->facut = true;
	}
	else{
		this->facut = false;
	}
}
template <class T>
class Desert : public TipFel{

	private:
		Produs<T>* desert;

	public:
		Desert();

		template <class U>
		friend istream& operator>>(istream&, Desert<U>&);
		virtual int calculeazaSuma();
};
template <class T>
class Inghetata : public Produs<T>{

	private:
		int limitaInf, limitaSup;
		int numarCupe;

	public:
		Inghetata();

		virtual void citeste(istream&);
};
template <class T>
class Tort : public Produs<T>{

	public:
		Tort();

		virtual void citeste(istream&){}
};
template <class T>
Desert<T>::Desert(){
	desert = nullptr;
}
template <class T>
int Desert<T>::calculeazaSuma(){
	if (desert != nullptr){
		T pret = desert->getPret();
		cout << desert->getNume() << " " << pret << endl;
		return pret;
	}

	return 0;
}

//raspunsurile se vor da cu initiala
template <class T>
istream& operator>>(istream& in, Desert<T>& obj){

	cout << "tort/inghetata/nimic?";
	char answ;
	in >> answ;

	if (answ == 't'){
		obj.desert = new Tort<T>();
	}
	else if (answ == 'i'){
		obj.desert = new Inghetata<T>();
		in >> (*obj.desert);
	}
	else{
		obj.desert = nullptr;
	}

	return in;
}
template <class T>
Inghetata<T>::Inghetata() : Produs<T>(5, "inghetata"){
	limitaInf = 3;
	limitaSup = 5;
	this->pret = 1;
}
template <class T>
void Inghetata<T>::citeste(istream& in){

	bool ok = true;

	while (ok){
		ok = false;
		cout << "numar de cupe?(3-5)";
		in >> numarCupe;
		if (numarCupe < limitaInf || numarCupe > limitaSup){
			ok = true;
		}
		else{
			this->pret *= numarCupe;
			this->numarCupe = numarCupe;
			char aux[2];
			aux[0] = (48 + numarCupe);
			aux[1] = '\0';
			strcat(this->nume, aux);
		}
	}
}

template <class T>
Tort<T>::Tort() : Produs<T>(10, "tort"){}

template <class T>
class Ciorba{

	protected:
		Produs<T>** produse;
		char* tip;
		int numarProduse;

	public:
		Ciorba();

		template<class U>
		friend istream& operator>>(istream&, Ciorba<U>&);
		virtual int calculeazaSuma();
};
template <class T>
class Smantana : public Produs<T>{

	public:
		Smantana();

		virtual void citeste(istream&){}
};
template <class T>
class Ardei : public Produs<T>{

	public:
		Ardei();

		virtual void citeste(istream&){}
};
template <class T>
class CiorbaDeBurta : public Produs<T>{

	public:
		CiorbaDeBurta();
		CiorbaDeBurta(T);

		virtual void citeste(istream&){}
};
template <class T>
class CiorbaDeLegume : public Produs<T>{

	public:
		CiorbaDeLegume();
		CiorbaDeLegume(float);

		virtual void citeste(istream&){}
};
template <class T>
class CiorbaDeCiuperci : public Produs<T>{

	public:
		CiorbaDeCiuperci();
		CiorbaDeCiuperci(T);

		virtual void citeste(istream&){}
};
template <class T>
Ciorba<T>::Ciorba(){
	numarProduse = 3;
	produse = new Produs<T>*[numarProduse];
	produse[0] = produse[1] = produse[2] = nullptr;
}

//raspunsurile se vor da cu initiala
template <class T>
istream& operator>>(istream& in, Ciorba<T>& obj){

	cout << "doriti ciorba?(d/n)?";
	char answ;
	cin >> answ;
	if (answ == 'd'){
		cout << "legume/burta/ciuperci?";
		cin >> answ;
		if (answ == 'l'){
			obj.produse[0] = new CiorbaDeLegume<T>();
		}
		else if (answ == 'b'){
			obj.produse[0] = new CiorbaDeBurta<T>();
		}
		else{
			obj.produse[0] = new CiorbaDeCiuperci<T>();
		}

		if (answ == 'l' || answ == 'b'){
			cout << "ardei?(d/n)";
			cin >> answ;
			if (answ == 'd'){
				obj.produse[1] = new Ardei<T>();
			}

			cout << "smantana?(d/n)";
			cin >> answ;
			if (answ == 'd'){
				obj.produse[2] = new Smantana<T>();
			}
		}
	}
	return in;
}
template <class T>
int Ciorba<T>::calculeazaSuma(){

	int sum = 0;

	for (int i = 0; i < numarProduse; ++i){
		if (produse[i] != nullptr){
			T pret = produse[i]->getPret();
			cout << produse[i]->getNume() << " " << pret << endl;
			sum += produse[i]->getPret();
		}
	}
	cout << endl;

	return sum;
}
template <class T>
CiorbaDeBurta<T>::CiorbaDeBurta() : Produs<T>(10, "ciorba burta"){}
template <class T>
CiorbaDeLegume<T>::CiorbaDeLegume() : Produs<T>(8, "ciorba legume"){}
template <class T>
CiorbaDeCiuperci<T>::CiorbaDeCiuperci() : Produs<T>(6, "ciorba ciuperci"){}
template <class T>
Ardei<T>::Ardei() : Produs<T>(1, "ardei"){}
template <class T>
Smantana<T>::Smantana() : Produs<T>(2, "smantana"){}

template <class T>
class Bautura : public TipFel{

	public:
		Produs<T>* bauturi;
		Bautura();

		template<class U>
		friend istream& operator >> (istream&, Bautura<U>&);
		virtual int calculeazaSuma();
};
template <class T>
class ApaPlata : public Produs<T>{

	public:
		ApaPlata();
		virtual void citeste(istream&){}
};
template <class T>
class BereAlcool : public Produs<T>{

	public:
		BereAlcool();
		virtual void citeste(istream&){}
};
template <class T>
class BereFaraAlcool : public Produs<T>{

	public:
		BereFaraAlcool();
		virtual void citeste(istream&){}
};
template <class T>
class Vin : public Produs<T>{

	protected:
		char* tip;

	public:
		Vin();
		Vin(T);
		Vin(T, const char*);
		Vin(const char*);
		virtual void citeste(istream&){}
};
template <class T>
class VinVarsat : public Vin<T>{

	private:
		int cantitate;
		int portie;

	public:
		VinVarsat();
		VinVarsat(int, const char*);

		virtual void citeste(istream&);
};
template <class T>
class VinSticla : public Vin<T>{

	public:
		VinSticla();
		VinSticla(const char*);

		virtual void citeste(istream&);
};
template <class T>
Bautura<T>::Bautura(){
	bauturi = nullptr;
}
template <class T>
int Bautura<T>::calculeazaSuma(){
	if (bauturi != nullptr){
		T pret = bauturi->getPret();
		cout << bauturi->getNume() << " " << pret << endl;
		return pret;
	}

	return 0;
}

//raspunsurile se vor da cu initiala
template <class T>
istream& operator >> (istream& in, Bautura<T>& obj){

	cout << "vin/apa/bere/nimic?(initiala)";
	char answ;
	in >> answ;

	if (answ == 'v'){
		cout << "varsat/sticla?";
		in >> answ;
		if (answ == 'v'){
			obj.bauturi = new VinVarsat<T>();
		}
		else{
			obj.bauturi = new VinSticla<T>();
		}
		in >> (*obj.bauturi);
	}
	else if (answ == 'b'){
		cout << "cu/fara alcool(c/f)";
		char answ;
		in >> answ;

		if (answ == 'c'){
			obj.bauturi = new BereAlcool<T>();
		}
		else{
			obj.bauturi = new BereFaraAlcool<T>();
		}
	}
	else if (answ == 'a'){
		obj.bauturi = new ApaPlata<T>();
	}
	else{
		obj.bauturi = nullptr;
	}

	return in;

}
template <class T>
ApaPlata<T>::ApaPlata() : Produs<T>(5, "apa"){}
template <class T>
BereAlcool<T>::BereAlcool() : Produs<T>(7, "bere alcool"){}
template <class T>
BereFaraAlcool<T>::BereFaraAlcool() : Produs<T>(6, "bere fara alcool"){}
template <class T>
Vin<T>::Vin(){}
template <class T>
Vin<T>::Vin(const char* nume) : Produs<T>(nume){}
template <class T>
Vin<T>::Vin(T pret, const char* tip) : Produs<T>(pret, "vin"){
	int len = strlen(tip);
	this->tip = new char[len + 1];
	strcpy(this->tip, tip);
}
template <class T>
VinVarsat<T>::VinVarsat() : Vin<T>("vin varsat"){
	this->pret = 10;
	this->portie = 100;
}
template <class T>
VinVarsat<T>::VinVarsat(int cantitate, const char* tip) : Vin<T>(cantitate * 10, tip){
	this->cantitate = cantitate;
	this->portie = 100;
}
template <class T>
void VinVarsat<T>::citeste(istream& in){

	cout << "rosu/alb?";
	char answ;
	in >> answ;
	if (answ == 'r'){
		char *tip = new char[5];
		strcpy(tip, "rosu");
		strcat(this->nume, tip);
	}
	else{
		char *tip = new char[4];
		strcpy(tip, "alb");
		strcat(this->nume, tip);
	}

	cout << "cati ml?";
	in >> cantitate;
	this->pret *= (cantitate / portie);
}
template <class T>
void VinSticla<T>::citeste(istream& in){

	cout << "bordeux/bolovanu?(x/u)";
	char answ;
	in >> answ;

	if (answ == 'x'){
		this->tip = new char[8];
		strcpy(this->tip, "bordeux");
		strcat(this->nume,this-> tip);
	}
	else{
		this->tip = new char[9];
		strcpy(this->tip, "bolovanu");
		strcat(this->nume, this->tip);
	}
}
template <class T>
VinSticla<T>::VinSticla() : Vin<T>("vin"){
	this->pret = 25;
}
template <class T>
VinSticla<T>::VinSticla(const char* tip) : Vin<T>(25, tip){}

template <class T>
class Comanda{

	private:
		Ciorba<T>* ciorba;
		FelPrincipal<T>* felPrincipal;
		Desert<T>* desert;
		Bautura<T>* bauturi;

	public:
		Comanda();
		~Comanda();

		void rezolvaComanda();
		int calculeazaSuma();
};
template <class T>
class Client{

	private:
		Comanda<T> comanda;

	public:
		Client(){}
		~Client(){}

		void rezolvaClient();
		void iaNota();
};
template <class T>
class Masa{

	private:
		Client<T>** clienti;
		int capacitate;

	public:
		Masa(int);
		~Masa();

		int getCapacitate();

		void rezolvaMasa();
		void iaNota(int*, int);
};

template <class T>
class Chelner{

	private:
		Masa<T>** mese;
		bool* eLibera;
		int numarMese;
		int numarMeseLibere;

	public:
		Chelner(int, int*);
		~Chelner();
		void proceseaza(int*, int);
		int cautaMasa(int);
		void rezolvaMasa(int);
		void iaNota(int, int*, int);
};
///////////
//Comanda//
//////////
template <class T>
void Comanda<T>::rezolvaComanda(){

	bauturi = new Bautura<T>();
	cin >> (*bauturi);

	ciorba = new Ciorba<T>();
	cin >> (*ciorba);

	felPrincipal = new FelPrincipal<T>();
	cin >> (*felPrincipal);

	desert = new Desert<T>();
	cin >> (*desert);

}
template <class T>
Comanda<T>::Comanda(){}
template <class T>
Comanda<T>::~Comanda(){}
template <class T>
int Comanda<T>::calculeazaSuma(){

	int sum = ciorba->calculeazaSuma() + bauturi->calculeazaSuma() + felPrincipal->calculeazaSuma() + desert->calculeazaSuma();
	cout << "total : " << sum << endl;

	return sum;
}

///////////
///Client//
//////////
template <class T>
void Client<T>::rezolvaClient(){
	comanda.rezolvaComanda();
}
template <class T>
void Client<T>::iaNota(){
	comanda.calculeazaSuma();
}

///////////
///Masa////
//////////
template <class T>
Masa<T>::Masa(int numarClienti){

	this->capacitate = numarClienti;
	clienti = new Client<T>*[numarClienti];

	//construim #numarClienti pentru masa actuala
	for (int i = 0; i < numarClienti; ++i){
		clienti[i] = new Client<T>();
	}
}
template <class T>
Masa<T>::~Masa(){

	//eliberam fiecare client
	for (int i = 0; i < capacitate; ++i){
		delete clienti[i];
		clienti[i] = nullptr;
	}

	delete[] clienti;
	clienti = nullptr;
}
template <class T>
int Masa<T>::getCapacitate(){
	return capacitate;
}
template <class T>
void Masa<T>::rezolvaMasa(){

	for (int i = 0; i < capacitate; ++i){
		cout << "Rezolva client " << i << ":\n";
		clienti[i]->rezolvaClient();
	}
}
template <class T>
void Masa<T>::iaNota(int* persoane, int numarPersoaneGata){

	for (int i = 0; i < numarPersoaneGata; ++i){
		clienti[persoane[i]]->iaNota();
	}
}


///////////
//Chelner//
//////////
template <class T>
Chelner<T>::Chelner(int numarMese, int* numarClientiMasa){

	this->numarMese = numarMese;
	mese = new Masa<T>*[numarMese];
	eLibera = new bool[numarMese];

	//construim #numarMese cu #numarClienti[i]
	for (int i = 0; i < numarMese; ++i){
		mese[i] = new Masa<T>(numarClientiMasa[i]);
		eLibera[i] = true;
	}

	this->numarMeseLibere = 0;
}
template <class T>
Chelner<T>::~Chelner(){

	//eliberam fiecare masa
	for (int i = 0; i < numarMese; ++i){
		delete mese[i];
		mese[i] = nullptr;
	}

	delete[] mese;
	mese = nullptr;
}
template <class T>
int Chelner<T>::cautaMasa(int numarPersoane){

	for (int i = 0; i < numarMese; ++i){
		if (mese[i]->getCapacitate() == numarPersoane && eLibera[i]){
			return i;
		}
	}

	return -1;
}
template <class T>
void Chelner<T>::proceseaza(int* grupuri, int numarGrupuri){

	for (int i = 0; i < numarGrupuri; ++i){
		int answ = cautaMasa(grupuri[i]);
		if (answ == -1){
			cout << "Nu exista locuri pentru grupul " << i << endl;
		}
		else{
			eLibera[answ] = false;
			cout << "Rezolva masa " << i << " : \n";
			mese[answ]->rezolvaMasa();
		}
	}

}
template <class T>
void Chelner<T>::iaNota(int numarMasa, int* persoane, int numarPersoaneGata){

	cout << "ia nota pentru masa " << numarMasa << endl;
	mese[numarMasa]->iaNota(persoane, numarPersoaneGata);
}
int main(){

	//capacitatea fiecarei mese (1,1,1)
	int numarMese = 3;
	int *numarClientiMasa = new int[numarMese];
	numarClientiMasa[0] = numarClientiMasa[1] = numarClientiMasa[2] = 1;

	//construim un nou obiect Chelner care va tine evidenta meselor
	Chelner<int> chelner(numarMese, numarClientiMasa);

	//sosesc 3 grupuri de clienti (1, 1, 2). Ultimul nu va avea o masa
	int *grupuri = new int[numarMese];
	grupuri[0] = grupuri[1] = 1;
	grupuri[2] = 2;

	//chelnerul va procesa comenzile fiecarei mese
	chelner.proceseaza(grupuri, numarMese);

	//o persoana pleaca de la masa 0
	int numarPersoaneGata = 1;
	//id ul persoanelor gata
	int* persoane = new int[numarPersoaneGata];
	persoane[0] = 0;

	//ia nota pentru mesele 0 si 1
	chelner.iaNota(1, persoane, numarPersoaneGata);
	chelner.iaNota(0, persoane, numarPersoaneGata);

	int x;
	cin >> x;
	return 0;

}
