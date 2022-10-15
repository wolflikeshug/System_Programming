//  CITS2002 Project 2 2022
//  Student:   23006364   HU   ZHUO   100

#include "trove.h"

// IF THE ARGUMENT IS NOT CORRECT, PRINT THE USAGE AND EXIT
void err_print(void)
{
    printf("%s\n%s\n\n%s\n%s\n%s\n%s\n%s\n%s\n",
           "Usage:\t./trove [-f filename] [-b | -r | -u] [-l length] filelist",
           "or\t./trove [-f filename] word",
           "where options are",
           "-b\t\tbuild a new trove-file",
           "-f filename\tprovide the name of the trove-file to be built or searched",
           "-l length\tspecify the minimum-length of words added to the trove-file",
           "-r\t\tremove a trove-file",
           "-u\t\tupdate a trove-file");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int result;
    int argc_cor = 2;
    int function = 0;           // 0: default 1: build, 2: remove, 3: update

    HASHTABLE_MLIST *hashtable = hashtable_mlist_new();

    while ((result = getopt(argc, argv, "f:brul:")) != -1 && function == 0)
    {
        switch (result)
        {
        case 'f':

            change_trove_file(optarg);
            argc_cor += 2;
            break;

        case 'l':

            if (!isInt(optarg) || atoi(optarg) < 1)
            {
                printf("Invalid length value\n");
                exit(EXIT_FAILURE);
            }
            change_wordlen(atoi(optarg));
            argc_cor += 2;
            break;

        case 'b':

            if (argc > argc_cor++)
            {
                function = 1;
            }
            break;

        case 'r':

            if (argc > argc_cor++)
            {
                function = 2;
            }
            break;

        case 'u':

            if (argc > argc_cor++)
            {
                function = 3;
            }
            break;
        }
    }

    if (function == 1)                  // BUILD FUNCTION
    {
        printf("\nBuilding:\t%s\n", TROVE_FILE);
        printf("--------------------------Building--------------------------\n");
        hashtable = hashtable_mlist_new();
        for (; optind < argc; optind++)
        {
            recordWord(argv[optind], hashtable);
        }
        trovefile_write(hashtable);
        printf("\nThe Trove File is now Containing:\n");
        printf("----------------------Trove File Detail----------------------\n");
        trovefile_print();
        exit(EXIT_SUCCESS);
    }
    else if (function == 2)             // REMOVE FUNCTION
    {
        printf("\nRemoving From:\t%s\n", TROVE_FILE);
        printf("--------------------------Removing--------------------------\n");
        hashtable = trovefile_load();
        for (; optind < argc; optind++)
        {
            if (isFile(argv[optind]))
            {
                hashtable_mlist_remove(hashtable, argv[optind]);
            }
        }
        trovefile_write(hashtable);
        printf("\nAfter Remove, The Trove File Containing:\n");
        printf("-------------------------Trove File-------------------------\n");
        trovefile_filename_print();
        exit(EXIT_SUCCESS);
    }
    else if (function == 3)             // UPDATE FUNCTION
    {
        printf("\nUpdating:\t%s\n", TROVE_FILE);
        printf("--------------------------Updating--------------------------\n");
        hashtable = hashtable_mlist_new();
        for (; optind < argc; optind++)
        {
            if (isFile(argv[optind]))
            {
                recordWord(argv[optind], hashtable);
            }
        }
        trovefile_update(hashtable);
        exit(EXIT_SUCCESS);
    }
    else if (argc == argc_cor)          // SEARCH FUNCTION
    {
        printf("\nSearching...\nTarget Word:\t\t\"%s\"\nUsing Trove File:\t%s\n", argv[argc - 1], TROVE_FILE);
        printf("--------------------------RESULT----------------------------\n");
        hashtable = trovefile_load();
        hashtable_mlist_files_have_word_print(hashtable, argv[argc - 1]);
        exit(EXIT_SUCCESS);
    }

    err_print();
    return 1;
}