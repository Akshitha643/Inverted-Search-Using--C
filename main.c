/*
NAME : G AKSHITHA REDDY
START DATE : 26-04-2026
END DATE : 06-05-2026
DESCRIPTION : An inverted index is an index data structure storing a mapping from content, such as words or numbers, to its locations in a database file, or in a document or a set of documents. The purpose of an inverted index is to allow fast full text searches, at a cost of increased processing when a document is added to the database. The inverted file may be the database file itself, rather than its index. It is the most popular data structure used in document retrieval systems, used on a large scale for example in search engines. The purpose of this project is to implement the inverted search using Hash Algorithms.
PRE-REQUISITE :
                Hashing
                Single linked list
                File Handling

*/

#include "header.h"

int main(int argc, char *argv[])
{
    /* Check for minimum command line arguments */
    if (argc < 2)
    {
        printf("\033[1;31mERROR\033[0m : Please provide the file name as a command line argument.\n");
        return 0;
    }

    /* Head pointer for linked list of valid files */
    File_info *head = NULL;

    /* Validate input files (.txt, not empty, no duplicates) */
    if (validate_arguments(argc, argv, &head) == 0)
    {
        printf("\033[1;31mINFO\033[0m : No valid files found.\n");
        return 0;
    }

    /* Hash table with 27 indexes (a-z + special characters) */
    Hash_t arr[27];

    /* Initialize hash table */
    for (int i = 0; i < 27; i++)
    {
        arr[i].index = i;
        arr[i].link = NULL;
    }

    int choice;
    int flag = 0;   // Prevent duplicate create
    int flag1 = 0;  // Prevent duplicate update

    /* Main menu loop */
    while (1)
    {
        printf("\033[1;34m\nMAIN MENUE :\033[0m\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Update DATABASE\n");
        printf("4. Search in Database\n");
        printf("5. Save Database\n");
        printf("6. Exit\n");
        printf("\nEnter your choice : ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                /* Create database only once */
                if (flag == 0)
                {
                    if (create_DB(arr, head) == 0)
                    {
                        printf("ERROR : Creating database failed\n");
                        return 0;
                    }
                    flag = 1;
                }
                else
                {
                    printf("\nINFO : Database already created\n\n");
                }
                break;

            case 2:
                /* Display full hash table contents */
                display_db(arr);
                break;

            case 3:
                /* Update database from backup file (only if not already created) */
                if (flag == 1 || flag1 == 1)
                {
                    printf("\nINFO : Database already created\n\n");
                }
                else
                {
                    if (update_db(arr, head) == 0)
                    {
                        printf("ERROR : Updating database failed\n");
                        return 0;
                    }
                    flag1 = 1;
                }
                break;

            case 4:
            {
                /* Search a word in database */
                char word[100];
                printf("Enter the word you want to search: ");
                scanf("%s", word);

                if (search_db(arr, word) == 0)
                {
                    printf("\n\e[1;31mINFO :\e[0m '%s' is not present in the database\n\n", word);
                }
                break;
            }

            case 5:
            {
                /* Save current database into backup file */
                char filename[100];
                printf("Enter the file name to save data: ");
                scanf("%s", filename);
                save_db(arr, filename);
                break;
            }

            case 6:
                /* Exit program safely */
                printf("\033[1;31m\n***TERMINATING***\033[0m\n");
                exit(0);

            default:
                printf("ERROR : Invalid choice\n");
        }
    }

    return 1;
}
