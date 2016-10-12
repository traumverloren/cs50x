/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdint.h>

// uint8_t is 8 bits = 1 BYTE
typedef uint8_t BYTE;

// define a block size constant
static const int BLOCK_SIZE = 512;

int main(void)
{
    FILE* file = fopen("card.raw", "r");
    
    if (file == NULL)
    {
        printf("File does not exist.\n");
        return 1;
    }
    
    FILE* image = NULL;
    
    // create a array to store the 512 bytes in FAT block size
    // uint8_t is 8 bits = 1 BYTE, so this array is 512 bytes long
    BYTE buffer[BLOCK_SIZE];
    
    int count = 0;
    
    // read 512 bytes until EOF reached
    while(!feof(file))
    {
      // read file in 512 byte blocks
      fread(buffer, 1, BLOCK_SIZE, file);
       
      // check if the block starts with a JPEG header
      if (buffer[0]== 0xff && buffer[1]== 0xd8 && buffer[2]== 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe0))
      {
          // Generate the file name
          char title[8];
          sprintf(title, "%03d.jpg", count);
  
          // close if JPEG file is open
          if (image != NULL) 
          {
            fclose(image);
          }
  
          // open file
          image = fopen(title, "w");
  
          // Write the block to JPEG file
          fwrite(buffer, BLOCK_SIZE, 1, image);
          
          // Increment the file number
          count ++;
       }
    }

    // close the card file
    fclose(file);
  
    // close the image file
    fclose(image);
    
    // that's all folks
    return 0;
    
}
