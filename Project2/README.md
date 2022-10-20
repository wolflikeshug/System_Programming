# Trove Program

[TOC]



## The following packages are required to build and run this project:

1. build-essential (I believe you have already installed this)

2. md5sum (This is required to check if the file has been modified after the trove-file has been built or updated)

3. manpages-posix-dev (If you see the following error message while making v2.0, it is recommended to install this package to solve the problem)

   ```shell
   /usr/bin/ld: wordFileIO.o: in function `recordWord_dir':
   wordFileIO.c:(.text+0x491): undefined reference to `pthread_create'
   collect2: error: ld returned 1 exit status
   make: *** [makefile:22: trove] Error 1
   ```
   

You can install all these packages by copying the following cmd to your shell (Ubuntu or any other Debian based system):

```shell
sudo apt-get install build-essential md5sum manpages-posix-dev
```

# Version Feature:

## v 2.0

**(Warning: This version has Potential FLAWS. Please read  v2.0's README file to get more info. if this program frequently crashes during automation tests, For stability and my grade's reason, use v1.0 for the automation test. But still, I wish to let v2.0 have a try, it performs well on my machine for most of the cases, and only crashes when I ask it to deal with some extremes tests)**

- built based on v1.0
- Introduced multi-threads to boost the speed of the Build / Update Function of the program 
  - (save about 50% time, works especially well with a large number of files, depends on the machine you are running)
- Upgrade the method to read from file, this will speed up the program overall ( a little bit :) )
- Enlarge the hashtable size to suit a greater number of files and words.

## v 1.0

- Implement the basic functions that are listed in [Project Instruction](https://teaching.csse.uwa.edu.au/units/CITS2002/projects/project2.php)
- ADD -v function to print out debug info

# Make:

You are able to make the version you wish by using the following cmd, Or jump to the directory of the version and use make directly to build the project!

```shell
make / make trove	 # default build v2.0.
make 1.0			# build v1.0
make 2.0			# build v2.0
```

