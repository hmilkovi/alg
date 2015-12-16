#include <iostream>
using namespace std;

#define N 4
int broj_opcija;

struct cvor{
	int donja_granica;
	int odabrani[N];
};

void Init (cvor &cvor){
	for (int i = 0; i < N; i++){
		cvor.odabrani[i] = 0;
	}
	cvor.donja_granica = 0;
}

cvor opcije[1000];

int DonjaGranica(cvor &cvor, int poslovi[N][N]){
	cvor.donja_granica = 0;
	for (int i = 0; i < N; i++){
		
		if (cvor.odabrani[i] != 0){
			cvor.donja_granica += poslovi[i][cvor.odabrani[i]-1];
		} else {
			int min = 1000;
			for (int j = 0; j < N; j++){
				int krivi_indeks = -1;
				for (int z = 0; z < i; z++){
					if (cvor.odabrani[z] == j + 1){
						krivi_indeks = j;
					}
				}
				if (poslovi[i][j] < min){
					if (j != krivi_indeks){
					min = poslovi[i][j];
					}
				}
			}
			cvor.donja_granica += min;
		}
	}
	cout << endl;
	return cvor.donja_granica;
}

int NajboljiKandidat(int poslovi[N][N]){
	int min = 1000;
	int indeks = -1;
	for (int i = 0; i < broj_opcija; i++){
		if (opcije[i].donja_granica < min){
			min = opcije[i].donja_granica;
			indeks = i;
		}
	}
	return indeks;
}

bool SviOdabrani(int indeks){
	for(int i = 0; i < N; i++){
		if (opcije[indeks].odabrani[i] == 0){
			return false;
		}
	}
	return true;
}

void Ispis(int indeks){
	for(int i = 0; i < N; i++){
		cout << opcije[indeks].odabrani[i] << " ";
	}
	cout << " = " << opcije[indeks].donja_granica;
}

void IspisCvora(cvor &cvor){
	cout << "Odabrani cvor: ";
	for (int i = 0; i < N; i++){
		cout << cvor.odabrani[i] << " ";
	}
	cout << "= " << cvor.donja_granica << endl;
}

void IspisOpcija(){
	cout << "-------- ISPIS OPCIJA --------" << endl;
	for (int i = 0; i < broj_opcija; i++){
		IspisCvora(opcije[i]);
	}
}

void GenerirajMogucnosti(int poslovi[N][N], int indeks){
	cvor obrisani = opcije[indeks];
	IspisCvora(obrisani);
	cout << "------------------------------" << endl;
	system("PAUSE");
	for (int i = indeks; i < broj_opcija; i++){
		opcije[i] = opcije[i + 1];
	}
	broj_opcija--;
	int propagiraj_ind;
	for (int i = 0; i < N; i++){
		if (obrisani.odabrani[i] == 0){
			propagiraj_ind = i;
			break;
		}
	}
	for (int i = 1; i <= N; i++){
		bool vec_postoji = false;
		for (int j = 0; j < propagiraj_ind; j++){
			if (i == obrisani.odabrani[j]){
				vec_postoji = true;
			}
		}
		if (!vec_postoji){
			cvor novi = obrisani;
			novi.odabrani[propagiraj_ind] = i;
			novi.donja_granica = DonjaGranica(novi, poslovi);
			opcije[broj_opcija] = novi;
			broj_opcija++;
		}
	}
	
}

void Brencaj_i_boundaj (int poslovi[N][N]){
	int najbolji_indeks = NajboljiKandidat(poslovi);
	cout << "------------------------------" << endl;
	cout << "Najbolji kandidat: " << najbolji_indeks << endl;

	if (SviOdabrani(najbolji_indeks)){
		Ispis(najbolji_indeks);
		return;
	} else {
		GenerirajMogucnosti(poslovi, najbolji_indeks);
	}
	system("CLS");
	IspisOpcija();
	Brencaj_i_boundaj(poslovi);
}


int main(){
	
	cout << "------------------------------------------------------" << endl;
	cout << "               B & B - Podjela poslova                " << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "                      9 2 7 8                         " << endl;
	cout << "                      6 4 3 7                         " << endl;
	cout << "                      5 8 1 8                         " << endl;
	cout << "                      7 6 9 4                         " << endl;
	cout << "------------------------------------------------------" << endl;
	
	int poslovi[N][N] = {{9, 2, 7, 8},
	                     {6, 4, 3, 7},
	                     {5, 8, 1, 8},
	                     {7, 6, 9, 4}};
	                     
	cvor korjen;
	Init (korjen);
	opcije[0] = korjen;
	broj_opcija = 1;
	cout << "Teoretska donja granica: " << DonjaGranica(opcije[0], poslovi) << endl;
	cout << "------------------------------------------------------" << endl;
	
	Brencaj_i_boundaj(poslovi);
	
	return 0;
}
