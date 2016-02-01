/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"
#include "helpers.h"

static node* hashtable[BUCKETS];
static int words_in_dict = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int i;
    char lower_word[LENGTH + 1];
    
    for(i = 0; word[i]; i++)
    {
        lower_word[i] = tolower(word[i]);
    }
    lower_word[i] = '\0';
    unsigned int index = hash(lower_word) % BUCKETS;
    return search(lower_word, hashtable[index]);
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(char* dictionary)
{
    // Initialize every node
    for(int i = 0; i < BUCKETS; i++)
    {
        node* head = malloc(sizeof(node));
        if (head == NULL)
        {
            return false;
        }
        head->next = NULL;
        head->word = "";
        hashtable[i] = head;
    }
    // Open dictionary file
    FILE* dictfp = fopen(dictionary, "r");
    
    // Check if opened correctly
    if (dictfp == NULL)
    {
        return false;
    }
    // LENGHT + 2 for null character and newline at end of line
    char line[LENGTH + 2];
    // attribution: http://pubs.opengroup.org/onlinepubs/009695399/functions/fgets.html
    while (fgets(line, LENGTH + 2, dictfp) != NULL)
    {
        // newline removing technique
        // http://stackoverflow.com/a/28462221
        line[strcspn(line, "\n")] = '\0';
        unsigned int index = (unsigned int) hash(line) % BUCKETS;
        node* new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        // strlen(line) + 1 because the null character is also stored
        char* storage_word = malloc(strlen(line) + 1);
        strcpy(storage_word, line);
        // based on https://study.cs50.net/linked_lists
        new_node->word = storage_word;
        new_node->next = hashtable[index];
        hashtable[index] = new_node;
        words_in_dict++;
    }
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return words_in_dict;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for(int i = 0; i < BUCKETS; i++)
    {
        rec_free(hashtable[i]);
    }
    return true;
}