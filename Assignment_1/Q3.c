/*************************************************************************************************************************
//
//	CS261- Assignment 1 - Q.3
//
//	Name:						Tucker Dane Walker
//	Date:						04 July 2017
//	Solution description:		Write a function void sort(int* numbers, int n) to sort a given array of n integers 
//								in ascending order
//
//									1.	In the main function, declare an integer n and assign it a value of 20. 
//										Allocate memory for an array of n integers using malloc. Fill this array with 
//										random numbers, using the c math library random number generator rand(). Print 
//										the contents of the array.
//									2.	Pass this array along with n to the sort(...) function above. Print the contents 
//										of the sorted array following the call to sort(...). You may *not* use the C 
//										provided sort function (e.g. qsort()).
//
*************************************************************************************************************************/
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>


void sort(int* number, int n){
    /*Sort the given array number, of length n*/
	int temp;											/*	allows for swapping */
	int sorted = 1;										/*	a flag - 1 means the list is unsorted, 0 means that it is */

	while (sorted == 1)
	{
		sorted = 0;										/*	temporarily set the list to "sorted" unless a swap occurs */

		for (int i = 0; i < n-1; i++)
		{
			if (number[i] > number[i + 1])				/*	make swaps if necessary to order the list */
			{
				temp = number[i];
				number[i] = number[i + 1];
				number[i + 1] = temp;
				sorted = 1;
			}
		}
	}
}

int main(){
	srand(time(NULL));

    /*Declare an integer n and assign it a value of 20.*/
	int n = 20;
    
    /*Allocate memory for an array of n integers using malloc.*/
	int * arr = malloc(20 * sizeof(int));
    
    /*Fill this array with random numbers, using rand().*/
	for (int i = 0; i < n; i++)
	{
		arr[i] = (rand() % 100) + 1;
	}

    /*Print the contents of the array.*/
	for (int i = 0; i < n; i++)
	{
		printf("The value stored in position %d is: \t%d\n", i + 1, arr[i]);
	}
	printf("\n");

    /*Pass this array along with n to the sort() function of part a.*/
	sort(arr, n);
    
    /*Print the contents of the array.*/
	for (int i = 0; i < n; i++)
	{
		printf("The value stored in position %d is: \t%d\n", i + 1, arr[i]);
	}
	printf("\n");
    
    return 0;
}
