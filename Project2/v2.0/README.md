# Trove Program v2.0

Program Trove provides a similar function to Spotlight indexing the contents of files.

Trove makes it easier to search for certain words from a list of files.

[TOC]



## Features:

- Indexing a list of files
- Update the Index File with a list of files
- Remove certain files from the Index file
- Searching the word from Index File
- Change the limitation of word length
- Multi-thread

## Building

```shell
make / make trove
```

## Executing

1.  

   ```shell
   ./trove [-f trovefile]  word
   ```

   If any file does not exist at the time of the search (it may have been deleted since the trove-file was built), then the file is *not* listed.

   If any files containing the requested word are found, then *trove* will exit with success; otherwise with failure.

   

2.  

   ```shell
   ./trove [-f trovefile] [-b | -r | -u] [-l length]  filelist
   ```

   A *filelist* is a sequence of one-or-more filenames or directory names. The contents of each named file should be indexed, and each named directory (and its subdirectories) should be traversed to locate files to be indexed.

   If the requested action can be performed successfully, then the *trove* will exit with success; otherwise with failure.

## The following command-line options are supported

------

| Command | Explanation |
| ------------ | ------------------------------------------------------------ |
| -b           | build a new trove-file from the contents of a *filelist*. The new trove-file will replace an existing trove-file of the same name. |
| -f trovefile | provides the name of the trove-file to be built or searched. If the -f option is not provided, the default name of the trove-file is **/tmp/trove** |
| -l length    | only words of at least the indicated length should be added to the trove-file. *length* must be a positive integer (not greater than 65535), for example: *-l 6*.  If the -l option is not provided, the default length is **4**. |
| -r           | if any of the files from the *filelist* appear in the trove-file, remove all of their information from the trove-file. |
| -u           | update the trove-file with the contents of all files in the *filelist*. If the information from any of the files already exists in the trove-file, then that (old) information is first removed. |
| -v | if you only use this argument, the program will return an error, print more information about trove-file after operations making any changes to trove-file (it disabled searching function just like -l did) |

## Notes  (Strongly Suggest Reading This before marking)

- Although optimized, the program inevitably sacrifices stability while improving the speed of reading words from files. When using it, you should try to avoid putting a directory containing multiple files of tens of megabytes into the file-list. In that case, you should enter the file name of the file inside the directory into the file-list separately.

- 

- Please set up the environment for this project before building and running, The following packages are required to run this project:
  
  1. build-essential (I believe you have already installed this)
  2. md5sum (This is required to check if the file has been modified after the trove-file has been built or updated)
  
- Do not put the trove program file or any other opened file (or the directory containing these) into the file list while updating or building, The program will not be able to read from these files. Any attempt to build or update the trove-file using those will fail. The program will return an error and terminate without making any changes to trove-file.

- Although the build and update function accepts a directory as input for the file list, the remove function does not support a directory as input. You can remove all the files under a certain directory using the * sign (but it wouldn't remove the files under the subdirectory of it)

- Please notice that files that are deleted or modified since the trove-file was built or updated, will be permanently removed from trove-file the next time you use the trove program. And this removal will not be resumed even if the deletion or changes made to these files are revocated. You will need to rebuild or update the trove-file to reinclude those files back into the trove-file( index file ) and make it rebecome searchable.

- There is a new argument 'v' added to the program, which is not required in the project outline. But I found it will make the terminal looks messy if the program always prints out the debug info, so this argument has been introduced to allow print information about trove-file after the user makes any changes to trove-file and if you don't use this argument those debug info will not show up. This is mainly used during debugging, but it would be helpful if you want to quickly find out what changes are made to the trove-file after operations like 'building'. Please notice this argument also disables the search function.

- You may find that in my source files, there is no int type variable, instead they are replaced by many uint_t. In fact in the previous version of my work int is often used instead of uint_t, but if trove file records a huge file, the total length of the words recorded from that file gets greater than 2147483647(2^31-1), my program will crash, and pop up segment fault. So it recalls me to use various data types for different situations instead of just using int for everything. But unsigned short, int, unsigned int,  long long... there are too many names, Therefore I include stdint.h to give them a uniform format.

- The trove program using PATH_MAX which is the POSIX equivalent for Microsoft's MAX_PATH, includes 255 characters plus one for a terminating NUL.

- Although I used malloc and realloc to implement dynamic memory control of my program, I cannot help to notice that the efficiency of this technic is very slow, especially when I dynamically allocate memory one letter by one for each word, the program will spend minutes to read a 10MByte file.

  

