//************************************************************************************************************************
//
//	CS261- Assignment 4 - task.c
//
//	Name:			Tucker Dane Walker
//	Date:			01 August 2017
//	Description:	Task Implementation.
//						Fixed the following functions:
//							1.	[x] taskNew()
//							2.	[x] taskDelete()
//							3.	[x] taskCompare()
//
// ***********************************************************************************************************************/

#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

/**
 * Creates a new task with the given priority and name.
 * @param priority
 * @param name
 * @return  The new task.
 */
Task* taskNew(int priority, char* name)
{
    // allocate memory for a new task
	struct Task * newTask = malloc(sizeof(struct Task));
	assert(newTask != 0);

	// fill the name of the new task
	int i = 0;
	while (name[i] != '\0')
	{
		newTask->name[i] = name[i];
		i++;
	}
	newTask->name[i] = name[i];
	//i++;

	newTask->priority = priority;

    return newTask;
}

/**
 * Frees a dynamically allocated task.
 * @param task
 */
void taskDelete(Task* task)
{
    free(task);
}

/**
 * Casts left and right to Task pointers and returns
 * -1 if left's priority < right's priority,
 *  1 if left's priority > right's priority,
 *  0 if left's priority == right's priority.
 * @param left  Task pointer.
 * @param right  Task pointer.
 * @return 
 */
int taskCompare(void* left, void* right)
{
	if (((Task*)left)->priority < ((Task*)right)->priority)
	{
		return -1;
	}
	else if (((Task*)left)->priority > ((Task*)right)->priority)
	{
		return 1;
	}
	else
	{
		return 0;
	}
		
    return 0;
}

/**
 * Prints a task as a (priority, name) pair.
 * @param value  Task pointer.
 */
void taskPrint(void* value)
{
    Task* task = (Task*)value;
    printf("%d :	%s", task->priority, task->name);
}
