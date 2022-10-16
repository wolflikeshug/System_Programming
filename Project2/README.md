# Trove Program

Program Trove provides a similar function to Spotlight indexing the contents of files.

Trove makes it easier to search for certain words from a list of files.

[TOC]



## Features:

- Indexing a list of files
- Update the Index File with a list of files
- Remove certain files from the Index file
- Searching the word from Index File
- Change the limitation of word length

## Building

```
make / make trove
```

## Executing

1.  

   ```
   prompt.1> ./trove [-f trovefile]  word
   ```

   If any file does not exist at the time of the search (it may have been deleted since the trove-file was built), then the file is *not* listed.

   If any files containing the requested word are found, then *trove* will exit with success; otherwise with failure.

   

2.  

   ```
   prompt.2> ./trove [-f trovefile] [-b | -r | -u] [-l length]  filelist
   ```

   A *filelist* is a sequence of one-or-more filenames or directory names. The contents of each named file should be indexed, and each named directory (and its subdirectories) should be traversed to locate files to be indexed.

   If the requested action can be performed successfully, then the *trove* will exit with success; otherwise with failure.

## The following command-line options are supported

------

| Command | Explanation |
| ------------ | ------------------------------------------------------------ |
| -b           | build a new trove-file from the contents of a *filelist*. The new trove-file will replace an existing trove-file of the same name. |
| -f trovefile | provides the name of the trove-file to be built or searched. If the -f option is not provided, the default name of the trove-file is **/tmp/trove** |
| -l length    | only words of at least the indicated length should be added to the trove-file. *length* must be a positive integer, for example: *-l 6*.  If the -l option is not provided, the default length is **4**. |
| -r           | if any of the files from the *filelist* appear in the trove-file, remove all of their information from the trove-file. |
| -u           | update the trove-file with the contents of all files in the *filelist*. If the information from any of the files already exists in the trove-file, then that (old) information is first removed. |

## Notes  (Strongly Suggest Reading This before you mark this work)

- Please set up the environment for this project before building and running, The following packages are required to run this project:
  1. build-essential (I believe you have already install this)
  2. md5sum (This is required to check if the file has been modified after the trove-file has been built or updated)
- Do not put the trove program file or any other opened file (or the directory containing these) into the file list while updating or building, The program will not be able to read from these files. Any attempt to build or update the trove-file using those will fail. The program will return an error and terminate without making any changes to trove-file.
- Although the build and update function accepts a directory as input for the file list, the remove function does not support directory as input. You can remove all the files under a certain directory using the * sign (but it wouldn't remove the files under the subdirectory of it)
- Please notice that files, have been deleted or modified since the trove-file was built or updated, will be removed from trove-file without noticing. And this removal will not be resumed even if those files or changes made to these files are resumed, you will need to rebuild or update the trove-file to include those files back into the trove-file( index file ) and make it become searchable again.

