#include <iostream>
using namespace std;
#define V 5

bool NoviPovezani(bool graf[V][V], int put[V], int pozicija, int verteks){
	
	if (graf[ put[pozicija - 1] ][verteks] == 0){
		return false;
	} else {
		for (int i = 0; i < pozicija; i++){
			if (put[i] == verteks){
				return false;
			}
		}
	}
	return true;	
}

void ispis(int put[V]){
	cout << "     ";
	for (int i = 0; i < V; i++){
		cout << put[i] << " ";
	}
	cout << endl;
}

void HamiltonovKrug(bool graf[V][V], int put[V], int pozicija){
	if (pozicija == V){
		//veza zadnji prema prvom
		if (graf[ put[pozicija-1] ][ put[0] ] == 1) {
			ispis(put);
		}
	}
	
	for (int verteks = 1; verteks < V; verteks++){
		
		if (NoviPovezani(graf, put, pozicija, verteks)){
			
			put[pozicija] = verteks;
			HamiltonovKrug(graf, put, pozicija + 1);
			put[pozicija] = -1;
		}
	}
}

int main(){
	cout << "         Hamiltonov krug" << endl;
	cout << "--------------------------------" << endl;
	cout << " 1)  0---1---2  2)  0---1---2    " << endl;
	cout << "     |  / \\  |      |  / \\  |   " << endl;
	cout << "     | /   \\ |      | /   \\ |   " << endl;
	cout << "     |/     \\|      |/     \\|   " << endl;
	cout << "     3-------4      3       4    " << endl;
	cout << "--------------------------------" << endl;
	
	bool graf1[V][V] = {{0, 1, 0, 1, 0},
						{1, 0, 1, 1, 1},
						{0, 1, 0, 0, 1},
						{1, 1, 0, 0, 1},
						{0, 1, 1, 1, 0}};
	
	bool graf2[V][V] = {{0, 1, 0, 1, 0},
						{1, 0, 1, 1, 1},
						{0, 1, 0, 0, 1},
						{1, 1, 0, 0, 0},
						{0, 1, 1, 0, 0}};
	
	//inicijalizacija polja rješenja		
	int put[V];
	for (int i = 0; i < V; i++){
		put[i] = -1;
	}		
	
	put[0] = 0;
					  
	//Algoritam za raèunanje Ham. krugova
	HamiltonovKrug(graf1, put, 1);
	cout << "--------------------------------" << endl;
	return 0;
}
