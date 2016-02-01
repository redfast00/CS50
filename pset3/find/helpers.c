/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Function returns true if value is in values[], bounds are inclusive
 */
bool binSearch(int value, int left_bound, int right_bound, int values[])
{

    if (left_bound > right_bound)
    {
        return false;
    }
    int middle = (left_bound + right_bound)/2;
    
    if (values[middle] == value)
    {
        // Found it!
        return true;
    }
    else if (values[middle] > value)
    {
        return binSearch(value, left_bound, middle - 1, values);
    }
    else
    {
        return binSearch(value, middle + 1, right_bound, values);
    }
}
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // This assumes the values[] are sorted
    
    // Check if n is non-negative
    if (n <= 0)
    {
        return false;
    }
    return binSearch(value, 0, n - 1, values);
    
    
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    bool did_swap;
    do
    {
        did_swap = false;
        for (int i = 1; i < n; i++)
        {
            if (values[i - 1] > values[i])
            {
                // Swap values
                int temp = values[i];
                values[i] = values[i - 1];
                values[i - 1] = temp;
                did_swap = true;
            }
        }
        n--;
    }
    while (did_swap);
    return;
}