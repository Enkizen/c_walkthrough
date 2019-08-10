/* This c file walks through the concept of 
retrieving the JPEG files from mememory if it is deleted.*/

/*Let's start from research of a few key ideas

What is delete? 

Windows (and other operating systems) keep track of where files are on a hard drive through “pointers.” 
Each file and folder on your hard disk has a pointer that tells Windows where the file’s data begins and ends.

When you delete a file, Windows removes the pointer and marks the sectors containing the file’s data as available. 
From the file system’s point of view, the file is no longer present on your hard drive and the sectors 
containing its data are considered free space.

However, until Windows actually writes new data over the sectors containing the contents of the file, 
the file is still recoverable. A file recovery program can scan a hard drive for these deleted files and restore them. 
If the file has been partially overwritten, the file recovery program can only recover part of the data.

If you’re wondering why your computer doesn’t just erase files when you delete them, 
it’s actually pretty simple. Deleting a file’s pointer and marking its space as available is an extremely fast operation. 
In contrast, actually erasing a file by overwriting its data takes significantly longer. 
For example, if you’re deleting a 10 GB file, that would be near-instantaneous. 
To actually erase the file’s contents, it may take several minutes – 
just as long as if you were writing 10 gigabytes of data to your hard drive.

To increase performance and save time, Windows and other operating systems don’t erase a file’s contents when it’s deleted.

So to summarise:

Windows removes the pointer and mark the sectors instead of overwriting with 0s then free up the pointer when you recycle in bin.

*/


/* Does the Filesystem affects the deletion? 
   A file system is a piece of software that controls how data on a media is stored and retrieved. 
   A file system manages operations such as copying, moving, and deleting files on a drive.
   
   Types:
   NTFS NT File System
   
   FAT32 /exFAT
   
   HFS+ Herarchical File System 
       
   EXT 2, 3 and 4 
   
   Yes. This assumes FAT first before dealing with other cases.
*/
#include <stdio.h>
#include <stdlib.h>


#define BLOCK_SIZE 512 //since FAT comes in blocks of 512



int main(int argc, char *argv[]) //argc number of items inputted. default main structure.
//argv act like string array   
int size_Char = sizeof( unsigned char );

{
    if (argc != 2)//[0] should be the command to run this. [1] should be the file to recover.
    {
        fprintf(stderr, "Let us input the file 1 at a time first\n"); //output error message
        return 1;
    }
   
   // remember filename to recover
    char *infile = argv[1];

    // open input file and get a pointer for read
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
   
    unsigned char* buffer[BLOCK_SIZE]= malloc( size_Char * BLOCK_SIZE );
    int imageCount = 0;//initialize image count
    char filename[8];
    FILE *outptr = NULL;

    
   while (1)
    {
        // read a block of the memory card image
        //size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
        size_t bytesRead = fread(buffer, sizeof(buffer), BLOCK_SIZE, inptr); //size_t is an unsigned integral data type which is defined in various header files

        // break out of the while loop when we reach the end of the card image
        if (bytesRead == 0 && feof(inptr))
        {
            break;
        }

        // check if we found a JPEG using beginning signature of a jpeg file
        if( buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0){

            // if we found a yet another JPEG, we must close the previous file
            if (outptr != NULL)
            {
               fclose(outptr);
               imageCount++;
            }

            // if we found a JPEG, we need to open the file for writing

               sprintf(filename, "%03i.jpg", imageCount+1); //i dont like to start with 0
               outptr = fopen(filename, "w");
            

            // write anytime we have an open file
            if (outptr != NULL)
            {
               fwrite(buffer, sizeof(char*), bytesRead, outptr);
            }
        } 
   }  
    // close last jpeg file
    fclose(outptr);

    // close infile
    fclose(inptr);
    
    
    //free
    free(buffer);
    
    // success
    return 0;
   



}
