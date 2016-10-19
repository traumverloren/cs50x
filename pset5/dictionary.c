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
        // make sure to change any uppercase to lowercase when returning index value
        return (tolower(c) % 'a');
    }
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // initially set the node pointer to the root
    node* pointer = root;
    
    // check each char in a word til hits the NUL terminator
    for (int i=0; word[i] !='\0'; i++)
    {
        // find index value for lookup in children node
        int index = findIndex(word[i]);
    
        // if child node is NULL, word is misspelled
        if (pointer->children[index] == NULL)
            return false;
   
        // else since !NULL, move to next letter by setting pointer to the next node.
        pointer = pointer->children[index];
    }
    
    // if at \n,  return value of isWord is true
    return pointer->isWord;
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
    for (char c = fgetc(fp); c != EOF; c = fgetc(fp))
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
    
    // close dictionary file
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

bool freeNodes(node* pointer)
{
    // unload top to bottom...
    // free all pointers in children, backwards up, freeing all children up to the root.
    for (int i = 0; i < 27; i++)
    {
        // if pointer's child node isn't NULL, keep going down the rabbit hole...
        if (pointer->children[i] != NULL)
            // recursively call our freeNodes method until the lowest possible node is reached.
            freeNodes(pointer->children[i]);
    }
    
    // once we hit the bottom, free those nodes!
    free(pointer);
    
    return true;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    return freeNodes(root);
}
