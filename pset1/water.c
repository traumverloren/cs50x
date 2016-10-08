#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("minutes: ");
    int x = GetInt();
    float y =  (x * 1.5 * 128 / 16);
    printf("bottles: %1.f\n", y);
}