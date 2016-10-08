#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // get amount from user
    float changeNeeded;
    do {
        printf("O hai! How much change is owed?\n");
        changeNeeded = GetFloat();
    }
    
    // make sure it's over zero
    while (changeNeeded <= 0);
    
    int amount = round(changeNeeded * 100);
    int count = 0;
    
    count += amount / 25;
    amount = amount % 25;

    count += amount / 10;
    amount = amount % 10;

    count += amount / 5;
    amount = amount % 5;

    count += amount / 1;

    printf("%d\n", count);
}