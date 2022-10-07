CC	= gcc -std=c99 -Wall -Werror

trove: 	fileIO/datastruct/tools.c fileIO/datastruct/tools.h \
		fileIO/datastruct/list.c fileIO/datastruct/list.h \
		fileIO/datastruct/hashtable_list.c fileIO/datastruct/hashtable_list.h \
		fileIO/datastruct/mlist.c fileIO/datastruct/mlist.h \
		fileIO/datastruct/hashtable_mlist.c fileIO/datastruct/hashtable_mlist.h \
		fileIO/trovefileIO.c fileIO/trovefileIO.h \
		fileIO/wordFileIO.c fileIO/wordFileIO.h \
		trove.c trove.h
	$(CC) -c fileIO/datastruct/tools.c 
	$(CC) -c fileIO/datastruct/list.c 
	$(CC) -c fileIO/datastruct/hashtable_list.c 
	$(CC) -c fileIO/datastruct/mlist.c 
	$(CC) -c fileIO/datastruct/hashtable_mlist.c 
	$(CC) -c fileIO/trovefileIO.c 
	$(CC) -c fileIO/wordFileIO.c 
	$(CC) -c trove.c 
	$(CC) -o trove tools.o list.o hashtable_list.o mlist.o hashtable_mlist.o trovefileIO.o wordFileIO.o trove.o
	rm -f *.o

test:	fileIO/datastruct/tools.c fileIO/datastruct/tools.h \
		fileIO/datastruct/list.c fileIO/datastruct/list.h \
		fileIO/datastruct/hashtable_list.c fileIO/datastruct/hashtable_list.h \
		fileIO/datastruct/mlist.c fileIO/datastruct/mlist.h \
		fileIO/datastruct/hashtable_mlist.c fileIO/datastruct/hashtable_mlist.h \
		fileIO/trovefileIO.c fileIO/trovefileIO.h \
		fileIO/wordFileIO.c fileIO/wordFileIO.h \
		test.c test.h
	$(CC) -c fileIO/datastruct/tools.c 
	$(CC) -c fileIO/datastruct/list.c 
	$(CC) -c fileIO/datastruct/hashtable_list.c 
	$(CC) -c fileIO/datastruct/mlist.c 
	$(CC) -c fileIO/datastruct/hashtable_mlist.c 
	$(CC) -c fileIO/trovefileIO.c 
	$(CC) -c fileIO/wordFileIO.c 
	$(CC) -c test.c
	$(CC) -o test test.o tools.o list.o hashtable_list.o mlist.o hashtable_mlist.o trovefileIO.o wordFileIO.o
	rm -f *.o

clean:
	rm -f trove
	rm -f *.o