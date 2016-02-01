#include <stdio.h>
#include <cs50.h>
#define MINUTES_TO_BOTTLES_FACTOR 12

int main(void)
{
   printf("minutes: ");
   int minutes = GetInt();
   int bottles = minutes * MINUTES_TO_BOTTLES_FACTOR;
   printf("bottles: %d\n", bottles);
}