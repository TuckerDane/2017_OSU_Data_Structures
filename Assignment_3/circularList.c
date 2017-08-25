//************************************************************************************************************************
//
//	CS261- Assignment 3 - circularList.c
//
//	Name:			Tucker Dane Walker
//	Date:			10 July 2017
//	Description:	Circular List Implementation.
//
// ***********************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

 /*********************************************************************
 //	Allocates the list's sentinel and sets the size to 0.
 //	The sentinels' next and prev should point to the sentinel itself.
 // *********************************************************************/
static void init(struct CircularList* list)
{
	// allocate space for sentinel
	list->sentinel = malloc(sizeof(struct Link));
	assert(list->sentinel != 0);

	// Initialize sentinel to point to itself
	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;

	// Set size of Linked List to 0
	list->size = 0;
}

/*********************************************************************
// Creates a link with the given value and NULL next and prev pointers.
// *********************************************************************/
static struct Link* createLink(TYPE value)
{
	/* Create newLnk and confirm it was created */
	struct Link *newLnk = malloc(sizeof(struct Link));
	assert(newLnk != 0);

	/* initialize newLnk */
	newLnk->value = value;
	newLnk->next = NULL;
	newLnk->prev = NULL;

	return newLnk;
}

/*********************************************************************
// Adds a new link with the given value after the given link and
// increments the list's size.
// *********************************************************************/
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	/* Create newLnk */
	struct Link *newLnk = createLink(value);

	/* set next and previous values for newLnk */
	newLnk->next = link->next;
	newLnk->prev = link;

	/* reset values of pointers in links next and previous to newLink */
	newLnk->next->prev = newLnk;
	newLnk->prev->next = newLnk;

	/* increment the list size */
	list->size++;
}

/*********************************************************************
//	Removes the given link from the list and
//	decrements the list's size.
// *********************************************************************/
static void removeLink(struct CircularList* list, struct Link* link)
{
	/* assert that the list is not empty */
	assert(!circularListIsEmpty(list));

	/* reset pointers to the front/back of link to one another */
	link->next->prev = link->prev;
	link->prev->next = link->next;

	/* free the memory associated with the link to be deleted */
	free(link);

	/* decrement the size of the list */
	list->size--;
}

/*********************************************************************
//	Allocates and initializes a list.
// ********************************************************************/
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/*********************************************************************
//	Deallocates every link in the list and frees the list pointer
// *******************************************************************/
void circularListDestroy(struct CircularList* list)
{
	while (!circularListIsEmpty(list))
	{
		circularListRemoveFront(list);
	}
	free(list->sentinel);
	free(list);
}

/*********************************************************************
//	Adds a new link with the given value to the front of the deque.
// *******************************************************************/
void circularListAddFront(struct CircularList* list, TYPE value)
{
	/* adds the new link after the sentinel */
	addLinkAfter(list, list->sentinel, value);
}

/*********************************************************************
//	Adds a new link with the given value to the back of the deque.
// *******************************************************************/
void circularListAddBack(struct CircularList* list, TYPE value)
{
	/* adds the new link before the sentinel */
	addLinkAfter(list, list->sentinel->prev, value);
}

/*********************************************************************
//	Returns the value of the link at the front of the deque.
// *******************************************************************/
TYPE circularListFront(struct CircularList* list)
{
	/* assert that the list is not empty */
	assert(!circularListIsEmpty(list));

	/* return the value at the front of the lsit */
	return list->sentinel->next->value;
}

/*********************************************************************
//	Returns the value of the link at the back of the deque.
// *******************************************************************/
TYPE circularListBack(struct CircularList* list)
{
	/* assert that the list is not empty */
	assert(!circularListIsEmpty(list));

	/* return the value at the front of the lsit */
	return list->sentinel->prev->value;
}

/*********************************************************************
//	Removes the link at the front of the deque.
// *******************************************************************/
void circularListRemoveFront(struct CircularList* list)
{
	/* assert that the list is not empty */
	assert(!circularListIsEmpty(list));

	/* remove the link at the front of the deque */
	removeLink(list, list->sentinel->next);
}

/*********************************************************************
//	Removes the link at the back of the deque.
// *******************************************************************/
void circularListRemoveBack(struct CircularList* list)
{
	/* assert that the list is not empty */
	assert(!circularListIsEmpty(list));

	/* remove the link at the back of the deque */
	removeLink(list, list->sentinel->prev);
}

/*********************************************************************
//	Returns 1 if the deque is empty and 0 otherwise.
// *******************************************************************/
int circularListIsEmpty(struct CircularList* list)
{
	return list->size == 0;
}

/*********************************************************************
//	Prints the values of the links in the deque from front to back.
// *******************************************************************/
void circularListPrint(struct CircularList* list)
{
	struct Link *head = list->sentinel->next;

	while (head != list->sentinel)
	{
		printf("%f \n", head->value);
		head = head->next;
	}

	printf("\n");
}

/*********************************************************************
// Reverses the deque.
// *******************************************************************/
void circularListReverse(struct CircularList* list)
{
	assert(!circularListIsEmpty(list));

	struct Link *head = list->sentinel->next;
	int temp = head->next;

	while (head != list->sentinel)
	{
		head->next = head->prev;
		head->prev = temp;
		head = head->prev;
		temp = head->next;
	}

	temp = list->sentinel->next;
	list->sentinel->next = list->sentinel->prev;
	list->sentinel->prev = temp;

	printf("\n");
}
