#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <cs50.h>
#include <ctype.h>

#define SPACE ' '

int main(void)
{
    // This assumes the following:
    // Names only contain lower- and uppercase letters
    // Names don't contain two consequetive spaces
    char* name = GetString();
    bool initial = true;
    // The first letter will always be an initial

    if (name != NULL)
    // Check if user typed something
    {
        for (int i = 0, t = strlen(name); i < t; i++)
        // Loops over every character in the string
        // Optimized (doesn't call strlen every time)
        {
            if (initial)
            {
                // This is an initial, let's uppercase and print it
                printf("%c", toupper(name[i]));
                initial = false;
            }
            if (name[i] == SPACE)
            {
                // This character is a space, so the next character
                // will be an initial
                initial = true;
            }
        }
        printf("\n");
        // Print a newline
    }
}