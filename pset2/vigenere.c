#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    string phrase;
    string key = argv[1];
        
    if (argc != 2) {
        printf("You forgot to enter an argument!\n");
        return 1;
    }

    else {   
        for (int i=0; i < strlen(key); i++)
        {
          if (!isalpha(key[i])) {
            printf("You key must be a string!!\n");
            return 1;
          }
        }
        
        phrase = GetString();
        
        for (int i = 0, k = 0, pLen = strlen(phrase); i < pLen; i++)
          {
            int keyOffset = tolower(key[k%strlen(key)])-97;
            
            if islower(phrase[i])
            {
                printf("%c", (phrase[i]-97+keyOffset)%26+97);
                k++;
            }
            else if isupper(phrase[i])
            {
                printf("%c", (phrase[i]-65+keyOffset)%26+65);
                k++;
            }
            else if (ispunct(phrase[i]) || isblank(phrase[i]))
            {
              printf("%c", phrase[i]);
            }
          }
    }
    printf("\n");
}
