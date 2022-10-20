#  CITS2002 Project 2 2022
#  Student:   23006364   HU   ZHUO   100

CC	= gcc -std=c99 -Wall -Werror -lpthread

trove: 	src/tools.c inc/tools.h \
		src/list.c inc/list.h \
		src/hashtable_list.c inc/hashtable_list.h \
		src/mlist.c inc/mlist.h \
		src/hashtable_mlist.c inc/hashtable_mlist.h \
		src/trovefileIO.c inc/trovefileIO.h \
		src/wordFileIO.c inc/wordFileIO.h \
		src/trove.c inc/trove.h
	$(CC) -c src/tools.c 
	$(CC) -c src/list.c 
	$(CC) -c src/hashtable_list.c 
	$(CC) -c src/mlist.c 
	$(CC) -c src/hashtable_mlist.c 
	$(CC) -c src/trovefileIO.c 
	$(CC) -c src/wordFileIO.c 
	$(CC) -c src/trove.c 
	$(CC) -o trove tools.o list.o hashtable_list.o mlist.o hashtable_mlist.o trovefileIO.o wordFileIO.o trove.o
	rm -f *.o

clean:
	rm -f trove
	rm -f /tmp/trove