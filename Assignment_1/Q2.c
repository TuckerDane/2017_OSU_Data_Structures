/*************************************************************************************************************************
//
//	CS261- Assignment 1 - Q.2
//
//	Name:						Tucker Dane Walker
//	Date:						4 July 2017
//	Solution description:		A simple program that implements the following
//
//								1.	a function int foo(int* a, int *b, int c) which performs the following computations
//										-	set the value of a to twice its original value
//										-	set the value of b to half of its original value
//										-	assign a + b to c
//										-	return the value of c
//								2.	In the main function, declare three integers x, y, and z, and assign them values 5, 6,
//									and 7 respectively. Print the values of x, y, and z. Call foo(...) appropriately 
//									passing x, y, and z as arguments and print the returned value. After the function call, 
//									print out the values of x, y, and z again. Answer the following question in a comment 
//									at the bottom of the file: Is the return value different than the value of z? Why?
//
*************************************************************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
	*a = *a * 2;

    /*Set b to half its original value*/
	*b = *b / 2;
    
    /*Assign a+b to c*/
	c = *a + *b;
    
    /*Return c*/
	return c;
}

int main(){
    /*Declare three integers x, y and z and initialize them to 5, 6, 7 respectively*/
	int x = 5;
	int y = 6;
	int z = 7;
    
    /*Print the values of x, y and z*/
	printf("The value of x is: \t%d\n", x);
	printf("The value of y is: \t%d\n", y);
	printf("The value of z is: \t%d\n\n", z);

    /*Call foo() appropriately, passing x,y,z as parameters*/
	/*Print the value returned by foo*/
	printf("The value returned by foo is: \t%d\n\n", foo(&x, &y, z));
    
    /*Print the values of x, y and z again*/
	printf("The value of x is: \t%d\n", x);
	printf("The value of y is: \t%d\n", y);
	printf("The value of z is: \t%d\n\n", z);
 
    /*Is the return value different than the value of z?  Why?*/

	//	Yes -	the return value is different from the value of z. This is because it was not directly modified in foo...
	//			a copy of z called c was modified and returned without changing z.

    return 0;
}
    
    
