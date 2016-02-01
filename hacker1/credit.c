#include <stdio.h>
#include <math.h>
#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool startsWith(const char *a, const char *b);
bool checkChecksum(char* CC);
bool isNumericString(char* CC);

int main(void)
{
    char* CC;
    do
    {
        printf("Number: ");
        CC = GetString();
    }
    while (! isNumericString(CC));
    unsigned int len = strlen(CC);
    if ((startsWith(CC, "34") || startsWith(CC, "37")) && (len == 15))
    {
        // American Express
        if (checkChecksum(CC))
        {
            printf("AMEX\n");
            return 0;
        }
    }
    else if ((startsWith(CC, "51") || startsWith(CC, "52") || startsWith(CC, "53") || startsWith(CC, "54") || startsWith(CC, "55")) && (len == 16))
    {
        // MasterCard
        if (checkChecksum(CC))
        {
            printf("MASTERCARD\n");
            return 0;
        }
    }
    else if (startsWith(CC, "4") && (len == 13 || len == 16))
    {
        // Visa
        if (checkChecksum(CC))
        {
            printf("VISA\n");
            return 0;
        }
    }
    // Invalid
    printf("INVALID\n");
    return 0;
}

// http://stackoverflow.com/a/15515276
bool startsWith(const char *haystack, const char *needle)
{
   if(strncmp(haystack, needle, strlen(needle)) == 0) return 1;
   return 0;
}

bool checkChecksum(char* CC)
{
    unsigned int result = 0;
    unsigned int len = strlen(CC);
    unsigned int offset = (len + 1 )% 2;
    for(int i = 0; i < len; i++)
    {
        int num = CC[i] - '0';
        if ((i + offset) % 2)
        {
            // Even fields (second, fourth, ...)
            int temp = num * 2;
            // Explanation: the tens are obtained by dividing by 10
            // the units are obtained by taking the modulus. We know numbers
            // will never be bigger then 18, so we don't have to calculate the 
            // hundreds in.
            result += (temp / 10) + (temp % 10);
        }
        else
        {
            // Uneven field (first, third, ...)
            result += num;
        }
    }
    return ((result % 10) == 0);
}

bool isNumericString(char* CC)
{
    for(int i = 0, len = strlen(CC); i < len; i++)
    {
        if (! isdigit(CC[i]))
        {
            return false;
        }
    }
    return true;
}