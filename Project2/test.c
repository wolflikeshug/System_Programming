#define _POSIX_C_SOURCE 20089L
#define _GNU_SOURCE

#include "test.h"

int main(int argc, char *argv[])
{
    char *file1 = "./testFile/The Last Night of the World.txt";
    char *file2 = "./testFile/The Tell-Tale Heart";
    char *file3 = "./testFile/The Yellow Wallpaper";
    char *file4 = "./testFile/The Last Night of the World.bk";
    char *file5 = "./testFile/The Black Cat";
    //char *fakefile = " ";
    HASHTABLE_MLIST *hashtable_mlist = hashtable_mlist_new();
    recordWord(file1, hashtable_mlist);
    recordWord(file2, hashtable_mlist);
    recordWord(file3, hashtable_mlist);
    recordWord(file4, hashtable_mlist);
    recordWord(file5, hashtable_mlist);
    //printf("%s\n", getRealPath(fakefile));

    change_trove_file("/mnt/c/Users/zhong/Documents/GitHub/System_Programming/Project2/new");
    trovefile_write(hashtable_mlist);
    return 0;
}
