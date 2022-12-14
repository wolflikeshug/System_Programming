/*
 *   CITS2002  Project 2  2022-sem2
 *   Student:  23006364   HU ZHUO   100
 */

#include "../inc/trove.h"

bool info = false;

// IF THE ARGUMENT IS NOT CORRECT, PRINT THE USAGE AND EXIT
void err_print(void)
{
    printf("%s\n%s\n\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
           "Usage:\t./trove [-f trove-file] [-b | -r | -u] [-l length] [-v] filelist",
           "or\t./trove [-f trove-file] word",
           "where options are",
           "-b\t\tbuild a new trove-file",
           "-f trove-file\tprovide the name of the trove-file to be built or searched",
           "-l length\tspecify the minimum-length of words added to the trove-file",
           "-r\t\tremove a trove-file",
           "-u\t\tupdate a trove-file",
           "-v\t\tadditional option to print details");
    exit(EXIT_FAILURE);
}

// BUILD FUNCTION
void build_trove(uint32_t argc, char *argv[], HASHTABLE_MLIST *hashtable)
{
    printf("\tTrove-File:\t%s\n\tWordlen limit:\t%d\n", TROVE_FILE, wordlen);
    printf("\t--------------------------Building--------------------------\n");
    hashtable = hashtable_mlist_new();
    for (; optind < argc; optind++)
    {
        recordWord(argv[optind], hashtable);
    }
    trovefile_write(hashtable);
    if (info)
    {
        printf("\tThe Trove File is now Containing:\n");
        printf("\t----------------------Trove File Detail----------------------\n");
        trovefile_print();
    }
    exit(EXIT_SUCCESS);
}

// REMOVE FUNCTION
void remove_func(uint32_t argc, char *argv[], HASHTABLE_MLIST *hashtable)
{
    if (access(TROVE_FILE, R_OK))
    {
        perror("Trove File");
        exit(EXIT_FAILURE);
    }
    printf("\tTrove-File:\t%s\n", TROVE_FILE);
    printf("\t--------------------------Removing--------------------------\n");
    hashtable = trovefile_load();
    for (; optind < argc; optind++)
    {
        if (!access(argv[optind], R_OK))
        {
            hashtable_mlist_remove(hashtable, argv[optind]);
        }
    }
    trovefile_write(hashtable);
    if (info)
    {
        printf("\tAfter Remove, The Trove File Containing:\n");
        printf("\t-------------------------Trove File-------------------------\n");
        trovefile_filename_print();
    }
    exit(EXIT_SUCCESS);
}

// UPDATE FUNCTION
void update_trove(uint32_t argc, char *argv[], HASHTABLE_MLIST *hashtable)
{
    if (access(TROVE_FILE, R_OK))
    {
        perror("Trove File");
        exit(EXIT_FAILURE);
    }
    printf("\tTrove-File:\t%s\n\tWordlen limit:\t%d\n", TROVE_FILE, wordlen);
    printf("\t--------------------------Updating--------------------------\n");
    hashtable = hashtable_mlist_new();
    for (; optind < argc; optind++)
    {
        recordWord(argv[optind], hashtable);
    }
    trovefile_update(hashtable);
    if (info)
    {
        printf("\tThe Trove File is now Containing:\n");
        printf("\t----------------------Trove File Detail----------------------\n");
        trovefile_print();
    }
    exit(EXIT_SUCCESS);
}

// SERACH FUNCTION
void search_func(uint32_t argc, char *argv[], HASHTABLE_MLIST *hashtable)
{
    if (access(TROVE_FILE, R_OK))
    {
        perror("Trove File");
        exit(EXIT_FAILURE);
    }
    printf("\tSearching...\n\tTrove File:\t%s\n\tTarget Word:\t\"%s\"\n", TROVE_FILE, argv[argc - 1]);
    printf("\t-----------------------SEARCH RESULT------------------------\n");
    hashtable = trovefile_load();
    hashtable_mlist_files_have_word_print(hashtable, argv[argc - 1]);
    trovefile_write(hashtable);
    exit(EXIT_SUCCESS);
}

int32_t main(int32_t argc, char *argv[])
{
    uint32_t result;
    uint16_t argc_cor = 2;
    uint16_t function = 0; // 0: search 1: build, 2: remove, 3: update

    HASHTABLE_MLIST *hashtable = hashtable_mlist_new();
    char *cmd = "ulimit -n 2048\n";
    system(cmd);

    while ((result = getopt(argc, argv, "f:brul:v")) != -1)
    {
        switch (result)
        {
        case 'f':

            change_trove_file(optarg);
            argc_cor += 2;
            break;

        case 'l':

            if (!isInt(optarg) || atoi(optarg) < 1) // if the length is not a positive integer or larger than 255
            {
                err_print();
            }
            change_wordlen(atoi(optarg));
            argc_cor += 2;
            if (function == 0)
            {
                function = 4; // 4: not allow search and remove, if -l argument is used
            }
            break;

        case 'b':

            if ((function && function != 4) || argc <= argc_cor++)
            {
                err_print();
            }
            function = 1; // 1: build
            break;

        case 'r':

            if ((function && function != 4) || argc <= argc_cor++)
            {
                err_print();
            }
            function = 2; // 2: remove
            break;

        case 'u':

            if ((function && function != 4) || argc <= argc_cor++)
            {
                err_print();
            }
            function = 3; // 3: update
            break;

        case 'v':

            argc_cor++;
            info = true;
            break;

        default:
            err_print();
        }
    }

    if (argc == argc_cor && !function && !info) // SEARCH FUNCTION
    {
        if (!isString(argv[argc - 1]))
        {
            err_print();
        }
        search_func(argc, argv, hashtable);
    }
    else if (function == 1) // BUILD FUNCTION
    {
        build_trove(argc, argv, hashtable);
    }
    else if (function == 2) // REMOVE FUNCTION
    {
        remove_func(argc, argv, hashtable);
    }
    else if (function == 3) // UPDATE FUNCTION
    {
        update_trove(argc, argv, hashtable);
    }

    err_print();
    return 1;
}