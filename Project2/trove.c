#define _POSIX_C_SOURCE 20089L
#define _GNU_SOURCE

#include "trove.h"

int main(int argc, char *argv[])
{
    int result;
    bool end = false;
    bool build = true;
    bool remove = true;
    bool update = true;
    bool search = true;

    HASHTABLE_MLIST *hashtable = hashtable_mlist_new();

    while ((result = getopt(argc, argv, "f:brul:")) != -1 && !end)
    {
        switch (result)
        {
        case 'f':

            change_trove_file(optarg);
            break;

        case 'l':

            if (!isNumber(optarg))
            {
                perror("Invalid length");
                exit(EXIT_FAILURE);
            }
            change_keylen(atoi(optarg));
            search = false;
            remove = false;
            break;

        case 'b':

            search = false;
            remove = false;
            update = false;

            end = true;
            break;

        case 'r':

            build = false;
            search = false;
            update = false;

            end = true;
            break;

        case 'u':

            build = false;
            search = false;
            remove = false;

            end = true;
            break;
        }
    }

    if (search)
    {
        printf("Searching For Key: \"%s\"\n", argv[argc - 1]);
        hashtable = trovefile_load();
        hashtable_mlist_files_have_key_print(hashtable, argv[argc - 1]);
        exit(EXIT_SUCCESS);
    }
    else if (build)
    {
        printf("Building Trove File:\n");
        hashtable = hashtable_mlist_new();
        for (; optind < argc; optind++)
        {
            if (isFile(argv[optind]))
            {
                recordWord(argv[optind], hashtable);
            }
        }
        trovefile_write(hashtable);
        exit(EXIT_SUCCESS);
    }
    else if (remove)
    {
        printf("Remove the Content:\n");
        hashtable = trovefile_load();
        for (; optind < argc; optind++)
        {
            if (isFile(argv[optind]))
            {
                hashtable_mlist_remove(hashtable, argv[optind]);
            }
        }
        trovefile_write(hashtable);
        exit(EXIT_SUCCESS);
    }
    else if (update)
    {
        printf("Update the Content:\n");
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

    perror("Argument Error");
    exit(EXIT_FAILURE);
    return 0;
}