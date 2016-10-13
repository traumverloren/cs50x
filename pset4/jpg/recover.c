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

// define a block size constant
static const int BLOCK_SIZE = 512;

// uint8_t is 8 bits = 1 BYTE
typedef uint8_t BYTE;

int main(void)
{
    FILE* file = fopen("card.raw", "r");
    
    if (file == NULL)
    {
        printf("File does not exist.\n");
        return 1;
    }
    
    FILE* image = NULL;
    
    int count = 0;
    
    // create a array to store the 512 bytes in FAT block size
    // uint8_t is 8 bits = 1 BYTE, so this array is 512 bytes long
    BYTE block[BLOCK_SIZE];
    
    // // read 512 bytes until EOF reached
    // while(!feof(file))
    while (fread(&block, BLOCK_SIZE, 1, file) == 1)
    {
        // check if the FAT 512 block starts with a JPEG header
        if (block[0]== 0xff && block[1]== 0xd8 && block[2]== 0xff && (block[3] == 0xe0 || block[3] == 0xe1))
        {
            // Generate a new incremental filename
            char title[8];
            sprintf(title, "%03d.jpg", count);
    
            // close if JPEG file is open
            if (image != NULL) 
            {
              fclose(image);
            }
    
            // open new empty file
            image = fopen(title, "w");
    
            // Write the block to new jpg file
            fwrite(&block, BLOCK_SIZE, 1, image);
            
            // Increment the filename number
            count ++;
         }
         
         // if no jpg signature at the beginning of the block,
         // keep writing the image to the open file
         else if (image != NULL)
         {
            // Write the block to JPEG file
            fwrite(&block, BLOCK_SIZE, 1, image);
         }
      }

    // close the card file
    fclose(file);
  
    // close the image file
    fclose(image);
    
    // that's all folks
    return 0;
}
