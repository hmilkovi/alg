#include <iostream>
#define N 4
using namespace std;

bool Slobodno(int polje[N][N], int stupac, int kolona){
	//ravno gore
	for (int x = 0; x < kolona; x++){
		if (polje[stupac][x]){
			return false;
		}
	}
	//dijagonala lijevo
	int x = stupac - 1;
	int y = kolona - 1;
	while ((x >= 0) && (y >= 0)){
		if (polje[x][y]){
			return false;
		} else {
			x--;
			y--;
		}
	}
	//dijagonala desno
	x = stupac + 1;
	y = kolona - 1;
	while ((x < N) && (y >= 0)){
		if (polje[x][y]){
			return false;
		} else {
			x++;
			y--;
		}
	}
	return true;	
}

void Ispis (int polje[N][N]){
	cout << "-------------------" << endl;
	for (int i=0; i<N; i++){
			for (int j=0; j<N; j++){
				cout << polje[i][j] << " ";
			}
			cout << endl;
		}
}

bool UbaciKraljice(int polje[N][N], int kolona){
	if (kolona == N){
		return true;
	}
	for (int i = 0; i<N; i++){
		if(Slobodno(polje, i, kolona)){
			polje[i][kolona] = 1;
			
			Ispis(polje);
			
			if (UbaciKraljice(polje, kolona+1)){
				return true;
			}
			
			polje[i][kolona] = 0;
		}
	}
	return false;
}

int main(){
	
	int polje[N][N];
	
	cout << "    Probljemus - N kraljica " << endl;
	cout << "------------------------------------" << endl;
	
	//inicijalizacija polja, nule
	for (int i=0; i<N; i++){
		for (int j=0; j<N; j++){
			polje[i][j] = 0;
		}
	}
	
	if(UbaciKraljice(polje, 0)){
		//ispis
		cout << "-------------------" << endl;
		for (int i=0; i<N; i++){
			for (int j=0; j<N; j++){
				cout << polje[i][j] << " ";
			}
			cout << endl;
		}
	} else {
		cout << "Nema rjesenja... :P" << endl;
	}	
	return 0;
}
