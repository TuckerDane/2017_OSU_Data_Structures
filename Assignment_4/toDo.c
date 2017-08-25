//************************************************************************************************************************
//
//	CS261- Assignment 4 - toDo.c
//
//	Name:			Tucker Dane Walker
//	Date:			01 August 2017
//	Description:	To Do List Implementation.
//						Fixed the following functions:
//							1.	[ ] handleCommand()
//							2.	[ ] main()
//
// ***********************************************************************************************************************/

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
    const int FORMAT_LENGTH = 256;
    char format[265];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);
    
    Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    {
        dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
    }
}

/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
     while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
	assert(list != 0);
	FILE *fIn;
	FILE *fOut;

	switch (command)
	{
	case 'l':		// load to-do list from a file (code modified from Fall 2012 CS 261 Recitation 6)
		printf("LOADING FILE\n");

		char lfName[100];
		printf("Please enter a filename: ");
		fgets(lfName, 100, stdin);
		lfName[strcspn(lfName, "\n\r")] = 0;

		fOut = fopen(lfName, "r");		//open the file for reading
		if (fOut == NULL)
		{
			fprintf(stderr, "cannot open %s\n", "todo.txt");
		}
		else
		{
			listLoad(list, fOut);	// load list onto the heap
			printf("%s loaded onto the heap!\n", lfName);
			fclose(fOut);			// close the file
		}
		break;
	case 's':		// save to-do list to a file
		printf("SAVING HEAP TO FILE\n");

		char sfName[100];
		printf("Please enter a filename: ");
		fgets(sfName, 100, stdin);
		sfName[strcspn(sfName, "\n\r")] = 0;

		fIn = fopen(sfName, "w");		// open the file for writing
		if (fIn == NULL)
		{
			fprintf(stderr, "cannot open %s\n", sfName);
		}
		else
		{
			listSave(list, fIn);	//	save heap into a file
			fclose(fIn);			//	close the file
			printf("%s Saved Successfully!\n", sfName);
		}
		break;
	case 'a':		// add a new task
		printf("ADDING TASK\n");
		printf("Please enter the task description :	");
		char str[100];
		fgets(str, 100, stdin);
		str[strcspn(str, "\n\r")] = 0;
		char *name;
		name = &str;
		int priority = -1;

		while (priority < 0 || priority > 999)
		{
			printf("Enter the task priority (0-999) :	");
			scanf("%d", &priority);
		}

		dyHeapAdd(list, taskNew(priority, name), taskCompare);
		printf("\n");
		printf("The task ( ");
		printf("%d : %s", priority, name);
		printf(" ) has been added to your to - do list.\n");

		while (getchar() != '\n');
		break;
	case 'g':		// get the first task
		printf("GETTING FIRST TASK\n");
		if (dySize(list) == 0)
		{
			printf("Your to-do list is empty!\n");
		}
		else
		{
			Task* task = dyHeapGetMin(list);
			printf("Your first task is\n");
			taskPrint(task);
			printf("\n");
		}
		break;
	case 'r':		// remove the first task
		printf("REMOVING FIRST TASK\n");
		if (dySize(list) == 0)
		{
			printf("Your to-do list is empty!\n");
		}
		else
		{
			dyHeapRemoveMin(list, taskCompare);
			printf("The first task has been removed.\n");
		}
		break;
	case 'p':		// print the list
		printf("PRINTING TASK LIST\n");
		if (dySize(list) == 0)
		{
			printf("Your to-do list is empty!\n\n");
		}
		else
		{
			printf("Your to-do list is as follows:\n");
			listPrint(list);
		}
		break;
	case 'e':		// exit the program
		printf("See ya later NERD!\n");
		break;
	}
}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n\n"
        );
        command = getchar();
        // Eat newlines
		while (getchar() != '\n');
		printf("\n");
        handleCommand(list, command);
		printf("\n");
    }
    while (command != 'e');

	//	garbage collection
    dyDelete(list);
    return 0;
}
