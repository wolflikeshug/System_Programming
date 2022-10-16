# Trove Program

Program Trove provides a similar function to Spotlight indexing the contents of files.

Trove makes it easier to search for certain words from a list of files.

## Features:

- Indexing a list of files
- Update the Index File with a list of files
- Remove certain files from the Index file
- Searching the word from Index File
- Change the limitation of word length

## Building:

```
sudo apt install build-essential

make
```

## Test:

```
make test
```

## Executing:

1.  

   ```
   prompt.1> ./trove [-f trovefile]  word
   ```

   The first invocation requests *trove* to list the *absolute pathname* of files containing the indicated word. Filenames are simply listed one-per-line (their order is not important).

   If any file does not exist at the time of the search (it may have been deleted since the trove-file was built), then the file is *not* listed.

   If any files containing the requested word are found, then *trove* will exit with success; otherwise with failure.

   

2.  

   ```
   prompt.2> ./trove [-f trovefile] [-b | -r | -u] [-l length]  filelist
   ```

   The second invocation requests *trove* to build a new index, to remove information from an existing index, **or** to update an existing index.

   A *filelist* is a sequence of one-or-more filenames or directory names. The contents of each named file should be indexed, and each named directory (and its subdirectories) should be traversed to locate files to be indexed.

   Note that the files do not have to be text-files - they could equally be, for example, executable programs or object files.

   If the requested action can be performed successfully, then *trove* will exit with success; otherwise with failure.



### The following command-line options are to be supported:

-b					build a new trove-file from the contents of a *filelist*. The new trove-file will replace an existing trove-file of the same name.

-f *trovefile*        provide the name of the trove-file to be built or searched. If the -f option is not provided, the default name of the trove-file is **/tmp/trove**

-l *length*		   only words of at least the indicated length should be added to the trove-file. *length* must be a positive integer, for example: *-l 6*.  If the -l option is 						not provided, the default length is **4**.

-r					 if any of the files from the *filelist* appear in the trove-file, remove all of their information from the trove-file.

-u					update the trove-file with the contents of all files in the *filelist*. If the information from any of the files already exists in the trove-file, then that (old) 					    information is first removed.