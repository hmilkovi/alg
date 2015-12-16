// There are 3 adjacent houses, one red, one blue, and one green on Elm
// St. Each is occupied by a single
// person, and each has a garden with one kind of flower.
//
// 1. Bob does not live in the green house.
// 2. Pat lives between Bob and Sue.
// 3. Sue planted daisies.
// 4. Lilies are planted at the blue house.
// 5. The leftmost house has roses.
//
// List the colors of the houses, the occupants, and their flowers, from
// left to right.

#include <iostream>
#include "backtrack.h"

// Backtracking problems involve a list of "variables" each of which
// can take on some finite number of possible "values".
// Here, we lay out integer equivalents for this problem.

enum Questions {colorOfHouse1=0,
		colorOfHouse2=1, 
		colorOfHouse3=2, 
		flowersAtHouse1=3,
		flowersAtHouse2=4,
		flowersAtHouse3=5,
		occupantOfHouse1=6,
		occupantOfHouse2=7,
		occupantOfHouse3=8};

enum Colors {red=0, blue=1, green=2};
const char* colorNames[] = {"red", "blue", "green"};

enum Occupants {bob=0, pat=1, sue=2};
const char* occupantNames[] = {"Bob", "Pat", "Sue"};

enum Flowers {daisies=0, lilies=1, roses=2};
const char* flowerNames[] = {"daisies", "lilies", "roses"};


void describeHouse(int houseNumber,
		   Occupants occupant,
		   Colors c, Flowers f)
{
  cout << occupantNames[occupant] << " lives in house " << houseNumber
       << ", which is painted " << colorNames[c] << " and has "
       << flowerNames[f] << endl;
}



int indexOf (const BackTrack& bt, int value,
	     int candidate1, int candidate2, int candidate3)
{
  if (bt[candidate1] == value)
    return candidate1;
  else if (bt[candidate2] == value)
    return candidate2;
  else
    return candidate3;
}


bool checkSolution(const BackTrack& bt)
  // Check the state of bt to see if it represents a valid solution.
{
  bool OK = true;

  // Implicit rule: each house is different
  if (bt[occupantOfHouse1] == bt[occupantOfHouse2])
    OK = false;
  if (bt[occupantOfHouse1] == bt[occupantOfHouse3])
    OK = false;
  if (bt[occupantOfHouse2] == bt[occupantOfHouse3])
    OK = false;

  if (bt[colorOfHouse1] == bt[colorOfHouse2])
    OK = false;
  if (bt[colorOfHouse1] == bt[colorOfHouse3])
    OK = false;
  if (bt[colorOfHouse2] == bt[colorOfHouse3])
    OK = false;

  if (bt[flowersAtHouse1] == bt[flowersAtHouse2])
    OK = false;
  if (bt[flowersAtHouse1] == bt[flowersAtHouse3])
    OK = false;
  if (bt[flowersAtHouse2] == bt[flowersAtHouse3])
    OK = false;

  // 1. Bob does not live in the green house.
  int bobsHouse = indexOf(bt, bob,
			  occupantOfHouse1,
			  occupantOfHouse2,
			  occupantOfHouse3);
  int greenHouse = indexOf(bt, green,
			  colorOfHouse1,
			  colorOfHouse2,
			   colorOfHouse3);

  if (bobsHouse - occupantOfHouse1 == greenHouse - colorOfHouse1)
    OK = false;
    

  // 2. Pat lives between Bob and Sue.
  if (bt[occupantOfHouse2] != pat)
    OK = false;


  // 3. Sue planted daisies.
  int suesHouse = indexOf(bt, sue,
			  occupantOfHouse1,
			  occupantOfHouse2,
			  occupantOfHouse3);
  int daisiesHouse = indexOf(bt, daisies,
			     flowersAtHouse1,
			     flowersAtHouse2,
			     flowersAtHouse3);

  if (suesHouse - occupantOfHouse1 != daisiesHouse - flowersAtHouse1)
    OK = false;
			

  // 4. Lilies are planted at the blue house.
  int liliesHouse = indexOf(bt, lilies,
			    flowersAtHouse1,
			    flowersAtHouse2,
			    flowersAtHouse3);
  int blueHouse = indexOf(bt, blue,
			  colorOfHouse1,
			  colorOfHouse2,
			  colorOfHouse3);

  if (liliesHouse - flowersAtHouse1 != blueHouse - colorOfHouse1)
    OK = false;
    

  // 5. The leftmost house has roses.
  if (bt[flowersAtHouse1] != roses)
    OK = false;

  return OK;
}




int main()
{
  BackTrack problem(9, 3); // 9 questions, each with 3 possible answers
  bool solved = false;
  while ((!solved) && problem.more())
    {
      for (int i = 0; i < 9; ++i)
	cout << problem[i] << ' ';
      cout << endl;

      solved = checkSolution(problem);
      
      if (!solved)
	++problem;
    }

  if (solved)
    {
      describeHouse(1,
		    (Occupants)problem[occupantOfHouse1],
		    (Colors)problem[colorOfHouse1], 
		    (Flowers)problem[flowersAtHouse1]);
      describeHouse(2,
		    (Occupants)problem[occupantOfHouse2],
		    (Colors)problem[colorOfHouse2], 
		    (Flowers)problem[flowersAtHouse2]);
      describeHouse(3,
		    (Occupants)problem[occupantOfHouse3],
		    (Colors)problem[colorOfHouse3], 
		    (Flowers)problem[flowersAtHouse3]);
    }
  else
    cout << "Problem has no solution" << endl;
}
