#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

#define OFFSET_LOWER 97
#define OFFSET_UPPER 65
// ASCII values for 'a' and 'A'

void printUsage(char* prog_name);
char encryptChar(char plain, int offset, int key);

int main(int argc, char* argv[])
{
    // First, let's check if the user 
    // supplied exactly one command-line argument
    if (argc != 2)
    {
        printUsage(argv[0]);
        return 1;
    }
    char* key = argv[1];
    int keylen = strlen(key);
    // Check if each character is alphabetical 
    // and transforms it to alphabet values
    for (int i = 0; i < keylen; i++)
    {
        if (! isalpha(key[i]))
        {
            printf("Key should be alphabetical\n");
            return 1;
        }
        if (islower(key[i]))
        {
            key[i] -= OFFSET_LOWER;
        }
        else if (isupper(key[i]))
        {
            key[i] -= OFFSET_UPPER;
        }
    }
    char* plaintext = GetString();
    int index = 0;
    
    // Since non-alphabetical characters don't count for the index,
    // we have to keep track of the index
    for (int i = 0, t = strlen(plaintext); i < t; i++)
        // Loops over every character in the plaintext
        {
            if (islower(plaintext[i]))
            {
                int cur_key = key[index % keylen];
                printf("%c", encryptChar(plaintext[i], OFFSET_LOWER, cur_key));
                index++;
            }
            else if (isupper(plaintext[i]))
            {
                int cur_key = key[index % keylen];
                printf("%c", encryptChar(plaintext[i], OFFSET_UPPER, cur_key));
                index++;
            }
            else
            {
                // Character is neither lowercase nor uppercase,
                // so it remains unencrypted
                printf("%c", plaintext[i]);
            }
        }
    printf("\n");
    return 0;
}

void printUsage(char* prog_name)
{
    printf(
        "Usage: %s str\n"
        "  str: the key to use (an alphabetical string)\n", prog_name);
    
}

char encryptChar(char plain, int offset, int key)
{
    int alphabet_index = plain - offset;
    int alphabet_enc = (alphabet_index + key) % 26;
    return alphabet_enc + offset;
}