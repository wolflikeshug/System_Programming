#define _POSIX_C_SOURCE 20089L
#define _GNU_SOURCE

#include "test.h"

int main(int argc, char *argv[])
{
    char *file1 = "The Last Night of the World.txt";
    char *file2 = "The Tell-Tale Heart";
    char *file3 = "The Yellow Wallpaper";
    char *file4 = "The Last Night of the World.bk";
    HASHTABLE_MLIST *hashtable_mlist = hashtable_mlist_new();
    recordWord(file1, hashtable_mlist);
    recordWord(file2, hashtable_mlist);
    recordWord(file3, hashtable_mlist);
    recordWord("test copy", hashtable_mlist);
    printf("%s\n", getRealPath("trove.c"));
    hashtable_mlist_print(hashtable_mlist);
    hashtable_mlist_have_key_print(hashtable_mlist, "scream");

    change_trove_file("/mnt/c/Users/zhong/Documents/GitHub/System_Programming/Project2/trovefile");
    char cmd[100];
    FILE *sh;
    char buffer[80];
    strcpy(cmd, "gzip '");
    strcat(cmd, file4);
    strcat(cmd, "'");
    strcpy(cmd, "zcat '");
    strcat(cmd, file4);
    strcat(cmd, ".gz'");
    sh = popen(cmd, "r");
    fgets(buffer, sizeof(buffer), sh);
    pclose(sh);
    printf("haha %s haha", buffer);
    return 0;
}
