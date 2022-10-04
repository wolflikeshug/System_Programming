CC	= gcc -std=c99 -Wall -Werror

trove: 	fileIO/datastruct/tools.c fileIO/datastruct/tools.h \
		fileIO/datastruct/list.c fileIO/datastruct/list.h \
		fileIO/datastruct/hashtable_list.c fileIO/datastruct/hashtable_list.h \
		fileIO/datastruct/mlist.c fileIO/datastruct/mlist.h \
		fileIO/datastruct/hashtable_mlist.c fileIO/datastruct/hashtable_mlist.h \
		fileIO/indexfileIO.c fileIO/indexfileIO.h \
		fileIO/wordFileIO.c fileIO/wordFileIO.h \
		trove.c trove.h
	$(CC) -o trove fileIO/datastruct/tools.c fileIO/datastruct/list.c fileIO/datastruct/hashtable_list.c fileIO/datastruct/mlist.c fileIO/datastruct/hashtable_mlist.c fileIO/indexfileIO.c fileIO/wordFileIO.c trove.c 

clean:
	rm -f trove