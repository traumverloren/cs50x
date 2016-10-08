#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    string phrase;
    
    if (argc != 2)
    {
        printf("You forgot to enter an argument!\n");
        return 1;
    }
    else
    {   
        phrase = GetString();
    }

    int k = atoi(argv[1]);
    for (int i = 0, n = strlen(phrase); i < n; i++)
    {
        if islower(phrase[i])
        {
            printf("%c", (phrase[i]-97+k)%26+97);
        }
        else if isupper(phrase[i])
            printf("%c", (phrase[i]-65+k)%26+65);
        else if (ispunct(phrase[i]) || isblank(phrase[i]))
            printf("%c", phrase[i]);
    }
    printf("\n");
}
