//************************************************************************************************************************
//
//	CS261- Assignment 2 - stack.c
//
//	Name:			Tucker Dane Walker
//	Date:			07 July 2017
//	Description:	Stack application.
//
//***********************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"

/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param:	s pointer to a string 	
	pre:	s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre:	s is not null	
	post:	returns 0 if not balanced, 1 if balanced
*/
int isBalanced(char* s)
{
	DynArr *stack;
	stack = newDynArr(2);
	assert(stack != 0);

	char temp = nextChar(s);

	while (!EQ(temp, '\0'))
	{
		if (EQ(temp, '(') || EQ(temp, '{') || EQ(temp, '['))
		{
			pushDynArr(stack, temp);
		}
		else if ((isEmptyDynArr(stack) == 1) && (EQ(temp, ')') || EQ(temp, '}') || EQ(temp, ']')))
		{
			deleteDynArr(stack);
			return 0;
		}
		else if (EQ(temp, ')'))
		{
			if (EQ(topDynArr(stack), '('))
				popDynArr(stack);
			else
			{
				deleteDynArr(stack);
				return 0;
			}
		}
		else if (EQ(temp, '}'))
		{
			if (EQ(topDynArr(stack), '{'))
				popDynArr(stack);
			else
			{
				deleteDynArr(stack);
				return 0;
			}
		}
		else if (EQ(temp, ']'))
		{
			if (EQ(topDynArr(stack), '['))
				popDynArr(stack);
			else
			{
				deleteDynArr(stack);
				return 0;
			}
		}

		temp = nextChar(s);
	}

	if (!isEmptyDynArr(stack))
	{
		deleteDynArr(stack);
		return 0;
	}
	else
	{
		deleteDynArr(stack);
		return 1;
	}
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];

	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

