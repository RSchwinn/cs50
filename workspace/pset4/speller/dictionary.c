// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}


//// Initialize dictionary size here which we later increment
int wordsInDict = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];


    //// The /n makes this read each line one at a time.
    // Insert words into hash table
    while (fscanf(file, "%s\n", word) != EOF)
    {
        // file >>> is the dictionary in memory
        // text >>> the text in memory

        // TODO
        // (1) Read each word. We can use the same setup as found in speller for reading words out of the text, but that is not
        // necesary because we do not need to be so careful due to the structure of the dictionary. (Basically,
        // fgetc in speller.c reads the next character into a string called word if it is a letter or apostrophe. Otherwise, it skips any
        // remaining characters and advances to the next word.)
        // (2) Create a node and put the word in the first position. Point this node to the address of the letter in the hashtable
        // that corresponds to the first letter in the word. Use "hash" for this.

        //// create a new node
        node *newNode = malloc(sizeof(node));

        //// save word to node
        strcpy(newNode->word, word);

        int wordHash = hash(word);

        // if hashtable location is empty, then copy node into place
        if (hashtable[wordHash] == NULL)
        {
            hashtable[wordHash] = newNode;
            newNode->next = NULL;
        }
        else
        // if not, add the address of the hashtable entry to the newNode and overwrite hashtable entry with newNode
        {
            newNode->next = hashtable[wordHash];
            hashtable[wordHash] = newNode;
        }

        // Increment word count size
        wordsInDict++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (wordsInDict == 0)
    {
        return 0;
    }
    else
    {
        return wordsInDict;
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{

    char lowerCaseWord[strlen(word)+1];
    for (int i = 0; i < strlen(word); i++)
    {
        lowerCaseWord[i] = tolower(word[i]);
    }
    lowerCaseWord[strlen(word)] = '\0';

    int wordHash = hash(lowerCaseWord);
    node* cursor = hashtable[wordHash];

    if (hashtable[wordHash] == NULL)
    {
        return false;
    }

    while (cursor != NULL)
    {
        if (strcmp(cursor->word, lowerCaseWord) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = hashtable[i];

        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}