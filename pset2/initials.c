#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string name = GetString();
    
    // loop through string and capitalize 1st letter and letter after space
    for (int i = 0, n = strlen(name); i < n; i++) 
    {
        if (i == 0 || isblank(name[i-1]))
            printf("%c", toupper(name[i]));
    }
    printf("\n");
}