 /*************************************************************************************************************************
 //
 //	CS261- Assignment 1 - Q.0
 //
 //	Name:						Tucker Dane Walker
 //	Date:						4 July 2017
 //	Solution description:		A simple program that:
 //									1.	declares an integer x and initializes it to 3
 //									2.	prints the address of x
 //									3.	passes x as an argument to a function void fooA(int* iptr)
 //									4.	prints the value of the integer pointed to by iptr
 //									5.	prints the address pointed to by iptr
 //									6.	prints the address of iptr itself
 //									7.	prints the value of x
 //
 *************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     /*Print the value pointed to by iptr*/
	printf("The value pointed to by iptr is: \t%d\n", *iptr);

     /*Print the address pointed to by iptr*/
	printf("The address pointed to by iptr is: \t%d\n", iptr);
     
     /*Print the address of iptr itself*/
	printf("The address of iptr itself is: \t\t%d\n", &iptr);
}

int main(){
    
    /*declare an integer x*/
	int x = 3;
    
    /*print the address of x*/
	printf("The address of x is: \t\t\t%d\n", &x);
    
    /*Call fooA() with the address of x*/
	fooA(&x);
    
    /*print the value of x*/
	printf("The value of x is: \t\t\t%d\n", x);
    
	printf("\n");
    return 0;
}
