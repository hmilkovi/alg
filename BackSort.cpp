/* Exercise in bizarreness:  back-tracking sorting algorithm
 *
 * Sorting CAN be viewed as testing the permutations of the elements, selecting
 * the one that is in order.
 *
 * Back-tracking allows elimination of permutations whose front section fails.
 *
 * At a given position, the elements up to that position are in proper order.
 * For each possible value in this position, if that value is out-of-order
 * with respect to its predecessor, do not pursue further permutations with
 * this front end.  If it is NOT out-of-order, recursively process the next
 * position.
 */
#include <iostream.h>
#include <stdlib.h>
#include <time.h>

long nCmp = 0;

// Count number of integer comparisons as they are done.
int intcmp ( int x[], int posn )
{  nCmp++;  return x[posn-1] - x[posn];  }

// Test whether x[posn] is correctly positioned w.r.t. x[posn-1]
bool test ( int x[], int posn )
{  if (posn == 0) return true;    // true if there IS no predecessor
   else           return intcmp(x, posn) <= 0;
}

inline void swap ( int x[], int p, int q )
{  int tmp = x[p]; x[p] = x[q]; x[q] = tmp;  }

// NEARLY the world's WORST sorting algorithm:
//
// Examine all permutations of elements, but trim the permutations
// through backtracking.
bool backSort ( int x[], int size, int posn )
{//We have a solution if we've moved past the right end of x[]
   if ( posn == size )
      return true;
   else
   {  int tmp;     // Hold cell contents during rotation
      int k;       // Loop variable

      if ( test (x, posn) && backSort (x, size, posn+1) )
         return true;
      for ( k = posn+1; k < size; k++ )
      {  swap (x, k, posn);
         if ( test(x, posn) && backSort (x, size, posn+1) )
               return true;
      }
   // Regenerate the back of the array.  This is critical so that
   // when we backtrack, the proper value is in position to be used.
      tmp = x[posn];
      for ( k = posn+1; k < size; k++ )
         x[k-1] = x[k];
      x[size-1] = tmp;
   }
   return false;
}

// Completely randomize positions within x[] from [0] to [n-1]
void shuffle (int x[], int n)
{  while ( n > 1 )
   {  int k = rand() % n--;
      int temp;

      temp = x[k]; x[k] = x[n]; x[n] = temp;
   }
}

void main (void)
{  int *x;         // Array to be sorted
   int  size,      // Requested size for x
        k;         // Loop variable
   bool chk;       // Result from backSort
   long fact = 1;

   srand(time(NULL));   // Will use rand() in shuffle()

   cout << "Size:  ";
   cin  >> size;  cin.ignore(255, '\n');

   x = new int[size];
   for ( k = 0; k < size;  )
   {  x[k] = size - k;
      fact *= ++k;
   }

   cout << size << " gives " << fact << " possible sequences." << endl;

// Data are reversed by for loop above
   nCmp = 0;
   chk = backSort(x, size, 0);
   cout << "Reversed data." << endl;
   if ( !chk )
   {  cout << "Sorting failed" << endl;
      exit(-1);
   }
   for ( k = 0; k < size; k++ )
      cout << "  " << x[k];
   cout << " --- " << nCmp << " comparisons." << endl;

// Completely randomize the data
   shuffle (x, size);
   nCmp = 0;
   chk = backSort(x, size, 0);
   cout << "Random data." << endl;
   if ( !chk )
   {  cout << "Sorting failed" << endl;
      exit(-1);
   }
   for ( k = 0; k < size; k++ )
      cout << "  " << x[k];
   cout << " --- " << nCmp << " comparisons." << endl;

// Data left sorted from previous run.
   nCmp = 0;
   chk = backSort(x, size, 0);
   cout << "Sorted data." << endl;
   if ( !chk )
   {  cout << "Sorting failed" << endl;
      exit(-1);
   }

   for ( k = 0; k < size; k++ )
      cout << "  " << x[k];
   cout << " --- " << nCmp << " comparisons." << endl;

   cout << "Press <ENTER> to exit.  " << flush;
   cin.ignore(255, '\n');
}
/*  Specimen execution:

Size:  12
12 gives 479001600 possible sequences.
Reversed data.
  1  2  3  4  5  6  7  8  9  10  11  12 --- 24564 comparisons.
Random data.
  1  2  3  4  5  6  7  8  9  10  11  12 --- 3913 comparisons.
Sorted data.
  1  2  3  4  5  6  7  8  9  10  11  12 --- 11 comparisons.
*/
