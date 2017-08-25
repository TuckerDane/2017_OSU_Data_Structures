//************************************************************************************************************************
//
//	CS261- Assignment 5 - main.c
//
//	Name:			Tucker Dane Walker
//	Date:			03 August 2017
//	Description:	Concordance Implementation:
//						[ ] 1.	
//						[ ] 2.	
//						[ ] 3.	
//						[ ] 4.	
//						[ ] 5.	
//						[ ] 6.	
//						[ ] 7.	
//						[ ] 8.	
//						[ ] 9.	
//						[ ] 10.	
//
// ***********************************************************************************************************************/

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

/*
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* File)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(File);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    const char* fileName = "input1.txt";
    if (argc > 1)
    {
        fileName = argv[1];
    }
    printf("Opening file: %s\n", fileName);
    
    clock_t timer = clock();
    
    HashMap* map = hashMapNew(10);
    
    // --- Concordance code begins here ---

	// 1. Open the file using fopen()
	FILE* fOut;
	fOut = fopen(fileName, "r");		//open the file for reading
	if (fOut == NULL)
	{
		fprintf(stderr, "cannot open %s\n", fileName);
	}
	else
	{
		// 2. Populate the Concordance with the words

		// 2a. Your concordance should loop over the words until the end of the file
		
		// i. Get the next word with getWord()
		char* word = nextWord(fOut);

		do
		{	// ii. If the word is already in the hash map, then increment its number of occurences
			if (hashMapContainsKey(map, word))
			{
				hashMapPut(map, word, *(hashMapGet(map, word)) + 1);
			}
			else // iii. Otherwise, put the word in the hash map with a count of 1
			{
				hashMapPut(map, word, 1);
			}

			// iv. free the word
			free(word);
			word = nextWord(fOut);	// i. Get the next word with getWord()
		} while (word != NULL);

		// 3. Close the file with fclose()
		fclose(fOut);
	}

	// 4. After processing the text file, print all words and occurence counts in the hash map
	// 4a. Print them in the format specified in the assignment above the call to hashMapPrint()

	printf("\nPRINTING ALL WORDS AND OCCURENCE COUNTS IN THE HASH MAP\n\n");

	// iterate through the hash table and print the values
	for (int i = 0; i < map->capacity; i++)
	{
		// if the bucket contains values
		if (map->table[i] != NULL)
		{
			// iterate through the links in the bucket and print them
			HashLink* temp = map->table[i];

			while (temp != NULL)
			{
				printf("%s: %d\n", temp->key, temp->value);
				temp = temp->next;
			}
		}
	}

	printf("\n");
	printf("PRINTING THE HASH MAP\n");

    // Be sure to free the word after you are done with it here.
    // --- Concordance code ends here ---
    
    hashMapPrint(map);
    
    timer = clock() - timer;
    printf("\nRan in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    printf("Empty buckets: %d\n", hashMapEmptyBuckets(map));
    printf("Number of links: %d\n", hashMapSize(map));
    printf("Number of buckets: %d\n", hashMapCapacity(map));
    printf("Table load: %f\n", hashMapTableLoad(map));
    
    hashMapDelete(map);
    return 0;
}