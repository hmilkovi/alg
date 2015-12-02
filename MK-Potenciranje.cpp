#include <iostream>
using namespace std;

int PotSmanji(int baza, int pot){
	if (pot == 1) {
		return baza;
	} else {
		return baza * PotSmanji(baza, pot - 1);
	}
}

int PotPodjeli(int baza, int pot){
	if (pot == 1){
		return baza;
	} else{
		if (pot%2 == 0){
			return PotPodjeli(baza, pot/2) * PotPodjeli(baza, pot/2);
		} else {
			return PotPodjeli(baza, pot/2) * PotPodjeli(baza, (pot/2)+1);
		}
	}
}


int main(){
	
	int baza;
	int potencija;
	int rezultat;
	int rezultat2;
		
	cout << "Racunanje potenciranja rekurzivno" << endl;
	cout << "---------------------------------" << endl;
	cout << "Unesi bazu: ";
	cin >> baza;
	cout << "Unesi potenciju: ";
	cin >> potencija;
	cout << "---------------------------------" << endl;
	
	//potenciranje SMANJI ZA JEDAN
	rezultat = PotSmanji(baza, potencija);
	rezultat2 = PotPodjeli(baza, potencija);
	cout << "Potenciranje smanji za jedan: " << rezultat << endl;
	cout << "Potenciranje podjeli pa vladaj: " << rezultat2 << endl;
	return 0;
}
