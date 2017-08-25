//************************************************************************************************************************
//
//	CS261- Assignment 3 - linkedList.c
//
//	Name:			Tucker Dane Walker
//	Date:			10 July 2017
//	Description:	Linked List Implementation.
//
// ***********************************************************************************************************************/

#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/*********************************************************************
//	Double link
// ********************************************************************/
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

/*********************************************************************
//	Double linked list with front and back sentinels
// ********************************************************************/
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/*********************************************************************
//	Allocates the list's sentinel and sets the size to 0.
//	The sentinels' next and prev should point to eachother or NULL
//	as appropriate.
// *********************************************************************/
static void init(struct LinkedList* list) {

	// allocate space for frontSentinel and backsSentinel
	list->frontSentinel = malloc(sizeof(struct Link));
	assert(list->frontSentinel != 0);
	list->backSentinel = malloc(sizeof(struct Link));
	assert(list->backSentinel != 0);

	// Initialize frontSentinal and backSentinel to point to one another and to 0
	list->frontSentinel->next = list->backSentinel;
	list->frontSentinel->prev = 0;
	list->backSentinel->next = 0;
	list->backSentinel->prev = list->frontSentinel;
	

	// Set size of Linked List to 0
	list->size = 0;
}

/*********************************************************************
//	Adds a new link with the given value before the given link and
//	increments the list's size.
// ********************************************************************/
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	/* Create newLnk and confirm it was created */
	struct Link *newLnk = malloc(sizeof(struct Link));
	assert(newLnk != 0);

	/* initialize newLnk */
	newLnk->value = value;
	newLnk->next = link;
	newLnk->prev = link->prev;

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
static void removeLink(struct LinkedList* list, struct Link* link)
{
	/* assert that the list is not empty */
	assert(!linkedListIsEmpty(list));

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
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/*********************************************************************
//	Deallocates every link in the list including the sentinels,
//	and frees the list itself.
// *******************************************************************/
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/*********************************************************************
//	Adds a new link with the given value to the front of the deque.
// *******************************************************************/
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	/* Create newLnk and confirm it was created */
	struct Link *newLnk = malloc(sizeof(struct Link));
	assert(newLnk != 0);

	/* initialize newLnk */
	newLnk->value = value;
	newLnk->next = list->frontSentinel->next;
	newLnk->prev = list->frontSentinel;

	/* reset values of pointers in links next and previous to newLink */
	newLnk->next->prev = newLnk;
	newLnk->prev->next = newLnk;

	/* increment the list size */
	list->size++;
}

/*********************************************************************
//	Adds a new link with the given value to the back of the deque.
// *******************************************************************/
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	/* Create newLnk and confirm it was created */
	struct Link *newLnk = malloc(sizeof(struct Link));
	assert(newLnk != 0);

	/* initialize newLnk */
	newLnk->value = value;
	newLnk->next = list->backSentinel;
	newLnk->prev = list->backSentinel->prev;

	/* reset values of pointers in links next and previous to newLink */
	newLnk->next->prev = newLnk;
	newLnk->prev->next = newLnk;

	/* increment the list size */
	list->size++;
}

/*********************************************************************
//	Returns the value of the link at the front of the deque.
// *******************************************************************/
TYPE linkedListFront(struct LinkedList* list)
{
	/* assert that the list is not empty */
	assert(!linkedListIsEmpty(list));

	/* return the value at the front of the lsit */
	return list->frontSentinel->next->value;
}

/*********************************************************************
//	Returns the value of the link at the back of the deque.
// *******************************************************************/
TYPE linkedListBack(struct LinkedList* list)
{
	/* assert that the list is not empty */
	assert(!linkedListIsEmpty(list));

	/* return the value at the front of the lsit */
	return list->backSentinel->prev->value;
}

/*********************************************************************
//	Removes the link at the front of the deque.
// *******************************************************************/
void linkedListRemoveFront(struct LinkedList* list)
{
	/* assert that the list is not empty */
	assert(!linkedListIsEmpty(list));

	/* remove the link at the front of the deque */
	removeLink(list, list->frontSentinel->next);
}

/*********************************************************************
//	Removes the link at the back of the deque.
// *******************************************************************/
void linkedListRemoveBack(struct LinkedList* list)
{
	/* assert that the list is not empty */
	assert(!linkedListIsEmpty(list));

	/* remove the link at the front of the deque */
	removeLink(list, list->backSentinel->prev);
}

/*********************************************************************
//	Returns 1 if the deque is empty and 0 otherwise.
// *******************************************************************/
int linkedListIsEmpty(struct LinkedList* list)
{
	return list->size == 0;
}

/*********************************************************************
//	Prints the values of the links in the deque from front to back.
// *******************************************************************/
void linkedListPrint(struct LinkedList* list)
{
	assert(!linkedListIsEmpty(list));
	
	struct Link *head = list->frontSentinel->next;

	while (head->next != NULL)
	{
		printf("%d \n", head->value);
		head = head->next;
	}

	printf("\n");
}

/*********************************************************************
//	Adds a link with the given value to the bag.
// *******************************************************************/
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	addLinkBefore(list, list->backSentinel, value);
}

/*********************************************************************
//	Returns 1 if a link with the value is in the bag and 0 otherwise.
// *******************************************************************/
int linkedListContains(struct LinkedList* list, TYPE value)
{
	assert(!linkedListIsEmpty(list));
	struct Link *head = list->frontSentinel->next;

	while (head->next != NULL)
	{
		if(head->value == value)
		{
			return 1;
		}
		head = head->next;
	}
	return 0;
}

/*********************************************************************
//	Removes the first occurrence of a link with the given value.
// *******************************************************************/
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	assert(linkedListContains(list, value));

	struct Link *head = list->frontSentinel->next;
	int removed = 0;

	while (head != NULL && removed == 0)
	{
		if (head->value == value)
		{
			removeLink(list, head);
			removed = 1;
		}
		head = head->next;
	}
}
