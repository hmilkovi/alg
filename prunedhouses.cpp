// Backtracking example with pruning
//
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


int badQuestionNumber(int knownIncorrect, int conflicting1, int conflicting2)
{
  return min(knownIncorrect, max(conflicting1, conflicting2));
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


int checkSolution(const BackTrack& bt)
  // Check the state of bt to see if it represents a valid solution.
  // Return -1 if a solution. If not a solution, return the smallest
  // number of any problem variable known to be incorrect.
{
  int knownIncorrect = bt.numberOfVariables();

  // Implicit rule: each house is different
  if (bt[occupantOfHouse1] == bt[occupantOfHouse2])
    knownIncorrect = min(knownIncorrect,
			 max(occupantOfHouse1, occupantOfHouse2));
  if (bt[occupantOfHouse1] == bt[occupantOfHouse3])
    knownIncorrect = min(knownIncorrect,
			 max(occupantOfHouse1, occupantOfHouse3));
  if (bt[occupantOfHouse2] == bt[occupantOfHouse3])
    knownIncorrect = min(knownIncorrect,
			 max(occupantOfHouse2, occupantOfHouse3));

  if (bt[colorOfHouse1] == bt[colorOfHouse2])
    knownIncorrect = min(knownIncorrect,
			 max(colorOfHouse1, colorOfHouse2));
  if (bt[colorOfHouse1] == bt[colorOfHouse3])
    knownIncorrect = min(knownIncorrect,
			 max(colorOfHouse1, colorOfHouse3));
  if (bt[colorOfHouse2] == bt[colorOfHouse3])
    knownIncorrect = min(knownIncorrect,
			 max(colorOfHouse2, colorOfHouse3));

  if (bt[flowersAtHouse1] == bt[flowersAtHouse2])
    knownIncorrect = min(knownIncorrect,
			 max(flowersAtHouse1, flowersAtHouse2));
  if (bt[flowersAtHouse1] == bt[flowersAtHouse3])
    knownIncorrect = min(knownIncorrect,
			 max(flowersAtHouse1, flowersAtHouse3));
  if (bt[flowersAtHouse2] == bt[flowersAtHouse3])
    knownIncorrect = min(knownIncorrect,
			 max(flowersAtHouse2, flowersAtHouse3));

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
    knownIncorrect = min(knownIncorrect,
			 max(bobsHouse, greenHouse));
    

  // 2. Pat lives between Bob and Sue.
  if (bt[occupantOfHouse2] != pat)
    knownIncorrect = min(knownIncorrect, occupantOfHouse2);


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
    knownIncorrect = min(knownIncorrect,
			 max(suesHouse, daisiesHouse));
			

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
    knownIncorrect = min(knownIncorrect,
			 max(liliesHouse, blueHouse));
    

  // 5. The leftmost house has roses.
  if (bt[flowersAtHouse1] != roses)
    knownIncorrect = min(knownIncorrect, flowersAtHouse1);

  if (knownIncorrect >= bt.numberOfVariables())
    return -1;
  else
    return knownIncorrect;
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

      int pruneAt = checkSolution(problem);
      if (pruneAt < 0)
	solved = true;
      else
	problem.prune(pruneAt+1);
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
