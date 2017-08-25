/*************************************************************************************************************************
//
//	CS261- Assignment 1 - Q.1
//
//	Name:						Tucker Dane Walker
//	Date:						4 July 2017
//	Solution description:		A simple program that implements the following functions and demonstrate their 
//								functionality by calling them (in the order given) from the main function:
//
//								1.	Write a function struct student* allocate() that allocates memory for ten students 
//									and returns the pointer.
//								2.	Write a function void generate(struct student* students) that generates random IDs 
//									and scores for each of the ten students and stores them in the array of students. 
//									You can make use of the rand() function to generate random numbers. Ensure that IDs 
//									are unique and between 1 and 10 (both inclusive) and score is between 0 and 100 (both 
//									inclusive).
//								3.	Write a function void output(struct student* students) that prints the ids and scores 
//									of all the students. the output of the function need not to be sorted.
//								4.	Write a function void summary(struct student* students) that prints the minimum score, 
//									maximum score and average score of the ten students.
//								5.	Write a function void deallocate(struct student* stud) that frees the memory
//									allocated to the students. Check that students is not NULL (NULL == 0) before you
//									attempt to free it
//
*************************************************************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct student{
	int id;
	int score;
};


//*********************************************************************************************/
//	Allocate memory for ten students
//*********************************************************************************************/
struct student* allocate(){
    /*Allocate memory for ten students*/
	int numStudents = 10;
	struct student *sptr = malloc(numStudents * sizeof(struct student));

    /*return the pointer*/
	return sptr;
}

//*********************************************************************************************/
//	Generate random and unique ID and scores for ten students, ID being between 1 and 10, 
//	scores between 0 and 100
//*********************************************************************************************/
void generate(struct student* students){
	
	for (int i = 0; i < 10; i++)
	{

		/* uniqueFlag is set to 1 when the student id is unique, 0 when it is not */
		int uniqueFlag = 0;

		/* assign a unique ID to the student */
		while (uniqueFlag == 0)
		{
			uniqueFlag = 1;									/* assume that the student ID is unique until proven false */
			students[i].id = (rand() % 10) + 1;				/* set a student ID */
			for (int j = 0; j < i; j++)						/* check the student ID against all other student IDs */
			{
				if (students[i].id == students[j].id)		/* if the student ID is equal to any other student ID... */
				{
					uniqueFlag = 0;							/* ... then it is not unique; Set a new student ID */
				}
			}

		}

		/* assign a score to the student */
		students[i].score = (rand() % 100) + 1;
	}
}

//*********************************************************************************************/
//	Output information about the ten students
//*********************************************************************************************/
void output(struct student* students){
    
	for (int i = 0; i < 10; i++)
	{
		printf("ID%d: \t%d \t Score%d: \t%d \n", i + 1, students[i].id, i + 1, students[i].score);
	}

	printf("\n");
}

//*********************************************************************************************/
//	Compute and print the minimum, maximum and average scores of the ten students
//*********************************************************************************************/
void summary(struct student* students){

	int min = 100;							// initialize min to the highest possible score
	int max = 0;							// initialize max to the lowest possible score
	int avg = 0;							// initialize average to 0 to be added to

	for (int i = 0; i < 10; i++)			// loop through all of the student's scores
	{
		avg += students[i].score;			// add the student score to average

		if (students[i].score < min)		// if the student's score is less than the current minimum
			min = students[i].score;		// reset min to the new lowest score

		if (students[i].score > max)		// if the student's score is greater than the current maximum
			max = students[i].score;		// reset max to the new highest score
	}

	avg = avg / 10;							// compute the average of the total student scores

	printf("The minimum student score is: \t%d \n", min);
	printf("The maximum student score is: \t%d \n", max);
	printf("The average student score is: \t%d \n\n", avg);
     
}

//*********************************************************************************************/
//	Deallocate memory from stud
//*********************************************************************************************/
void deallocate(struct student* stud){
    
	if (stud != NULL)
	{
		free(stud);
	}
}

int main(){
    struct student* st = NULL;	
	srand(time(NULL));					
    
    /*call allocate*/
	st = allocate();

    /*call generate*/
	generate(st);

    /*call output*/
	output(st);
    
    /*call summary*/
	summary(st);

    /*call deallocate*/
	deallocate(st);

    return 0;
}
