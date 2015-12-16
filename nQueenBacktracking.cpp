/***************************************************************************
 *   Copyright (C) 2008 by Jurica Seva   *
 *   jseva@foi.hr   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *									   *
 *	Backtracking algorithm applied to the N-Queens CSP.		   *
 *	Algorithm from _Foundations of Constraint Satisfaction_		   *
 *	by E. P. K. Tsang Chapter 2 page 37.  				   *
 ***************************************************************************/


#include <iomanip.h>
#include <iostream.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <vector>
using namespace std;

int constraintsViolated(vector<int> &Q) {
	int a, b, c = 0, i, j, n;
	
	n = Q.size();
	for (i = 0; i < n; i++) {
		a = Q[i];
		for (j = 0; j < n; j++) {
			b = Q[j];
			if (i != j && a != - 1 && b != - 1) {
				if (a == b) c++;
				if (i - j == a - b || i - j == b - a) c++;
			}
		}
	}
	return c;
}

bool Backtrack(vector<int> unlabelled, vector<int> compoundLabel,
	vector<int> &solution) {
	bool result;
	int i, j, v, x;
	vector<int> Dx(compoundLabel.size());

	if (unlabelled.empty()) {
		for (i = 0; i < compoundLabel.size(); i++)
			solution[i] = compoundLabel[i];
		return true;
	}
	for (i = 0; i < compoundLabel.size(); i++)
   		Dx[i] = i;
	// pick a random variable from unlabelled array
	i = rand() % unlabelled.size();
	x = unlabelled[i];
	do {
		// pick a random value from domain of x
		j = rand() % Dx.size();
		v = Dx[j];
		vector<int>::iterator vIterator = find(Dx.begin(), Dx.end(), v);
		Dx.erase(vIterator);
		compoundLabel[x] = v;
		if (constraintsViolated(compoundLabel) == 0) {
			vIterator = find(unlabelled.begin(), unlabelled.end(), x);
			unlabelled.erase(vIterator);
			result = Backtrack(unlabelled, compoundLabel, solution);
			if (result) return result;
			unlabelled.push_back(x);
		}
		else
			compoundLabel[x] = - 1;
	} while (!Dx.empty());
	return false;
}

void printSolution(vector<int> &solution) {
	char hyphen[256];
	int column, i, i4, n = solution.size(), row;

	if (n <= 10) {
		for (i = 0; i < n; i++) {
			i4 = i * 4;
			hyphen[i4 + 0] = '-';
			hyphen[i4 + 1] = '-';
			hyphen[i4 + 2] = '-';
			hyphen[i4 + 3] = '-';
		}
		i4 = i * 4;
		hyphen[i4 + 0] = '-';
		hyphen[i4 + 1] = '\n';
		hyphen[i4 + 2] = '\0';
		for (row = 0; row < n; row++) {
			column = solution[row];
			cout << hyphen;
			for (i = 0; i < column; i++)
				cout << "|   ";
			cout << "| Q ";
			for (i = column + 1; i < n; i++)
				cout << "|   ";
			cout << '|' << endl;
		}
		cout << hyphen;
	}
	else
		for (row = 0; row < n; row++)
			cout << row << ' ' << solution[row] << endl;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "usage: " << argv[0] << " numberOfQueens" << endl;
		exit(1);
	}
	int i, n = atoi(argv[1]);
	vector<int> compoundLabel(n, - 1), solution(n, - 1), unlabelled(n);
	for (i = 0; i < n; i++)
   		unlabelled[i] = i;
	srand(time(NULL));
	if (Backtrack(unlabelled, compoundLabel, solution))
		printSolution(solution);
	else
		cout << "problem has no solution" << endl;
	return 0;
}