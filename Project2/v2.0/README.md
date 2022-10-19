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

- Although optimized, the program inevitably sacrifices little stability while improving the speed of reading words from files (That is why adding multi-thread only has impacts on Building / Updating, because these function needs to read a large amount of files while Removing and Searching are just operating a single trove-file). While using it, you should try to avoid putting a directory containing multiple huge files into the file-list. In that case, you should enter the file name of the file inside the directory into the file-list separately. 
  - That is because each time reading a word file, the program will create a new thread and use fopen to read it directly. However, if the program runs too fast, it will soon reach the limit of open file at same time, and the fopen will return NULL pointer which will take as a failure of opening the file. 
  - This depends on the machine you are running, if you have an excellent machine that has extremely fast IO, there is no problem
  - At first, I use usleep() to slow the program down according to the size got from stat(), however stat() cannot get the real size of files that is larger than 8192 Bytes, so it will still cause problems when reading multiple large files under the same directory put in file-list. 
  - Then I tried to use popen("ls -l filenmae", "r") to get the real size of the file, but frequently IO to shell slows down the program way too much. Even without usleep(), the multi-threads version is slower than the mono-thread version!!!
  - so eventually I set the usleep(1000) to keep it stable for most of the files on my computer while being fast, But the drawback is obvious, this is a fixed setting, which means it may not be stable running on other machines.
  - if this program frequently crashes on the test machine, you can longer the time of usleep() in worFileIO.c to suit the test machine. Or for stability reasons, just use the mono-thread version for the automation test.

- Compare to v1.0, v2.0 upgrades the technic of reading words and Lines from files. (especially when reading trove-file). In the older version, for both word and line objects program uses malloc sizeof(char) * 1 and uses realloc to get one more size for every character got from the file. in v2.0, for word objects, the program uses calloc sizeof(char) * 20 to store it and for line object, the program uses calloc sizeof(char) * 1000 and will if the object need to get larger than that, v2.0 can also be dynamic and expands the memory using realloc().
