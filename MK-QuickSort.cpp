#include <iostream>
using namespace std;

void QuickSort(int polje[], int lijevo, int desno){
	int pomocni;
	int i = lijevo + 1;
	int j = desno;
	int sredina = lijevo;
	
	//particioniranje
	while(i <= j){
		while(polje[i] < polje[sredina]){
			i++;
		}
		while(polje[j] > polje[sredina]){
			j--;
		}
		if (i <= j){
			pomocni = polje[i];
			polje[i] = polje[j];
			polje[j] = pomocni;
			i++;
			j--;
		}
	}
	pomocni = polje[j];
	polje[j] = polje[sredina];
	polje[sredina] = pomocni;
		
	//rekurzija
	if(lijevo < j - 1){
		QuickSort(polje, lijevo, j - 1);
	}
	if (i < desno){
		QuickSort(polje, i, desno);
	}	
}

int main(){
	int n;
	int lijevo;
	int desno;
	int broj;
	
	cout << "----------------- QUICKSORT -----------------" << endl;
	cout << "Unesi velicinu polja: ";
	cin >> n;
	
	int *polje = new int[n];
	
	//unos
	for(int i = 0; i < n; i++){
		cout << "Unesite " << i + 1 << ". broj: ";
		cin >> broj;
		polje[i] = broj;
	}
	
	//ispis
	cout << endl << "---------------------------------------------" << endl;
	for(int i = 0; i < n; i++){
		cout << polje[i] << " ";
	}
	
	lijevo = 0;
	desno = n - 1;
	
	QuickSort(polje, lijevo, desno);
	
	//ispis
	cout << endl << "---------------------------------------------" << endl;
	for(int i = 0; i < n; i++){
		cout << polje[i] << " ";
	}
	
	return 0;
}
