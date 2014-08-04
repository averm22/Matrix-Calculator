/******************************************************************************
Title :Main.cpp
Author : Akansksha Verma
Submitted on : February 15, 2013
Description : implements the function TestMatrix to test the functions 
			  of class Matrix.h using the given TestMatrix()
Build with : make all using make file
modifications: none
******************************************************************************/
#include <iostream>
#include "Verma_Matrix.h"

using namespace std;

void TestingMatrix();


int main()
{

    TestingMatrix(); //function call 
    
	cout<<endl<<"End of Program"<<endl;
    return 0; 
}

void TestingMatrix(){
    Matrix<int> a, b, c; //Three empty matrices are created
    cout << a.numrows() << " " << a.numcols() << endl; // yields 0 0
	cin >> a; // User types [3 3 1 2 3 6 5 4 9 8 10]
    // This will create a 3 by 3 matrix
    // The first input is the number of rows, and the
    // second is the number of columns.
    // The rest are the values inserted row by row
    cout << a; // Output should be
    // [1 2 3
    // 6 5 4
    // 9 8 10]
    cin >> b; // User types [3 2 9 1 2 3 4 5]
    cout << b<<endl; // Output should be
    // [9 1
    // 2 3
    // 4 5]
    c=a*b; // c is the product of a and b
    cout << c << endl; // The output should be:
    // [25 22
    // 80 41
    // 137 83]
  cout << b+c << endl; // Output is the sum of b and c:
    // [34 23
    // 82 44
    // 141 88]
  Matrix<int>d(5*b); // d is initialized to 5*b
   cout << d << endl; //The output should be
    //[45 5
    // 10 15
    // 20 25]
  d += c;
  cout << d << endl; //The output should be
    //[70 27
    // 90 563 
    // 157 108]
    cout << a[0][0] << endl; //Should printout 1
    cout << a[1][2] << endl; //Should printout 4
    d = a + b; //This should cause an exception that you //are able to handle; The sizes of a and b don’t agree.
}//End of TestingMatrix() function

