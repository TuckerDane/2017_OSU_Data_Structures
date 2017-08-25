/*************************************************************************************************************************
//
//	CS261- Assignment 1 - Q.4
//
//	Name:						Tucker Dane Walker
//	Date:						04 July 2017
//	Solution description:		Consider the structure student in Q1.c. Modify the above sort(...) function from Q.3 to
//								sort an array of n students based on their scores in ascending order. The function
//								prototype is void sort(struct student* students, int n). The IDs and scores of the
//								students are to be generated randomly (see use of rand()). Also you must make sure that
//								IDs are unique.
//
//
*************************************************************************************************************************/

#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student {
	int id;
	int score;
};

void sort(struct student* students, int n) {
	/*Sort the n students based on their score*/
	struct student temp;										//	allows for swapping
	int sorted = 1;												//	a flag - 1 means the list is unsorted, 0 means that it is

	while (sorted == 1)
	{
		sorted = 0;												//	temporarily set the list to "sorted" unless a swap occurs

		for (int i = 0; i < n - 1; i++)
		{
			if (students[i].score > students[i + 1].score)		//	make swaps if necessary to order the list
			{
				temp = students[i];
				students[i] = students[i + 1];
				students[i + 1] = temp;
				sorted = 1;
			}
		}
	}
}

int main() {
	srand(time(NULL));									//	seed the random number generator

	/*Declare an integer n and assign it a value.*/
	int n = 20;

	/*Allocate memory for n students using malloc.*/
	struct student *students = malloc(n * sizeof(struct student));

	/*Generate random and unique IDs and random scores for the n students, using rand().*/
	int unique;											//	unique is a flag set to 1 if the student id is unique, 0 if it is not

	for (int i = 0; i < n; i++)							//	go through all students, setting their scores and ids
	{
		do	{											//	ensure each student id is unique
			unique = 1;									//	temporarily set flag to true (unique)
			students[i].id = (rand() % 8999) + 1001;	//	insert new student id

			for (int j = 0; j < n; j++)					//	compare student id to all other student ids
			{
				if (students[i].id == students[j].id)	//	if the student id is not unique, set unique to 0 and break out of this loop; reset student id
				{
					if (i != j)			
					{
						unique = 0;
						break;
					}
				}
			}

		} while (unique == 0);							//	once a unique student id is generated and set, continue on
		
		students[i].score = (rand() % 100) + 1;			//	randomly generate a student score
	}

    /*Print the contents of the array of n students.*/
	for (int i = 0; i < n; i++)
	{
		printf("ID%d: \t%d \t Score%d: \t%d \n", i + 1, students[i].id, i + 1, students[i].score);
	}

	printf("\n");

    /*Pass this array along with n to the sort() function*/
	sort(students, n);
    
    /*Print the contents of the array of n students.*/
	for (int i = 0; i < n; i++)
	{
		printf("ID%d: \t%d \t Score%d: \t%d \n", i + 1, students[i].id, i + 1, students[i].score);
	}

	printf("\n");

	/*Free memory allocated for students*/
	free(students);
    
    return 0;
}
