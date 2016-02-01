/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 5
 */

#include "helpers.h"
#include <stdlib.h>
#include <string.h>

/**
 * djb2 hashing function
 * Returns a hash given a pointer to a string
 * Adapted from http://www.cse.yorku.ca/~oz/hash.html
 */
unsigned int hash(char* str)
{
    unsigned int hash = 5381;
    unsigned int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

// Adapted from https://study.cs50.net/linked_lists
bool search(char word[LENGTH + 1], node* head)
{
    node* ptr = head;
    while (ptr != NULL)
    {
        if (strcmp(word, ptr->word) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

// Self-invented
void rec_free(node* node)
{
    if(node->next != NULL)
    {
        free(node->word);
        // Free next node
        rec_free(node->next);
    }
    free(node);
}
