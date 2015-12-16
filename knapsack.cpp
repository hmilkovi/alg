/*
Program:	Knapsack.cpp
Author:		Michael J. Sepcot
Purpose:	Testing various methods of solutions to the
			0/1 Knapsack problem with various file 
			sizes and correlation types.  
Date:		November 09, 2003
Class:		CS 430 - Illinois Institut of Technology
Professor:	Matthew Bauer
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <stdlib.h>
#include "apmatrix.h"
#include "timer.h"
using namespace std;

struct weights
{
	int price;				// Holds Item Price
	int weight;				// Holds Item Weight
	double ppw;				// Holds Item Price/Pound
};

struct Rtype
{
	int price;				// Holds Price
	int weight;				// Holds Weight
};

/* For Best First Branch and Bound */
struct node
{
	int level;				// Node Level
	int profit;				// Node Profit
	int weight;				// Node Weight
	float bound;			// Node Upper Bound
	/* External Operators For Comparison In Priority Queue */
	bool operator < (const node &right) const;
	bool operator == (const node &right) const;
};

// Node Less Than Comparison
bool node::operator < (const node &right) const
{
	if (bound < right.bound)
		return true;
	else
		return false;
}

// Node Equal To Comparison
bool node::operator == (const node &right) const
{
	if (bound == right.bound)
		return true;
	else
		return false;
}

/* Function Declaration */
// Sorting Scheme
void bubbleSort(int start, int finish, vector <weights> &list);

// Brute Force Functions
void BruteForce(vector <weights> list, int maxWeight);
void Combination(int &checked, vector <weights> list, int slot, Rtype &Optimal, 
				int cSize, int rCol, int loop, Rtype total, Rtype prevAdd, int maxWeight);

// Backtracking Functions
void Backtrack(vector <weights> list, int maxWeight);
void BT(int &count, vector <weights> list, Rtype &total, int index, 
		int maxWeight, Rtype &maxProfit);
bool promising(int index, vector <weights> list, int maxWeight, Rtype total);

// Best-First Branch and Bound Functions
void BranchBound(vector <weights> list, int maxWeight);
float bound(node test, int maxWeight, vector <weights> list, Rtype maxProfit);

// Dynamic Programming Functions
void Dynamic(vector <weights> list, int maxWeight, int n);

//*****************************************************************************************
void main()
{
	/**** Variable Declaration ****/
	int numItems,					// Total Number of Items
		corrType,					// Correlation Type
		maxWeight,					// Maximum Weight of Knapsack
		dummy;						// Hold for Unneeded Info
	int method = 0;					// Solution Method - Default No Solution
	string filename;				// Holds Name of Input File
	bool correct;					// Error Checking Variable
	ifstream infile;				// Location of Data
	vector <weights> list;			// List of Weights and Prices

	/**** Instructions ****/
	cout << "                    0/1 Knapsack                    " << endl;
	cout << "            Coded By:  Michael J. Sepcot            " << endl;
	cout << "****************************************************" << endl;
	cout << "**                  INSTRUCTIONS                  **" << endl;
	cout << "****************************************************" << endl;
	cout << "** This program examines four solutions to the    **" << endl;
	cout << "** 0/1 Knapsack problem.  Follow On-Screen        **" << endl;
	cout << "** instructions on selecting the number of items, **" << endl;
	cout << "** correlation type, and solution method.  This   **" << endl;
	cout << "** program includes test files generated with     **" << endl;
	cout << "** GENERATOR.c created by David Pisinger with     **" << endl;
	cout << "** values of n and t varying the same as the      **" << endl;
	cout << "** selections in this program and r, i, and S     **" << endl;
	cout << "** remaining constant (250, 325, and 1000).  This **" << endl;
	cout << "** program also accepts user input file names     **" << endl;
	cout << "** after list size is given.  Files must be in    **" << endl;
	cout << "** GENERATOR.c output format for acurate results. **" << endl;
	cout << "** The solution time is displayed along with the  **" << endl;
	cout << "** maximum profit and weight of the input.  Set   **" << endl;
	cout << "** number of items to 1234 to bypass list size    **" << endl;
	cout << "** restriction and enter in alternate value.      **" << endl;
	cout << "****************************************************" << endl;
	cout << "***          PRESS ENTER KEY TO CONTINUE         ***" << endl;
	cout << "****************************************************" << endl;
	
	cin.get();
	system("cls");

	cout << "*** 0/1 Knapsack ***" << endl;

	/**** Set Number of Items ****/
	cout << endl;
	cout << "Set Number of Items (10, 20, 40, 80, or 160): ";
	cin >> numItems;
	
	/* ERROR CHECK */
	correct = false;
	if (numItems == 10 || numItems == 20 || numItems == 40 ||
			numItems == 80 || numItems == 160 || numItems == 1234)
		correct = true;

	while (!correct)
	{
		cout << endl;
		cout << "***** ITEM SET ERROR *****" << endl;
		cout << "Please Select One of the Following Values For the Number of Itmes: ";
		cout << endl;
		cout << "10 .. 20 .. 40 .. 80 .. 160" << endl;
		cout << "Set the Number of ITEMS: ";
		cin >> numItems;
		if (numItems == 10 || numItems == 20 || numItems == 40 ||
				numItems == 80 || numItems == 160 || numItems == 1234)
			correct = true;
	}	

	if (numItems == 1234)
	{
		cout << endl;
		cout << "***** ITEM SET BYPASS *****" << endl;
		cout << "Enter Number of Items: ";
		cin >> numItems;
	}

	/**** Set the Correlation Type ****/
	cout << endl;
	cout << "Set the Correlation Type: " << endl;
	cout << "1. Uncorrelated" << endl;
	cout << "2. Weakly Correlated" << endl;
	cout << "3. Strongly Correlated" << endl;
	cout << "4. User Input File" << endl;
	cout << endl;
	cout << "Correlation Type: ";
	cin >> corrType;

	/* ERROR CHECK */
	correct = false;
	if (corrType == 1 || corrType == 2 || corrType == 3 || corrType == 4)
		correct = true;

	while (!correct)
	{
		cout << endl;
		cout << "***** CORRELATION ERROR *****" << endl;
		cout << "Please Select One of the Following Values For the Correlation Type:";
		cout << endl;
		cout << "1. Uncorrelated" << endl;
		cout << "2. Weakly Correlated" << endl;
		cout << "3. Strongly Correlated" << endl;
		cout << "4. User Input Filename" << endl;
		cout << endl;
		cout << "Correlation Type: ";
		cin >> corrType;
		if (corrType == 1 || corrType == 2 || corrType == 3 || corrType == 4)
			correct = true;
	}

	/**** Using numItems and corrType, Load the Approprate File ****/
	/*
		Files Labled as Follows: Two Character Correlation + numItems + .dat
		un: uncorrelated
		wk: weakly correlated
		st: strongly correlated
		numItems: 10, 20, 40, 80, or 160
	*/
	switch (corrType)
	{
		case 1:
			{
				if (numItems == 10)
					filename = "un10.dat";
				if (numItems == 20)
					filename = "un20.dat";
				if (numItems == 40)
					filename = "un40.dat";
				if (numItems == 80)
					filename = "un80.dat";
				if (numItems == 160)
					filename = "un160.dat";
			}
			break;
		case 2:
			{
				if (numItems == 10)
					filename = "wk10.dat";
				if (numItems == 20)
					filename = "wk20.dat";
				if (numItems == 40)
					filename = "wk40.dat";
				if (numItems == 80)
					filename = "wk80.dat";
				if (numItems == 160)
					filename = "wk160.dat";
			}
			break;
		case 3:
			{
				if (numItems == 10)
					filename = "st10.dat";
				if (numItems == 20)
					filename = "st20.dat";
				if (numItems == 40)
					filename = "st40.dat";
				if (numItems == 80)
					filename = "st80.dat";
				if (numItems == 160)
					filename = "st160.dat";
			}
			break;
		case 4:
			{
				cout << endl;
				cout << "***** USER INPUT FILE *****" << endl;
				cout << "Enter Filename (ie. filename.ext): ";
				cin >> filename;
			}
			break;
	}

	/**** Load File Into Memory ****/
	cout << endl;
	cout << "LOADING FILE... " << filename << " ";
	infile.open(filename.c_str());
	infile >> dummy;
	
	/* ERROR CHECK */
	/* Check Correctness of Current File */
	if (dummy != numItems)
	{
		cout << endl;
		cout << endl;
		cout << "***** READ ERROR *****" << endl;
		cout << "Number of Items Specified Does Not Match File" << endl;
		cout << "Results of Program Unreliable" << endl;
		cout << "Program Terminating..." << endl;
		correct = false;				// Do NOT Proceed to Execute Any More Commands
	}

	/* Proceed Loading File If File Passes Error Check */
	if (correct)
	{
		for (int lcv = 0; lcv < numItems; lcv++)
		{
			list.resize(list.size() + 1);	// Increase Vector Size By One
			infile >> dummy;				// Disregard Item Number
			infile >> list[lcv].price;		// Set Price
			infile >> list[lcv].weight;		// Set Weight
			list[lcv].ppw = double(list[lcv].price) / list[lcv].weight;	// Set Price/Pound
		}
		infile >> maxWeight;				// Set Maximum Weight of Knapsack
		infile.close();

		bubbleSort(0, list.size() - 1, list);	// Sort Items

		cout << " COMPLETE" << endl;

		/**** Set Solution Method ****/
		cout << endl;
		cout << "Select the Solution Method: " << endl;
		cout << "1. Brute Force" << endl;
		cout << "2. Backtracking" << endl;
		cout << "3. Best-First Branch and Bound" << endl;
		cout << "4. Dynamic Programming" << endl;
		cout << "Solution Method: ";
		cin >> method;
		correct = false;
		if (method == 1 || method == 2 || method == 3 || method == 4)
			correct = true;

		/* ERROR CHECK */
		while (!correct)
		{
			cout << endl;
			cout << "***** METHOD SELECTION ERROR *****" << endl;
			cout << "Please Select One of the Following Values For the Solution Mehtod:";
			cout << endl;
			cout << "1. Brute Force" << endl;
			cout << "2. Backtracking" << endl;
			cout << "3. Best-First Branch and Bound" << endl;
			cout << "4. Dynamic Programming" << endl;
			cout << "Solution Mehtod: ";
			cin >> method;
			if (method == 1 || method == 2 || method == 3 || method == 4)
				correct = true;
		}
	}

	/**** Branch Into Specific Solution Method Proceedures ****/
	if (method == 1)						// Brute Force
		BruteForce(list, maxWeight);
	if (method == 2)						// Backtracking
		Backtrack(list, maxWeight);
	if (method == 3)						// Best-First Branch and Bound
		BranchBound(list, maxWeight);
	if (method == 4)						// Dynamic Programming
		Dynamic(list, maxWeight, numItems);
}

//*****************************************************************************************
void BruteForce(vector <weights> list, int maxWeight)
{
	/* Variable Declaration and Initialization */
	Rtype total;				// Holds the Changing Total
	total.price = 0;
	total.weight = 0;

	Rtype prevAdd;				// Holds the Last Item Added to Total
	prevAdd.price = 0;
	prevAdd.weight = 0;
	
	Rtype Optimal;				// Holds the Solution to the Knapsack
	Optimal.price = 0;
	Optimal.weight = 0;
	
	Timer solutionTime;			// Times the Method

	int checked = 0;			// Holds Number of Combinations Explored

	solutionTime.start();		// Start Timing

	/* Find All Possible Combinations */
	for (int lcv = 0; lcv <= list.size(); lcv++)
	{
		Combination(checked, list, 0, Optimal, lcv, 0, (list.size() - lcv),
			total, prevAdd, maxWeight);
	}

	solutionTime.stop();	// Stop Timing

	// Output the Results
	cout << endl;
	cout << "Brute Force Approach On " << list.size() << " Items took: " 
		<< solutionTime.elapsedTime() << " Seconds" << endl;
	cout << "The Optimum Solution is: $" << Optimal.price << " and " << Optimal.weight 
		<< " pounds." << endl;
	cout << checked << " Explored Combinations - Values Greater Than "
		<< "Maximum Were Not Explored" << endl;
}

void Combination(int &checked, vector <weights> list, int slot, Rtype &Optimal, 
				int cSize, int rCol, int loop, Rtype total, Rtype prevAdd, int maxWeight)
{
	/* Set Local Variables */
	int lLoop = loop;
	int lslot = slot;

	// If Number of Slots Full, Check Against Best So Far
	if (rCol > (cSize - 1))
	{
		checked++;
		if (total.price > Optimal.price)
		{
			Optimal.price = total.price;	// Replace Best So Far With
			Optimal.weight = total.weight;	//		New Best
		}
		return;
	}

	// Prime the Loop
	total.price += prevAdd.price;
	total.weight += prevAdd.weight;

	for (int i = 0; i <= loop; ++i)
	{
		// Swap the Last Added Value With the Next Value to Try
		total.price = total.price + list[slot + i].price - prevAdd.price;
		total.weight = total.weight + list[slot + i].weight - prevAdd.weight;

		prevAdd.price = list[slot + i].price;		// Store Added Value For Swapping
		prevAdd.weight = list[slot + i].weight;		//		and Loop Priming

		++lslot;	// Increment Slot Location

		if (total.weight <= maxWeight)
		{
			Combination(checked, list, lslot, Optimal, cSize, rCol + 1, lLoop, 
				total, prevAdd, maxWeight);
		}
		--lLoop;	// Decrement the Local Loop to Avoid Repeated Values
	}
}

//*****************************************************************************************
void Backtrack(vector <weights> list, int maxWeight)
{
	/* Variable Declaration and Initialization */
	Rtype total;				// Hold Current Total
	total.price = 0;
	total.weight = 0;

	Rtype maxProfit;			// Hold Best So Far
	maxProfit.price = 0;
	maxProfit.weight = 0;

	int count = 0;				// Node Count
	int index = 0;				// Start at Root

	Timer solutionTime;			// Time the Method
	solutionTime.start();		// Start Timing

	BT(count, list, total, index, maxWeight, maxProfit);
	
	solutionTime.stop();		// Stop Timing

	// Output the Results
	cout << "Backtrack Approach On " << list.size() << " Items took: " 
		<< solutionTime.elapsedTime() << " Seconds" << endl;
	cout << "The Optimum Solution is: $" << maxProfit.price << " and " << maxProfit.weight 
		<< " pounds." << endl;
	cout << count << " Nodes Explored." << endl;
}

void BT(int &count, vector <weights> list, Rtype &total, int index, 
		int maxWeight, Rtype &maxProfit)
{
	count++;				// Increase Number of Nodes Looked At
	if (total.weight <= maxWeight && total.price >= maxProfit.price)
	{
		// Set maxProfit if a Bigger Profit is Found
		maxProfit.price = total.price;
		maxProfit.weight = total.weight;
	}

	// Explore Node if Promising
	if (promising(index, list, maxWeight, total))
	{
		Rtype newTotal;		// Inclusive Total
		newTotal.price = total.price + list[index].price;
		newTotal.weight = total.weight + list[index].weight;
		index++;
		BT(count, list, newTotal, index, maxWeight, maxProfit);	// Include Node
		BT(count, list, total, index, maxWeight, maxProfit);	// Exclude Node
	}
}

bool promising(int index, vector <weights> list, int maxWeight, Rtype total)
{
	int j;				// Index
	int totweight;		// Weight
	float bound;		// Upper Bound

	if (total.weight >= maxWeight)
		return false;	// Do NOT Expand to Children
	else
	{
		j = index + 1;

		bound = total.price;		// Set to Current
		totweight = total.weight;	// Set to Current
		while( j < list.size() && (totweight + list[j].weight) <= maxWeight)
		{
			totweight = totweight + list[j].weight;		// Add as Many Values As Possible
			bound = bound + list[j].price;				//		To Determine An Upper Bound
			j++;
		}

		// Use Fraction of Next Item to Determine Upper Bound if another Item Exists
		if (j < list.size())
			bound = bound + (maxWeight - totweight) * list[j].ppw;

		return (bound > total.price);
	}
}

//*****************************************************************************************
void BranchBound(vector <weights> list, int maxWeight)
{
	/* Variable Declaration and Initialization*/
	priority_queue <node> PQ;		// Priority Queue
	int count = 0;					// Count Number of Nodes Explored
	node u;							// Node of Item to Check
	
	node v;							// Node of Item to Check
	v.level = -1;					// Initialized to Root
	v.profit = 0;
	v.weight = 0;
	
	Rtype maxProfit;				// Holds Best So Far
	maxProfit.price = 0;
	maxProfit.weight = 0;
	
	Rtype total;					// Holds Current Data
	total.price = 0;
	total.weight = 0;

	Timer solutionTime;				// Time the Method
	solutionTime.start();			// Start Timing

	v.bound = bound(v, maxWeight, list, maxProfit);
	PQ.push(v);						// Place onto Queue
	while(!PQ.empty())
	{
		v = PQ.top();				// Set to Node With Best Bound
		PQ.pop();					// Remove Node From Queue
		count++;					// Increase Number of Nodes Explored
		if (v.bound > maxProfit.price)	// Check if Node is Still Promising
		{
			// Set u to Child Inclusive of Next Item
			u.level = v.level + 1;
			u.weight = v.weight + list[u.level].weight;
			u.profit = v.profit + list[u.level].price;
			if (u.weight <= maxWeight && u.profit > maxProfit.price)
			{
				// If New Best is Found, Replace Old Value
				maxProfit.price = u.profit;
				maxProfit.weight = u.weight;
			}
			// Check if Node is Still Promising
			u.bound = bound(u, maxWeight, list, maxProfit);
			if (u.bound > maxProfit.price)
				PQ.push(u);		// Put Item In Queue
			// Set u to Child Exclusive of Next Item
			u.weight = v.weight;
			u.profit = v.profit;
			u.bound = bound (u, maxWeight, list, maxProfit);
			if (u.bound > maxProfit.price)
				PQ.push(u);			// Put Item In Queue
		}
	}

	solutionTime.stop();			// Stop Timing

	// Output the Results
	cout << endl;
	cout << "Branch & Bound Approach On " << list.size() << " Items took: " 
		<< solutionTime.elapsedTime() << " Seconds" << endl;
	cout << "The Optimum Solution is: $" << maxProfit.price << " and " << maxProfit.weight 
		<< " pounds." << endl;
	cout << count << " Nodes Explored." << endl;
}

float bound(node test, int maxWeight, vector <weights> list, Rtype maxProfit)
{
	int j;			// Index
	int totweight;	// Weight
	float result;	// Upper Bound

	if (test.weight >= maxWeight)	// If Not Promising, Return 0
		return 0;
	else
	{
		j = test.level + 1;
		
		result = test.profit;		// Set to Current Node
		totweight = test.weight;
		
		while (j < list.size() && (totweight + list[j].weight) <= maxWeight)
		{
			totweight = totweight + list[j].weight;
			result = result + list[j].price;
			j++;
		}

		// Use Fraction of Next Item to Determine Upper Bound if another Item Exists
		if (j < list.size())
			result = result + (maxWeight - totweight) * list[j].ppw;
		return result;
	}
}

//*****************************************************************************************
void Dynamic(vector <weights> list, int maxWeight, int n)
{
	int i,					// Holds Row 
		j;					// Holds Column
	Rtype total;			// Holds Current Total
	total.price = 0;
	total.weight = 0;

	apmatrix <int> a(n + 1, maxWeight + 1);		// Matrix Holding Solutions
	apmatrix <int> k(n + 1, maxWeight + 1);		// Matrix Holding Items To Keep
	int solutions = 0;		// Holds Number of Unique Solutions Explored
	Timer solutionTime;		// Time the Method	
	solutionTime.start();	// Start Timing

	/* Set the Matrices */
	for (j = 0; j <= maxWeight; j++)
		a[0][j] = 0;				// No Item

	for (i = 1; i <= n; i++)
	{
		for (j = 0; j <= maxWeight; j++)
		{
			if (list[i - 1].weight <= j && 
					(list[i - 1].price + a[i - 1][j - list[i - 1].weight]) > a[i - 1][j])
			{
				// Compute Solution and Store in Matrix For Future Use
				solutions++;		// Increase Number of Solutions Explored
				a[i][j] = list[i - 1].price + a[i - 1][j - list[i - 1].weight];
				k[i][j] = 1;		// Identify Item as Keep
			}
			else
			{
				a[i][j] = a[i - 1][j];	// Reuse Solution
				k[i][j] = 0;		// Identify Item as NO Keep
			}
		}
	}
	
	/* Construct the Optimal Solution */
	int x = maxWeight;				// Start Checking From Last Location
	for (i = n; i > 0; i--)
	{
		if (k[i][x] == 1)
		{
			// If Keep, Add Item to Optimum Solution
			//		and Check loctation [i -1][Weight - Solution Weight]
			total.price += list[i - 1].price;
			total.weight += list[i - 1].weight;
			x = x - list[i - 1].weight;
		}
	}

	solutionTime.stop();	// Stop Timing

	// Output the Results
	cout << endl;
	cout << "Dynamic Programming On " << list.size() << " Items took: " 
		<< solutionTime.elapsedTime() << " Seconds" << endl;
	cout << "The Optimum Solution is: $" << total.price << " and " << total.weight 
		<< " pounds." << endl;
	cout << solutions << " Unique Solutions Explored." << endl;
}

//*****************************************************************************************
void bubbleSort(int start, int finish, vector <weights> &list)
{
	if (start == finish)	// If No Items To Be Sorted Return List
		return;
	else
	{
		bool swap = false;
		for (int lcv = start; lcv < finish; lcv++)
		{
			// Sort List In Decreasing Order
			if (list[lcv].ppw < list[lcv + 1].ppw)
			{
				/* Swap Items */
				weights temp;	// Temp Value Holder 

				temp.ppw = list[lcv].ppw; 
				temp.price = list[lcv].price;
				temp.weight = list[lcv].weight;

				list[lcv].ppw = list[lcv + 1].ppw;
				list[lcv].price = list[lcv + 1].price;
				list[lcv].weight = list[lcv + 1].weight;

				list[lcv + 1].ppw = temp.ppw;
				list[lcv + 1].price = temp.price;
				list[lcv + 1].weight = temp.weight;

				swap = true;
			}
		}
		if (!swap)			// If No Swaps Are Made List Is Sorted
			return;
		else
			bubbleSort(start, finish - 1, list);	// Last Item In Place, Sort Subset
	}
}