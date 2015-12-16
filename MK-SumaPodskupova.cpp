#include <iostream>
using namespace std;

int n; //koliko brojeva unosimo
int suma; //suma koju tražimo
int ukupno = 0; //zborj svih brojeva
int pozicija; //brojac pozicije
int brojevi[100]; //upisani brojevi
bool odabrani[100]; //koji brojevi su odabrani
int trenutno = 0; //trenutno stanje zbroja brojeva

void Ispis(){
	cout << "----------------------------------" << endl;
	cout << " ";
	for (int i = 0; i < n; i++){
		if (odabrani[i]){
			cout << brojevi[i] << " ";
		}
	}
	cout << endl;
}

void SumaPodskupova(int pozicija){
	
	if (pozicija < n){
		odabrani[pozicija] = 1;
		trenutno += brojevi[pozicija];
		
		if (trenutno == suma){
			Ispis();
		}
		if (trenutno < suma) {
			SumaPodskupova(pozicija+1);
		}
						
		odabrani[pozicija] = 0;
		trenutno -= brojevi[pozicija];
		SumaPodskupova(pozicija+1);
	}
}

int main(){
	
	cout << "----------------------------------" << endl;
	cout << "  Backtracking - Suma podskupova" << endl;
	cout << "----------------------------------" << endl;
	cout << "  Koliko brojeva zelite unijeti? ";
	cin >> n;
	cout << "----------------------------------" << endl;
	
	//unos brojeva
	for (int i = 0; i < n; i++){
		cout << i + 1 << ". broj: ";
		cin >> brojevi[i];
		ukupno = ukupno + brojevi[i];
	}
	
	cout << "----------------------------------" << endl;
	cout << " Koju sumu trazite? ";
	cin >> suma;
	
	SumaPodskupova(0);
	cout << "----------------------------------" << endl;
	return 0;
}
