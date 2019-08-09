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

Windows removes the pointer and mark the sectors instead of overwriting with 0s when you recycle in bin.

*/


/* Does the Filesystem affects the deletion? 
   A file system is a piece of software that controls how data on a media is stored and retrieved. 
   A file system manages operations such as copying, moving, and deleting files on a drive.
   
   Types:
   NTFS NT File System
   
   FAT32 /exFAT
   
   HFS+ Herarchical File System 
       
   EXT 2, 3 and 4 
     
*/
