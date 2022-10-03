ALL	= testlist testhashtable

CC	= cc -std=c99 -Wall -Werror


all:	$(ALL)

testlist: list.h testlist.c list.c support.c
	$(CC) -o testlist testlist.c list.c support.c

testhashtable: hashtable.h testhashtable.c hashtable.c list.h list.c support.c
	$(CC) -o testhashtable testhashtable.c hashtable.c list.c support.c


compare: $(ALL)
	@./compare.sh
	
plot: $(ALL)
	@echo this may take 30seconds...
	@./plot-to-html.sh
	@echo 'now open  plot.html  in your browser'


clean:
	rm -f $(ALL) col? stats.* plot.html
