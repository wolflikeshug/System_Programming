#define _POSIX_C_SOURCE 200809L

#include "wordFileIO.h"

// PUT THE WORD INTO HASHTABLE_LIST
void store_word(char *word, HASHTABLE_LIST *hashtable)
{
    hashtable_list_add(hashtable, word);
}

// RECORD ALL THE WORDS FROM FILE INTO THE HASHTABLE
void recordWord(FILE *fp, char *filename, HASHTABLE_MLIST *hashtable)
{
    char *word = (char *)malloc(sizeof(char) * 1);
    word[0] = '\0';
    char c = fgetc(fp);
    while (feof(fp))
    {
        if (stillWord(c))
        {
            word = (char *)realloc(word, sizeof(char) * (strlen(word) + 2));
            word[strlen(word) - 1] = c;
            word[strlen(word)] = '\0';
        }
        else
        {
            if (wordlen_check(word))
            {
                store_word(word, hashtable_mlist_filename_list(hashtable, filename));
            }
            word = (char *)malloc(sizeof(char) * 1);
            word[0] = '\0';
        }
        c = fgetc(fp);
    }
}

