#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    do 
    {
        printf("Height: ");
        height = GetInt();
    }

    while (height < 0 || height > 23);

    if (height == 0)
    {
        exit(0);
    }
    
    else 
    {
        for (int row=0; row<height; row++) 
        {   
            for (int space=height-1; space>row; space--)
            {
                printf(" ");
            }
    
            for (int hash=0; hash<row+2; hash++)
            {
                printf("#");
            }
            
            printf("\n");
    
        }
    }

}