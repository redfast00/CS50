#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

#define OFFSET_LOWER 97
#define OFFSET_UPPER 65

void printUsage(char* prog_name);
char encryptChar(char plain, int offset, int key);

int main(int argc, char* argv[])
{
    // First, check if the user 
    // supplied exactly one command-line argument
    if (argc != 2)
    {
        printUsage(argv[0]);
        return 1;
    }
    int key = atoi(argv[1]);
    if (key <= 0)
    {
        // Key is 0 or not an integer
        printf("Key should be a non-negative integer\n");
        return 2;
    }
    char* plaintext = GetString();

    // Loops over every character in the plaintext
    for (int i = 0, t = strlen(plaintext); i < t; i++)
    {
        if (islower(plaintext[i]))
        {
            printf("%c", encryptChar(plaintext[i], OFFSET_LOWER, key));
        }
        else if (isupper(plaintext[i]))
        {
            printf("%c", encryptChar(plaintext[i], OFFSET_UPPER, key));
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
        "Usage: %s n\n"
        "  n: the key to use (a non-negative integer)\n"
        "Encrypt a text with caesar cipher\n", prog_name
          );
    
}

char encryptChar(char plain, int offset, int key)
{
    // Get the index in the alphabet (A=0, B=1, Z=25)
    int alphabet_index = plain - offset;
    int alphabet_enc = (alphabet_index + key) % 26;
    // Get from index to ascii value
    return alphabet_enc + offset;
}