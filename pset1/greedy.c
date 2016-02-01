#include <stdio.h>
#include <math.h>
#include <cs50.h>

int calcNumCoins(int cents);

int main(void)
{
    float dollars;
    do 
    {
        printf("O hai! How much change is owed?\n");
        dollars = GetFloat();
    }
    while (dollars < 0);

    // Converts dollars to cents and calculate the number of coins to return
    int coinsRet = calcNumCoins(round(dollars * 100));
    printf("%i\n", coinsRet);
}

int calcNumCoins(int cents)
{
    // Sorted list of supported coins
    int currency[4] = {25, 10, 5, 1};
    
    // Number of supported coins
    int numCoins = sizeof(currency) / sizeof(int);

    // Number of coins to return
    int coins = 0;
    
    // Loops over every supported coin
    for(int i = 0; i < numCoins; i++)
    {
        while (cents >= currency[i])
        {
            cents -= currency[i];
            coins++;
        }
        if (cents == 0)
        {
            return coins;
        }
    }
    // As long as we have a 1 cent in the supported coins, this will never be reached.
    // I had to put the explicit return to stop Clang from complaining
    return coins;
}
