/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "dictionary.h"

// trie structure of node:
// each child node has 27 spots due to 26 letters + apostrophe
typedef struct node
{
    bool isWord;
    struct node* children[27];
}
node;

// set root node
node* root;

// initialize wordCount
unsigned int wordCount;

int findIndex(const char c)
{
    if (c == '\'')
    {
        return 26;
    }
    else
    {
        return (c % 'a');
    }
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // allocate memory for the root node
    root = calloc(1, sizeof(node));

    // initially set the node pointer to the root
    node* pointer = root;
    
    // open dictionary file
    FILE* fp = fopen(dictionary, "r");

    // for every dictionary word, iterate thru the trie
    for (char c = tolower(fgetc(fp)); c != EOF; c = fgetc(fp))
    {
        // at end of word, set isWord to true and reset pointer to root, and add to word count
        if (c == '\n')
        {
            pointer->isWord = true;
            pointer = root;
            wordCount++;
        }
        
        // word is still in progress: find index of each letter, build the trie
        else 
        {
            // assign index for c
            int index = findIndex(c);

            // check to see if that node exists, if not, allocate memory and create it.
            if (pointer->children[index] == NULL)
            {
                pointer->children[index] = calloc(1, sizeof(node));
            }
            
            // set pointer to the next node.
            pointer = pointer->children[index];
                
        }
    }
    
    printf("%i", wordCount);
    
    fclose(fp);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordCount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
