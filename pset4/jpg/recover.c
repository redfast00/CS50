/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

// JPEG constants
#define JPEG_MAGIC_0 0xff
#define JPEG_MAGIC_1 0xd8
#define JPEG_MAGIC_2 0xff
#define JPEG_MAGIC_3 0xe0

// constants
#define CARD_FILENAME "card.raw"
#define LEFTOVER_FILENAME "leftover.raw"
#define BLOCK_SIZE 512

// errors
#define ERR_CARDFILE_OPEN 1
#define ERR_LEFTOVER_OPEN 2
#define ERR_READ 3

// funtions
bool isJPEGHeader(BYTE block[BLOCK_SIZE]);
FILE* openPhoto(int index);

int main(int argc, char* argv[])
{
    FILE* cardfile = fopen(CARD_FILENAME, "r");
    if (cardfile == NULL)
    {
        printf("Error while opening %s\n", CARD_FILENAME);
        return ERR_CARDFILE_OPEN;
    }
    int index = 0;
    
    // the blocks before the first valid JPEG signature get saved in this file
    FILE* photo = fopen(LEFTOVER_FILENAME, "w");
    
    // check for errors while opening LEFTOVER_FILENAME
    if (photo == NULL)
    {
        printf("Error while opening %s\n", LEFTOVER_FILENAME);
        return ERR_LEFTOVER_OPEN;
    }
    
    // main loop: reads disk image block by block
    while (true)
    {
        BYTE block[BLOCK_SIZE];
        int read_elements = fread(block, sizeof(BYTE), BLOCK_SIZE, cardfile);
        
        // If the block begins with the JPEG magic values,
        // the previous photo file gets closed, a new photo file gets opened and
        // the index gets bumped up by one
        if (isJPEGHeader(block))
        {
            fclose(photo);
            photo = openPhoto(index);
            index++;
        }
        
        // Check if we read all BLOCK_SIZE bytes
        if (read_elements)
        {
            // Block gets copied over to the photo file
            fwrite(block, sizeof(BYTE), read_elements, photo);
        }
        // For some reason, we didn't read all BLOCK_SIZE bytes
        else
        {
            // Check if the reason is that we encountered an EOF
            bool eof = feof(cardfile);
            
            // Close files since the program is going to halt anyway
            fclose(cardfile);
            fclose(photo);
            if (eof)
            {
                // Read whole card and encountered an EOF
                return 0;
            }
            else
            {
                // Didn't read all BLOCK_SIZE bytes and didn't EOF,
                // so there must be an IO error
                printf("Error while reading %s\n", CARD_FILENAME);
                return ERR_READ;
            }
        }
    }
    return 0;
}

bool isJPEGHeader(BYTE block[BLOCK_SIZE])
{
    // Checks if first three bytes match
    // Checks if first nibble of fourth byte matches using binary AND
    // (Bitmasking technique)
    if 
    (
        block[0] == JPEG_MAGIC_0 && block[1] == JPEG_MAGIC_1 && 
        block[2] == JPEG_MAGIC_2 && (block[3] & 0xf0) == JPEG_MAGIC_3
        )
    {
        return true;
    }
    return false;
}

FILE* openPhoto(int index)
{
    char photo_filename[8];
    sprintf(photo_filename, "%03d.jpg", index);
    FILE* photo = fopen(photo_filename, "w");
    return photo;
}