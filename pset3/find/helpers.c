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

void bubbleSort();
bool binarySearch();
bool linearSearch();

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{

    if (value < 0)
        return false;
    else
    {
        return binarySearch(value, values, 0, n-1);
    }
}

bool binarySearch(int value, int values[], int firstIndex, int lastIndex)
{
    if (firstIndex <= lastIndex)
    {
        int middle = (firstIndex + lastIndex) / 2;
        if (value == values[middle])
            return true;
        else if (value < values[middle])
            return binarySearch(value, values, firstIndex, middle - 1);
        else
            return binarySearch(value, values, middle + 1, lastIndex);
    }
    return false;
}

bool linearSearch(int value, int values[], int n)
{
    for (int i=0; i<n; i++)
    {
        if (value == values[i])
        {
            return true;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    bubbleSort(values, n);
    return;
}

void bubbleSort(int values[], int n)
{
    // go through array n-1 times
    for (int i=0; i<(n-1); i++)
    {
        // compare each value to one next to it.
      for (int v=0; v<(n-1); v++)
      {
           
          if (values[v] > values[v+1])
          {
              int new_first = values[v+1];
              values[v+1] = values[v];
              values[v] = new_first;
          }
      } 
    }
}