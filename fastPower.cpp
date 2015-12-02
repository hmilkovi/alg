#include <iostream>

using namespace std;

int FastPower(int a, int power)        //the extra fast power calculation routine
{
if(power==1)               //if power equals 1 then return just a
return a;
else
{
int x=FastPower(a,power/2);        //else call the same routine, on the divded power by 2
if(power%2)                //if it is odd then return x*x*a
return x*x*a;
else                    //else if it is even then return x*x
return x*x;
}
}

int main()
{
cout<< FastPower(2,11) << endl;        //call the routine for the extra fast power
system ("pause");
}
