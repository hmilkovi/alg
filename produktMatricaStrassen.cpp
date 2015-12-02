 /*************************************************************************/
 /*************************************************************************/
 //---------------------------  Header Files  ----------------------------//
 /*************************************************************************/
 /*************************************************************************/

 #include <iostream.h>
 #include <conio.h>
 #include <stdlib.h>
 #include <windows.h>
 #include <process.h>

 /*************************************************************************/
 /*************************************************************************/
 //------------------------  Global Variabbles  --------------------------//
 /*************************************************************************/
 /*************************************************************************/

 int matrix_A[4][4]={0};
 int matrix_B[4][4]={0};
 int matrix_C[4][4]={0};

 /*************************************************************************/
 /*************************************************************************/
 //------------------------  Function Prototypes  ------------------------//
 /*************************************************************************/
 /*************************************************************************/

 void gotoxy(int, int); // prototype
 void clrscr(); // prototype
 void get_matrix_A( );
 void get_matrix_B( );
 void multiply_matrices( );
 void show_matrix_C( );

 void add_2x2_matrices(const int [2][2],const int [2][2],int [2][2]);
 void subtract_2x2_matrices(const int [2][2],const int [2][2],int [2][2]);
 void multiply_2x2_matrices(const int [2][2],const int [2][2],int [2][2]);

 /*************************************************************************/
 /*************************************************************************/
 //-----------------------------  main( )  -------------------------------//
 /*************************************************************************/
 /*************************************************************************/

 int main( )
 {
    clrscr( );
    //textmode(C4350);

    get_matrix_A( );
    get_matrix_B( );
    multiply_matrices( );
    show_matrix_C( );

    cout<<"\n\n\n\n\n Press any key to exit...";

    getch( );
    return 0;
 }

 /*************************************************************************/
 /*************************************************************************/
 //------------------------  Function Definitions  -----------------------//
 /*************************************************************************/
 /*************************************************************************/

 /***********************************************************************/
 //--------------------------  get_matrix_A( )  ------------------------//
 /***********************************************************************/

 void get_matrix_A( )
 {
    gotoxy(1,2);
    cout<<" Enter the values of Matrix-A row by row :\n "<<endl;

    cout<<"\t\t\t �                     �"<<endl;
    cout<<"\t\t\t �                     �"<<endl;
    cout<<"\t\t\t �                     �"<<endl;
    cout<<"\t\t\t �                     �"<<endl;
    cout<<"\t\t\t �                     �"<<endl;
    cout<<"\t\t\t �                     �"<<endl;

    gotoxy(18,6);
    cout<<" A  = "<<endl;

    int x=28;
    int y=5;

    for(int i=0;i<4;i++)
    {
       for(int j=0;j<4;j++)
       {
	  gotoxy(x,y);
	  cin>>matrix_A[i][j];

	  x+=5;
       }

       x=28;
       y++;
    }
 }

 /***********************************************************************/
 //-------------------------  get_matrix_B( )  -------------------------//
 /***********************************************************************/

 void get_matrix_B( )
 {
    gotoxy(1,15);
    cout<<" Enter the values of Matrix-B row by row :\n "<<endl;

    cout<<"\t\t\t �                     �"<<endl;
    cout<<"\t\t\t �                     �"<<endl;
    cout<<"\t\t\t �                     �"<<endl;
    cout<<"\t\t\t �                     �"<<endl;
    cout<<"\t\t\t �                     �"<<endl;
    cout<<"\t\t\t �                     �"<<endl;

    gotoxy(18,19);
    cout<<" B  = "<<endl;

    int x=28;
    int y=18;

    for(int i=0;i<4;i++)
    {
       for(int j=0;j<4;j++)
       {
	  gotoxy(x,y);
	  cin>>matrix_B[i][j];

	  x+=5;
       }

       x=28;
       y++;
    }
 }

 /*************************************************************************/
 //------------------------  add_2x2_matrices( )  ------------------------//
 /*************************************************************************/

 void add_2x2_matrices(const int a[2][2],const int b[2][2],int c[2][2])
 {
    for(int i=0;i<2;i++)
    {
       for(int j=0;j<2;j++)
	  c[i][j]=(a[i][j]+b[i][j]);
    }
 }

 /*************************************************************************/
 //-----------------------  subtract_2x2_matrices( )  --------------------//
 /*************************************************************************/

 void subtract_2x2_matrices(const int a[2][2],const int b[2][2],int c[2][2])
 {
    for(int i=0;i<2;i++)
    {
       for(int j=0;j<2;j++)
	  c[i][j]=(a[i][j]-b[i][j]);
    }
 }

 /*************************************************************************/
 //----------------------  multiply_2x2_matrices( )  ---------------------//
 /*************************************************************************/

 void multiply_2x2_matrices(const int a[2][2],const int b[2][2],int c[2][2])
 {
    for(int i=0;i<2;i++)
    {
       for(int j=0;j<2;j++)
       {
	  c[i][j]=0;

	  for(int k=0;k<2;k++)
	     c[i][j]+=(a[j][k]*b[k][j]);
       }
    }
 }

 /*************************************************************************/
 //-----------------------  multiply_matrices( )  ------------------------//
 /*************************************************************************/

 void multiply_matrices( )
 {
    int A11[2][2]={0};
    int A12[2][2]={0};
    int A21[2][2]={0};
    int A22[2][2]={0};

    int B11[2][2]={0};
    int B12[2][2]={0};
    int B21[2][2]={0};
    int B22[2][2]={0};

    int C11[2][2]={0};
    int C12[2][2]={0};
    int C21[2][2]={0};
    int C22[2][2]={0};

    int i;
    int j;

    for(i=0;i<2;i++)
    {
       for(j=0;j<2;j++)
       {
	  A11[i][j]=matrix_A[i][j];
	  B11[i][j]=matrix_B[i][j];
       }
    }

    for(i=0;i<2;i++)
    {
       for(j=2;j<4;j++)
       {
	  A12[i][(j-2)]=matrix_A[i][j];
	  B12[i][(j-2)]=matrix_B[i][j];
       }
    }

    for(i=2;i<4;i++)
    {
       for(j=0;j<2;j++)
       {
	  A21[(i-2)][j]=matrix_A[i][j];
	  B21[(i-2)][j]=matrix_B[i][j];
       }
    }

    for(i=2;i<4;i++)
    {
       for(j=2;j<4;j++)
       {
	  A22[(i-2)][(j-2)]=matrix_A[i][j];
	  B22[(i-2)][(j-2)]=matrix_B[i][j];
       }
    }

    int M1[2][2]={0};
    int M2[2][2]={0};
    int M3[2][2]={0};
    int M4[2][2]={0};
    int M5[2][2]={0};
    int M6[2][2]={0};
    int M7[2][2]={0};

    int Temp1[2][2]={0};
    int Temp2[2][2]={0};

    subtract_2x2_matrices(A12,A22,Temp1);
    add_2x2_matrices(B21,B22,Temp2);
    multiply_2x2_matrices(Temp1,Temp2,M1);

    add_2x2_matrices(A11,A22,Temp1);
    add_2x2_matrices(B11,B22,Temp2);
    multiply_2x2_matrices(Temp1,Temp2,M2);

    subtract_2x2_matrices(A11,A21,Temp1);
    add_2x2_matrices(B11,B12,Temp2);
    multiply_2x2_matrices(Temp1,Temp2,M3);

    add_2x2_matrices(A11,A12,Temp1);
    multiply_2x2_matrices(Temp1,B22,M4);

    subtract_2x2_matrices(B12,B22,Temp1);
    multiply_2x2_matrices(Temp1,A11,M5);

    subtract_2x2_matrices(B21,B11,Temp1);
    multiply_2x2_matrices(Temp1,A22,M6);

    add_2x2_matrices(A21,A22,Temp1);
    multiply_2x2_matrices(Temp1,B11,M7);

    add_2x2_matrices(M1,M6,Temp1);
    subtract_2x2_matrices(M2,M4,Temp2);
    add_2x2_matrices(Temp1,Temp2,C11);

    add_2x2_matrices(M4,M5,C12);

    add_2x2_matrices(M6,M7,C21);

    subtract_2x2_matrices(M2,M3,Temp1);
    subtract_2x2_matrices(M5,M7,Temp2);
    add_2x2_matrices(Temp1,Temp2,C22);

    for(i=0;i<2;i++)
    {
       for(j=0;j<2;j++)
	  matrix_C[i][j]=C11[i][j];
    }

    for(i=0;i<2;i++)
    {
       for(j=2;j<4;j++)
	  matrix_C[i][j]=C12[i][(j-2)];
    }

    for(i=2;i<4;i++)
    {
       for(j=0;j<2;j++)
	  matrix_C[i][j]=C21[(i-2)][j];
    }

    for(i=2;i<4;i++)
    {
       for(j=2;j<4;j++)
	  matrix_C[i][j]=C22[(i-2)][(j-2)];
    }
 }

 /***********************************************************************/
 //------------------------  show_matrix_C( )  -------------------------//
 /***********************************************************************/

 void show_matrix_C( )
 {
    gotoxy(1,28);
    cout<<" Values of Matrix-C row by row :\n "<<endl;

    cout<<"\t\t\t �                     �"<<endl;
    cout<<"\t\t\t �                     �"<<endl;
    cout<<"\t\t\t �                     �"<<endl;
    cout<<"\t\t\t �                     �"<<endl;
    cout<<"\t\t\t �                     �"<<endl;
    cout<<"\t\t\t �                     �"<<endl;

    gotoxy(18,32);
    cout<<" C  = "<<endl;

    int x=28;
    int y=31;

    for(int i=0;i<4;i++)
    {
       for(int j=0;j<4;j++)
       {
	  gotoxy(x,y);
	  cout<<matrix_C[i][j];

	  x+=5;
       }

       x=28;
       y++;
    }
 }
 
 /***********************************************************************/
 //------------------------  gotoxy()  ---------------------------------//
 /***********************************************************************/
 
    void gotoxy(int x, int y)
    {
        HANDLE hConsoleOutput;
        COORD dwCursorPosition;
        cout.flush();
        dwCursorPosition.X = x;
        dwCursorPosition.Y = y;
        hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
    }

 /***********************************************************************/
 //------------------------  clrscr() ----------------------------------//
 /***********************************************************************/
 
    void clrscr()
    {
         system("cls");
    }

 /*************************************************************************/
 /*************************************************************************/
 //-----------------------------  End of File  ---------------------------//
 /*************************************************************************/
 /*************************************************************************/
