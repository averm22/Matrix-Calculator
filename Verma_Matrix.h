/******************************************************************************
Title : Matrix.h
Author : Akansksha Verma
Submitted on : February 15, 2013
Description : header file with Matrix class that complements the test class in main
			 contains overload operators as friend functions of class Matrix
Build with : make all using make file
******************************************************************************/
#ifndef __Matrices__Matrix__
#define __Matrices__Matrix__

#include <iostream>
#include <cstdlib>
using namespace std;

template <typename T>
class Matrix {
    
public:
    
    Matrix(){
        Columns=Rows=0; //default Constructor initializes columns and rows to 0 
         };
    
    void allocarray(int rows,int cols){ //creates the array and allocates memory
        Rows=rows;
        Columns=cols;
        
        Data =new T*[Rows];	 //creats a new pointer for each row
        
        for ( int i = 0; i < Rows; ++i)
        {
            Data[i] = new T[Columns];	//creates a new column in memory against each row
        }
      
    };
   
    
    Matrix(int rows,int cols){ // Constructor takes in parameters to allocate Matrix with specifics
        int Columns = cols;
        int Rows = rows;
       
        if(Rows>0 && Columns>0){
            allocarray(Rows,Columns);
        }  
    };
    
    ~Matrix(){  //destructor
     
       if(Rows>0 && Columns>0 && Data == 0){
        for (int i=0;i<Rows; i++) {
                delete [] Data[i];		//deletes the Data first
            }
             delete [] Data;	//deletes the final pointer to the Data
        }

    };
    
  Matrix(const Matrix &another){ //copy constructor
      Data=another.Data;
      Rows = another.Rows;
      Columns = another.Columns;
      
      for(int i = 0; i < Rows;i++){
            for (int k=0 ; k<Columns;k++){
                Data[i][k]=another.Data[i][k];	//copies the current referenced matrix to the new one
            }
        }
    };
    
    int numrows(){   //accessor function returns Rows
        return Rows;
    };
    
    int numcols(){  //accessor function returns Columns
        return Columns;
    };
    
//overloaded "()" operator
    Matrix<T> operator ()(const Matrix<T> other, Matrix<T> another){    
        
        other(another); //copies one matrix onto the other
    }
    
//overloaded array subscript " []" operator for "[][]" accesses the data of the 2d Matrix
 	 T* operator[](int num){
	return Data[num];	//return the data for the given num	
};
    
    //overloading output"<<" operator friends function declaration
template<typename U>
  friend ostream& operator<< (ostream &output,const Matrix<U> &other);
    
    
    //overloading input ">> "operator friend function declaration
template<typename U>
  friend istream& operator>>(istream &input, Matrix<U> &other);
   
    //overloading Multiplication "*" operator friend function declarations
template<typename U>
    friend const Matrix<U> operator*(const Matrix<U>& first,const Matrix<U>& second);
    
    //overloading Addition "+" operator friend function declaration
template<typename U>
    friend Matrix<U> operator +(const Matrix<U>& first, const Matrix<U>& second);

    //overloading unary addition "+=" operator friend function declaration
template<typename U>
    friend Matrix<U> operator+=(const Matrix<U>& other,const Matrix<U>& other2);
    
    //overloading Scalar Multiplication "*" operator (int * matrix) friend function declaration
template<typename U>
    friend Matrix<U> operator*(U num, const Matrix<U> other);
    
  
private:            //private Data members Matrix Class
    int Columns;
    int Rows;
    T** Data;
};



//implementation of Friend function operator >>
template <typename T>
 istream& operator>>(istream &input, Matrix<T> &other){
    
     char temp[2];	//takes in the "[ ]" characters and ignored
     input>>temp[1]>>other.Rows>>other.Columns;	//assigns rows and columns to the matrix
     other.allocarray(other.Rows,other.Columns); //allocates memory for the new matrix
    
	 for(int i=0;i<other.Rows;i++){		//for loop to input each value into the matrix
         for(int k=0;k<other.Columns;k++){
             input>>other.Data[i][k];
         }
    }
     input>>temp[2]; //inputs the last "]" char entered and is ignored
     
      return input;	
}

//definition for Friend function output operator "<<" 
template<typename T>
ostream& operator<<(ostream &output,const Matrix<T> &other){
	
    if(other.Data != 0)//outputs if matrix is not empty
    cout<<"[";
	for(int i=0;i<other.Rows;i++){
		for(int c=0;c<other.Columns;c++){
			cout<<" "<<other.Data[i][c]<<" ";//using a for loop outputs each value by accessing each data of matrix
        }
        
        if(i == other.Rows -1){				//formatting for the output within "[]"
			cout<<"]";
        }
		else
			cout<<endl;
      }
    	cout<<endl;
 
    return output;
    }

//definition Multiplication "*" operator friend function
template<typename T>
const Matrix<T> operator*(const Matrix<T>& first, const Matrix<T>& second){
       
       Matrix<T> answer(first.Rows,second.Columns);
       T Sum;
    
       for(int r=0;r < answer.Rows;r++){
           for(int c=0;c<answer.Columns;c++){
               Sum=0;
               for(int k=0;k<first.Columns;k++){
                   Sum += first.Data[r][k]*second.Data[k][c];
               }
               answer.Data[r][c]=Sum;
           }
       }
       return answer;
    }
    

//definition of  Addition "+" operator friend function of class Matrix
template<typename T>
Matrix<T> operator +(const Matrix<T>& first,const Matrix<T>& second){
       
        if(first.Rows != second.Rows || first.Columns != second.Columns){
		
         try{
                throw 20;   // throwing an exception if the matrix are not equal in rows and Columns
            }
            catch(int e){
                cout<<"An exception occured.Matrix do not match"<<endl;
            }
        }
    
        Matrix<T> answer(first.Rows,first.Columns);
        
        for(int r=0;r<answer.Rows;r++){
            for(int c=0;c<answer.Columns;c++){
               
                answer.Data[r][c]=first.Data[r][c]+second.Data[r][c];	//adding operation
            }
        }
        return answer;
    }
   
 
//definition of unary addition "+=" operator friend function of class Matrix
template<typename T>
Matrix<T> operator+=(const Matrix<T>& other,const Matrix<T>& other2){
        for(int r=0;r<other.Rows;r++){
            for(int c=0;c<other.Columns;c++){
                other.Data[r][c]=other.Data[r][c]+other2.Data[r][c]; //unary addition to the matrix
            }
        }
        return other;   
    }
  
      
//definition of Scalar Multiplication "*" operator (int * matrix) friend function of class Matrix
template<typename T>
Matrix<T> operator*(T num, const Matrix<T> other){
            Matrix<T> answer(other.Rows,other.Columns);
           
            for(int r=0;r<answer.Rows;r++){
                for(int c=0;c<answer.Columns;c++){
                    answer.Data[r][c]= num*other.Data[r][c]; //multiplying matrix with a scalar value
                }
            }
            return answer;
        }
    

    
#endif /* defined(__Matrices__Matrix__) */

