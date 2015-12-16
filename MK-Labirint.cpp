#include <iostream>
#include <windows.h>
using namespace std;

int MAX = 1000;
int rjesenje = 1000;
char optimalni[10][10];
int br_rjesenja = 0;
int sve_ukupno = 0;

void Pozicija (short x, short y){
	COORD coord = {x, y};
	SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), coord);
}

Ispis(char labirint[10][10]){
	Pozicija(0, 0);
	cout << endl;
	for (int i = 0; i < 10; i++){
		cout << "  ";
		for (int j = 0; j < 10; j++){
			cout << labirint[i][j];
		}
		cout << endl;
	}
	cout << "--------------------------------------" << endl;
	cout << "Broj koraka: " << rjesenje << "    Br. rjesenja: " << br_rjesenja << "  " << endl;
	cout << "Sve: " << sve_ukupno << endl;
	cout << "--------------------------------------" << endl;
	Sleep(50);
}

void NajboljiDoSad(char labirint[10][10]){
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			optimalni[i][j] = labirint[i][j];
		}
	}
	Ispis(optimalni);
}

int PronadjiPut(char labirint[10][10], int x, int y, int brojac){
	//Ispis(labirint);
	brojac++;
	sve_ukupno++;
	if (labirint[x][y] == 'X'){
		br_rjesenja++;
		rjesenje = brojac;
		NajboljiDoSad(labirint);
		return brojac;
	}
	
	if (labirint[x][y] == '#' || labirint[x][y] == '.'){
		return MAX;
	}
	if (brojac > rjesenje){
		return MAX;
	}
	
	//Backtracking
	labirint[x][y] = '.';
	
	int novi_rezultat = MAX;
	
	//probaj ici desno/gore/lijevo/dolje
	novi_rezultat = PronadjiPut(labirint, x, y+1, brojac);
	novi_rezultat = PronadjiPut(labirint, x+1, y, brojac);
	novi_rezultat = PronadjiPut(labirint, x, y-1, brojac);
	novi_rezultat = PronadjiPut(labirint, x-1, y, brojac);

	labirint[x][y] = ' ';
	return MAX;	
}

int main(){

	cout << "--------------------------------------" << endl;
	cout << "  ##########                          " << endl;
	cout << "  #X  # #  #  Pronalazak              " << endl;
	cout << "  #   # # ##     puta u sakatom       " << endl;
	cout << "  #        #              labirintu!  " << endl;
	cout << "  #        #                          " << endl;
	cout << "  ###      #                          " << endl;
	cout << "  #    #####                          " << endl;
	cout << "  #     # ##               M.K.       " << endl;
	cout << "  #S#      #                          " << endl;
	cout << "  ##########                          " << endl;
	cout << "--------------------------------------" << endl;
	
	Sleep(2000);
	
	char labirint[10][10] ={
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
		{'#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', '#'},
		{'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}};
		
	//definiranje izlaza
	labirint[1][1] = 'X';
	//pronalazak puta
	PronadjiPut(labirint, 8, 8, 0);
	
	if (rjesenje != 1000){
		//ispis najbolje putanje
		Ispis(optimalni);
	} else {
		cout << "Nema rjesenja." << endl;
		cout << "--------------------------------------" << endl;
	}
	return 0;
}
