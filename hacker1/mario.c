#include <stdio.h>
#include <cs50.h>
#define MAX_HEIGHT 23
#define PIRAMID_CHAR '#'
#define SPACING ' '

void repeatPrint(char repeat, int n);

int main(void)
{
    int height;
    // Get height from user and check if it's a strictly positive integer
    // no bigger then MAX_HEIGHT
    do 
    {
        printf("Height: ");
        height = GetInt();
    }
    while ((height > MAX_HEIGHT) || (height < 0));
    for(int i = 0; i < height; i++)
    {
        // Prints one row of the piramid
        repeatPrint(SPACING, height - i - 1);
        repeatPrint(PIRAMID_CHAR, i + 1);
        // Prints gap between two half-piramids
        repeatPrint(SPACING, 2);
        repeatPrint(PIRAMID_CHAR, i + 1);
        printf("\n");
    }
    return 0;
}

/*
    Prints `repeat` `n` times
*/
void repeatPrint(char repeat, int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%c", repeat);
    }
}