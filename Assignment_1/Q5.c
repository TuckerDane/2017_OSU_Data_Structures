//************************************************************************************************************************
//
//	CS261- Assignment 1 - Q.5
//
//	Name:						Tucker Dane Walker
//	Date:						04 July 2017
//	Solution description:		Write a function void sticky(char* word) where word is a single word such as “sticky” 
//								or “RANDOM”. sticky() should modify the word to appear with “sticky caps” 
//								(http://en.wikipedia.org/wiki/StudlyCaps), that is, the letters must be in alternating 
//								cases(upper and lower), starting with upper case for the first letter. For example, 
//								“sticky” becomes “StIcKy” and “RANDOM” becomes “RaNdOm”. Watch out for the end of the
//								string, which is denoted by ‘\0’. You can assume that legal strings are given to the 
//								sticky() function. 
//								
//								NOTE: You can use the toUpperCase(...) and toLowerCase(...) functions
//								provided in the skeletal code to change the case of a character. Notice that toUpperCase() 
//								assumes that the character is currently in lower case. Therefore, you would have to check 
//								the case of a character before calling toUpperCase(). The same applies for toLowerCase(). 
//
//
//***********************************************************************************************************************/
 
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void sticky(char* word){
    /*Convert to sticky caps*/
	int i = 0;

	while (word[i] != 0) 
	{
		if (word[i] > 'Z')
			word[i]=toUpperCase(word[i]);
		if ((word[i + 1] < 'a') && (word[i+1] != 0))
			word[i+1] = toLowerCase(word[i + 1]);
		i= i+2;
	}
}

int main(){
    /*Read word from the keyboard using scanf*/
	printf("enter a word to be converted to StIcKeY KeYs: ");

	char string[25];				// create an array to hold the string
	for (int i = 0; i < 25; i++)	// initialize its contents to 0
	{
		string[i] = 0;
	}


	scanf("%s", string);

    /*Call sticky*/
	sticky(string);
    
    /*Print the new word*/
	printf("%s\n", string);
    
    return 0;
}
