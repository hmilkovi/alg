#include <iostream>
using namespace std;

#define N 4
int br_opcija;
int kapacitet;

struct stvar{
	int velicina;
	int vrijednost;
	int odnos;
};

struct cvor{
	int gg;
	int velicina;
	int vrijednost;
	int razina;
	int odabrani[N];
};

cvor opcije[100];

void Init(cvor &cvor){
	cvor.gg = 0;
	cvor.velicina = 0;
	cvor.vrijednost = 0;
	cvor.razina = 0;
	for (int i = 0; i < N; i++){
		cvor.odabrani[i] = 0;
	}
}

void Ispis(stvar stvari[N]){
	cout << "--------------------------------------" << endl;
	for (int i = 0; i < N; i++){
		cout << i + 1 << ". stvar ";
		cout << stvari[i].velicina << " " << stvari[i].vrijednost << " ";
		cout << stvari[i].odnos << endl;
	}
	cout << "--------------------------------------" << endl;
}

void IspisRjesenje(int indeks){
	cout << "------------- RJESENJE ---------------" << endl << endl;
	for (int i = 0; i < N; i++){
		cout << opcije[indeks].odabrani[i] << " ";
	}
	cout << "GG: " << opcije[indeks].gg << " Vel: " << opcije[indeks].velicina;
	cout << " Vr: " << opcije[indeks].vrijednost << " Raz: " << opcije[indeks].razina << endl;
}

void IspisOpcija(){
	for (int i = 0; i < br_opcija; i++){
		for (int j = 0; j < N; j++){
			cout << opcije[i].odabrani[j] << " ";
		}
		cout << "GG: " << opcije[i].gg << " Vel: " << opcije[i].velicina;
		cout << " Vr: " << opcije[i].vrijednost << " Raz: " << opcije[i].razina << endl;
	}
}

int GornjaGranica(cvor &cvor, stvar stvari[N]){
	cvor.gg = cvor.vrijednost + (kapacitet - cvor.velicina) * (stvari[cvor.razina].odnos);
	if (cvor.razina == N) cvor.gg = cvor.vrijednost;
	return cvor.gg;
}

int NajboljiKandidat(stvar stvari[N]){
	int indeks = -1;
	int max = 0;
	for (int i = 0; i < br_opcija; i++){
		if (opcije[i].gg > max){
			indeks = i;
			max = opcije[i].gg;
		}
	}
	return indeks;
}

void IspisCvora (cvor &cvor){
	for (int i = 0; i < N; i++){
		cout << cvor.odabrani[i] << " ";
	}
	cout << cvor.gg << " " << cvor.velicina << " " << cvor.vrijednost << " " << cvor.razina << endl;
}

void GenerirajMogucnosti(stvar stvari[N], int indeks){
	cvor obrisani = opcije[indeks];
	cout << "Brisem cvor: ";
	IspisCvora(obrisani);
	cout << "--------------------------------------" << endl;
	for (int i = indeks; i < br_opcija; i++){
		opcije[i] = opcije[i+1];
	}
	br_opcija--;
	cvor sa_sljedecim = obrisani;
	sa_sljedecim.velicina += stvari[sa_sljedecim.razina].velicina;
	sa_sljedecim.vrijednost += stvari[sa_sljedecim.razina].vrijednost;
	sa_sljedecim.odabrani[sa_sljedecim.razina] = 1;
	sa_sljedecim.razina = obrisani.razina + 1;
	sa_sljedecim.gg = GornjaGranica(sa_sljedecim, stvari);
	if (sa_sljedecim.velicina <= kapacitet){
		opcije[br_opcija] = sa_sljedecim;
		br_opcija++;
	} else {
		cout << "Premasen kapacitet: ";
		IspisCvora(sa_sljedecim);
		cout << "--------------------------------------" << endl;
	}
	
	cvor bez_sljedeceg = obrisani;
	bez_sljedeceg.razina = obrisani.razina + 1;
	bez_sljedeceg.gg = GornjaGranica(bez_sljedeceg, stvari);
	opcije[br_opcija] = bez_sljedeceg;
	br_opcija++;
}

void Brencaj_i_boundaj(stvar stvari[N]){
	int najbolji_indeks = NajboljiKandidat(stvari);
	cout << "--------------------------------------" << endl;
	cout << "Najbolji kandidat - indeks: " << najbolji_indeks << endl;
	cout << "--------------------------------------" << endl;
	system("PAUSE");
	system("CLS");
	if(opcije[najbolji_indeks].razina == N){
		IspisRjesenje(najbolji_indeks);
		return;
	} else {
		GenerirajMogucnosti(stvari, najbolji_indeks);
	}
	IspisOpcija();
	Brencaj_i_boundaj(stvari);
}

int main(){
	cout << "------------------------------------------------------" << endl;
	cout << "               B & B - Problem (v)ranca           M.K." << endl;
	cout << "------------------------------------------------------" << endl;
	
	stvar stvari[N];
	
	for(int i = 0; i < N; i++){
		stvar pomocni;
		cout << i + 1 << ". stvar" << endl;
		cout << "Velicina: ";
		cin >> pomocni.velicina;
		cout << "Vrijednost: ";
		cin >> pomocni.vrijednost;
		pomocni.odnos = pomocni.vrijednost/pomocni.velicina;
		int j = i - 1;
		while (j >= 0 && stvari[j].odnos < pomocni.odnos){
			stvari[j+1].velicina = stvari[j].velicina;
			stvari[j+1].vrijednost = stvari[j].vrijednost;
			stvari[j+1].odnos = stvari[j].odnos;
			j--;
		}
		stvari[j+1].velicina = pomocni.velicina;
		stvari[j+1].vrijednost = pomocni.vrijednost;
		stvari[j+1].odnos = pomocni.odnos;
		cout << "--------------------------------------" << endl;
	}
	cout << "Kapacitet ranca? ";
	cin >> kapacitet;
	
	Ispis(stvari);	
	
	cvor korjen;
	Init(korjen);
	opcije[0] = korjen;
	br_opcija = 1;
	cout << "Teoretska gornja granica: " << GornjaGranica(opcije[0], stvari) << endl;
	Brencaj_i_boundaj(stvari);
    Ispis(stvari);	
	system("PAUSE");
	return 0;
}
