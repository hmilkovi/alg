#include <iostream>
using namespace std;

int Fibo(int poz){
	if (poz <= 1) {
		return poz;
	} else {
		return Fibo(poz-1) + Fibo(poz-2);
	}
}

void NegFibo(int prvi, int drugi, int n){
	if (n > 0){
		cout << drugi - prvi << " ";
		NegFibo(drugi - prvi, prvi, n-1);
	}
}

int main(){
	
	int pozicija;
	int rezultat;
	int n;
	
	cout << "Racunanje Fibonacija, ne..." << endl;
	cout << "---------------------------" << endl;
	cout << "Unesite poziciju broja: ";
	cin >> pozicija;
	
	rezultat = Fibo(pozicija);
	
	cout << "---------------------------" << endl;
	cout << pozicija << ". broj iznosi: " << rezultat << endl;
	cout << "---------------------------" << endl;
	cout << "Negativni Fibonacci brojevi" << endl;
	cout << "---------------------------" << endl;
	cout << "Koliko brojeva? ";
	cin >> n;
	cout << "---------------------------" << endl;
	NegFibo(0, 1, n);
	
	return 0;
}
