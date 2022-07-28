# make readfile.c rename it as readfile
readfile: readfile.c
	gcc readfile.c -o readfile;

CountSameFile: CountSameFile.c
	gcc CountSameFile.c -o CountSameFile;