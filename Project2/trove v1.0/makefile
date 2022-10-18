#  CITS2002 Project 2 2022
#  Student:   23006364   HU   ZHUO   100

CC	= gcc -std=c99 -Wall -Werror

trove: 	src/dataStruct/tools.c src/dataStruct/tools.h \
		src/dataStruct/list.c src/dataStruct/list.h \
		src/dataStruct/hashtable_list.c src/dataStruct/hashtable_list.h \
		src/dataStruct/mlist.c src/dataStruct/mlist.h \
		src/dataStruct/hashtable_mlist.c src/dataStruct/hashtable_mlist.h \
		src/fileIO/trovefileIO.c src/fileIO/trovefileIO.h \
		src/fileIO/wordFileIO.c src/fileIO/wordFileIO.h \
		src/trove.c src/trove.h
	$(CC) -c src/dataStruct/tools.c 
	$(CC) -c src/dataStruct/list.c 
	$(CC) -c src/dataStruct/hashtable_list.c 
	$(CC) -c src/dataStruct/mlist.c 
	$(CC) -c src/dataStruct/hashtable_mlist.c 
	$(CC) -c src/fileIO/trovefileIO.c 
	$(CC) -c src/fileIO/wordFileIO.c 
	$(CC) -c src/trove.c 
	$(CC) -o trove tools.o list.o hashtable_list.o mlist.o hashtable_mlist.o trovefileIO.o wordFileIO.o trove.o
	rm -f *.o

clean:
	rm -f trove
	rm -f /tmp/trove