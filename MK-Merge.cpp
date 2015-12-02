#include <iostream>
using namespace std;

int n;

void merge(int niz[], int min_indeks, int max_indeks, int sredina){
	
	int i, j, k, pomocni[n];
	
	i = min_indeks;
	k = min_indeks;
	j = sredina + 1;
	
	while (i <= sredina && j <= max_indeks){
		if (niz[i] < niz[j]){
			pomocni[k] = niz[i];
			i++;
		} else {
			pomocni[k] = niz[j];
			j++;
		}
		k++;
	}
	while (i <= sredina){
		pomocni[k] = niz[i];
		k++;
		i++;
	}
	while (j <= max_indeks){
		pomocni[k] = niz[j];
		k++;
		j++;
	}
	for(i = min_indeks; i < k; i++){
		niz[i] = pomocni[i];
	}
}

void mergesort(int niz[], int min_indeks, int max_indeks){
	int sredina;
	
	if(min_indeks < max_indeks){
		sredina = (min_indeks + max_indeks)/2;
		mergesort(niz, min_indeks, sredina);
		mergesort(niz, sredina + 1, max_indeks);
		merge(niz, min_indeks, max_indeks, sredina);
	}
}

int main(){
	int broj;
	cout << "----------------- MERGE SORT -----------------" << endl;
	cout << "  Unesite koliko brojeva zelite sortirati: ";
	cin >> n;
	
	int *niz = new int[n];
	
	//unos brojeva u polje
	cout << "------------------- UNOS ---------------------" << endl;
	for (int i = 0; i < n; i++){
		cout << "Niz[" << i << "] = ";
		cin >> broj;
		niz[i] = broj;
	}
	
	//pozivanje funkcije za Merge sort
	mergesort(niz, 0, n-1);
	
	//ispis polja
	cout << "------------------- ISPIS --------------------" << endl;
	for (int i = 0; i < n; i++){
		cout << niz[i] << " ";
	}
	cout << endl;
	
	return 0;
}
