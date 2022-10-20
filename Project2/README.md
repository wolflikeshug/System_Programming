# Trove Program

[TOC]



## The following packages are required to build and run this project:

1. build-essential (I believe you have already installed this)

2. md5sum (This is required to check if the file has been modified after the trove-file has been built or updated)

3. manpages-posix-dev (If you see the following error message while making v2.0, it is recommended to install this package to solve the problem)

   ```shell
   $ make
   gcc -std=c99 -Wall -Werror -lpthread -c src/tools.c
   gcc -std=c99 -Wall -Werror -lpthread -c src/list.c
   gcc -std=c99 -Wall -Werror -lpthread -c src/hashtable_list.c
   gcc -std=c99 -Wall -Werror -lpthread -c src/mlist.c
   gcc -std=c99 -Wall -Werror -lpthread -c src/hashtable_mlist.c
   gcc -std=c99 -Wall -Werror -lpthread -c src/trovefileIO.c
   gcc -std=c99 -Wall -Werror -lpthread -c src/wordFileIO.c
   gcc -std=c99 -Wall -Werror -lpthread -c src/trove.c
   gcc -std=c99 -Wall -Werror -lpthread -o trove tools.o list.o hashtable_list.o mlist.o hashtable_mlist.o trovefileIO.o wordFileIO.o trove.o
   /usr/bin/ld: wordFileIO.o: in function `recordWord_dir':
   wordFileIO.c:(.text+0x491): undefined reference to `pthread_create'
   collect2: error: ld returned 1 exit status
   make: *** [makefile:22: trove] Error 1
   ```

   

You can install all these by copying the following cmd to your shell (Ubuntu or any other Debian based system):

```shell
sudo apt-get install build-essential md5sum manpages-posix-dev
```

# Version Feature:

## v 2.0

- mostly built based on v1.0
  
- Introduced multi-threads to boost the speed of the Build / Update Function of the program 
  - (save about 50% time, works especially well with a large number of files, depends on the machine you are running)
  - (Warning: This version has Potential FLAWS. Please read the README.md instruction of v2.0 to get more info. if this program frequently crashes on the test machine, For stability reasons, I suggest using v1.0 for the automation test.)

- improve the reading speed of trove-file, this will speed up the program overall ( a little bit :) )
- introducing access() to check the file's state.
- enlarge the hashtable size to suit greater number of files and words.

## v 1.0

- Implement the basic functions that are listed in [Project Instruction](https://teaching.csse.uwa.edu.au/units/CITS2002/projects/project2.php)
- ADD -v function to print out debug info

# Make:

You  are able to make the version you wish by using the following cmd, Or jump to the directory of the version and use make directly to build the project!

```shell
make/make trove		 # default build v1.0 for automatic testing.
make 1.0			# build v1.0
make 2.0			# build v2.0
```

