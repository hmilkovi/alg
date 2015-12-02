#include <iostream>
using namespace std;

void KreirajHrpu(int polje[], int n){
	for(int i = n/2; i>=1; i--){
		
		int k = i; //indeks roditelja
		int v = polje[i]; //vrijednost roditelja
		bool hrpa = false; //nije hrpa
		
		while ((!hrpa) && (2*k <= n)){
			
			int j = 2*k; //pozicija prvog djeteta
			
			if (j < n){ //da li postoji drugo dijete
				if (polje[j] < polje[j+1]){ //jel drugo dijete veæe
					j = j + 1;
				}
			}
			
			if (v > polje[j]){
				hrpa = true;
			} else {
				polje[k] = polje[j];
				k = j;
				polje[k] = v;
			}
		}
	}
}

void HrpaSort(int polje[], int n){
	for(int i=n; i>=1; i--){
		cout << polje[1] << " ";
		polje[1] = polje[i];
		KreirajHrpu(polje, i-1);
	}	
}

int main(){
	
	int n;
	
	cout << "         Neefikasni hrpasti sort" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "Koliko brojeva zelite unijeti? ";
	cin >> n;
	
	int *polje = new int[n];
	
	//unos brojeva
	cout << "-----------------------------------------" << endl;
	for(int i = 1; i <= n; i++){
		cout << i << ". broj: ";
		cin >> polje[i];
	}
	
	KreirajHrpu(polje, n);
	cout << "-----------------------------------------" << endl;
	HrpaSort(polje, n);

	return 0;
}
