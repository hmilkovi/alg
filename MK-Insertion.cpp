#include <iostream>
using namespace std;

void InsertionSort(int polje[], int n){
	
	int pomocni;
	int j;
	
	for (int i = 1; i < n; i++){
		pomocni = polje[i];
		j = i - 1;
		while ((j >= 0) && (polje[j] > pomocni)) {
			polje[j+1] = polje[j];
			j--;
		}
		polje[j+1] = pomocni;
	}
}

int main (){
	
	int n;
	int broj;
	
	cout << "-------------- INSERTION SORT --------------" << endl;
	cout << "Velicina polja: ";
	cin >> n;
	
	int *polje = new int[n];
	
	//unos brojeva u polje
	for (int i = 0; i < n; i++){
		cout << i + 1 << ". broj: ";
		cin >> polje[i];
	}
	
	//ispis polja prije
	cout << "--------------------------------------------" << endl;
	for (int i = 0; i < n; i++){
		cout << polje[i] << " ";
	}
	cout << endl;
	
	InsertionSort(polje, n);
	
	//ispis polja poslje
	cout << "--------------------------------------------" << endl;
	for (int i = 0; i < n; i++){
		cout << polje[i] << " ";
	}
	cout << endl;
	
}
