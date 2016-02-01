/**
 * helpers.h
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
#ifndef HELPERS_H
#define HELPERS_H
#include "dictionary.h"
// Linked list from https://study.cs50.net/linked_lists
typedef struct node 
{
    char* word;
    struct node* next;
}
node;

unsigned int hash(char* str);

bool search(char word[LENGTH + 1], node* head);
void rec_free(node*);
#endif