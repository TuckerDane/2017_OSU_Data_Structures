//************************************************************************************************************************
//
//	CS261- Assignment 5 - hashMap.c
//
//	Name:			Tucker Dane Walker
//	Date:			03 August 2017
//	Description:	Hash Map Implementation:
//						[x] 1.	hashMapCleanUp()
//						[x] 2.	hashMapGet()
//						[x] 3.	resizeTable()
//						[x] 4.	hashMapPut()
//						[x] 5.	hashMapRemove()
//						[x] 6.	hashMapContainsKey()
//						[x] 7.	hashMapSize()
//						[x] 8.	hashMapCapacity()
//						[x] 9.	hashMapEmptyBuckets()
//						[x] 10.	hashMapTableLoad()
//
// ***********************************************************************************************************************/

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    // used to assist with freeing hashLinks
	HashLink* temp = NULL;

	// iterate through the buckets in the hash table
	for (int i = 0; i < map->capacity; i++)
	{
		// clean up the hashLinks in the bucket until the bucket is empty (points to NULL)
		temp = map->table[i];
		if (temp != NULL)
		{
			while (temp->next != NULL)
			{
				map->table[i] = temp->next;
				hashLinkDelete(temp);
				temp = map->table[i];
			}
			hashLinkDelete(temp);
		}
	}
	free(map->table);
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
	// Hash to the bucket
	int idx = HASH_FUNCTION(key) % map->capacity;

	// Iterate through the bucket until value is found or NULL
	HashLink* tempLnk = map->table[idx];
	while (tempLnk != NULL)
	{	
		// if the bucket contains the key
		if (strcmp(tempLnk->key, key) == 0)
		{
			// return the value associated with the kay
			return &(tempLnk->value);
		}
		tempLnk = tempLnk->next;
	}

	// Return NULL - the bucket does not contain the key
    return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given
 * capacity. After allocating the new table, all of the links need to be
 * rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
	HashMap* newMap = malloc(sizeof(HashMap));
	hashMapInit(map, capacity);
	HashLink* currentLnk = NULL;

	// iterate through the buckets of the old map
	for (int i = 0; i < capacity; i++)
	{
		currentLnk = map->table[i];
		// while the current bucket contains values that have not been added to newMap
		while (currentLnk != NULL)
		{
			// assign those values to the new hashTable
			int idx = HASH_FUNCTION(currentLnk->key) % newMap->capacity;
			currentLnk = currentLnk->next;
		}
	}

	// no freeing is necessary, because all values pointed to in map into newMap are maintained in map
	map = newMap;

}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
	int idx = HASH_FUNCTION(key) % map->capacity;
	HashLink* currentLnk = map->table[idx];

	// if the bucket does not contain values in it
	if(currentLnk == NULL)
	{
		// place a new hashLink with the key/value pair there
		map->table[idx] = hashLinkNew(key, value, NULL);
		map->size++;
	}
	else // otherwise the bucket does contain values...
	{
		// check to see if the first link contains the key, if it does, add in the value
		if (strcmp(currentLnk->key, key) == 0)
		{
			currentLnk->value = value;
			return;
		}
		else // otherwise...
		{
			// iterate through the appropriately indexed bucket
			// if the bucket contains the key, update and return
			while (currentLnk->next != NULL)
			{
				// if the next link contains the key, update the value and return
				if (strcmp(currentLnk->next->key, key) == 0)
				{
					currentLnk->next->value = value;
					return;
				}
				else
				{
					currentLnk = currentLnk->next;
				}
			}

			// The map does not contain the Key, add the key/value pair as a new link and return.
			currentLnk->next = hashLinkNew(key, value, NULL);
			map->size++;
		}
	}

	return;
}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
	assert(map != 0);
	assert(key != 0);

	int idx = HASH_FUNCTION(key) % map->capacity;
	HashLink* nextLnk = NULL;
	HashLink* currentLnk = NULL;

	// If the hashmap contains the key
	if (hashMapContainsKey(map, key) == 1)
	{
		// iterate through the appropriately indexed bucket
		if (map->table[idx] != NULL)
		{
			currentLnk = map->table[idx];
			nextLnk = map->table[idx]->next;

			// if the first link in the bucket contains the key, set the first link to the next link and free the current
			if (strcmp(currentLnk->key, key) == 0)
			{
				// set the first link to the next
				map->table[idx] = nextLnk;

				// delete the current link
				hashLinkDelete(currentLnk);
				map->size--;
			}

			// if the first is not the key, iterate through the list, find it, remove it and return
			while (nextLnk != NULL)
			{
				// if the next link is the key, set currentLnk to the link after Next link, remove nextLink and return
				if (strcmp(nextLnk->key, key) == 0)
				{
					// reset links
					currentLnk->next = nextLnk->next;

					// delete link with the key
					hashLinkDelete(nextLnk);
					map->size--;

					// link was removed; return
					return;
				}
				else // if the next link does not contain the key, continue moving forward
				{
					currentLnk = nextLnk;
					nextLnk = currentLnk->next;
				}
			}
		}

		// The map does not contain the Key
		return;
	}

}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
	int idx = HASH_FUNCTION(key) % map->capacity;
	HashLink* currentLnk = NULL;

	// iterate through the appropriately indexed bucket
	if (map->table[idx] != NULL)
	{
		currentLnk = map->table[idx];

		// if the bucket contains the key, return 1
		while (currentLnk != NULL)
		{
			// if the current link is the key, return 1
			if (strcmp(currentLnk->key, key) == 0)
			{
				return 1;
			}
			else
			{
				currentLnk = currentLnk->next;
			}
		}
	}

	// The map does not contain the Key
    return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
	int emptyBuckets = 0;

	// iterate through the table
	for (int i = 0; i < map->capacity; i++)
	{
		// check each table to see if it points to null
		if (map->table[i] == NULL)
		{
			// if it does, add 1 to empty buckets
			emptyBuckets++;
		}
	}
	
    return emptyBuckets;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
	// (values in the map / number of full buckets)
	return (float)map->size / map->capacity;
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    for (int i = 0; i < map->capacity; i++)
    {
        HashLink* link = map->table[i];
        if (link != NULL)
        {
            printf("\nBucket %i ->", i);
            while (link != NULL)
            {
                printf(" (%s, %d) ->", link->key, link->value);
                link = link->next;
            }
        }
    }
    printf("\n");
}