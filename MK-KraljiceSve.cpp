#include <iostream>
#define N 6
//BROJ RJEŠENJA ZA VELIÈINE:
//1=1, 2=0, 3=0, 4=2, 5=10, 6=4, 7=40, 8=92

using namespace std;
int brojac = 0;
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

void ispis(int polje[N][N]){
	for (int i=0; i<N; i++){
			for (int j=0; j<N; j++){
				cout << polje[i][j] << " ";
			}
			cout << endl;
		}
}

void UbaciKraljice(int polje[N][N], int kolona){
	if (kolona == N){
		ispis(polje);
		brojac++;
		cout << "---------------------" << endl;
	}
	for (int i = 0; i<N; i++){
		if(Slobodno(polje, i, kolona)){
			polje[i][kolona] = 1;
			UbaciKraljice(polje, kolona+1);
			polje[i][kolona] = 0;
		}
	}
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
	
	UbaciKraljice(polje, 0);
	cout << "Brojac: "<< brojac;
	return 0;
}
