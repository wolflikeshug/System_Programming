#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include "test.h"

int main(int argc, char *argv[])
{
    HASHTABLE_MLIST *hashtable_mlist = hashtable_mlist_new();
    FILE *fp = fopen("text.txt", "r");

    recordWord(fp, "text.txt", hashtable_mlist);
    hashtable_mlist_print(hashtable_mlist);
    fclose(fp);
    return 0;
}
