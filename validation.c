#include "header.h"

int validate_arguments(int argc, char *argv[], File_info **head)
{
    int valid_file_found = 0;

    for (int i = 1; i < argc; i++)
    {
        int j = 0;

        /* Check for .txt extension */
        for (j = 0; argv[i][j]; j++)
        {
            if (argv[i][j] == '.')
            {
                break;
            }
        }

        if (strcmp(argv[i] + j, ".txt") != 0)
        {
            continue;
        }

        FILE *fd = fopen(argv[i], "r");
        if (fd == NULL)
        {
            continue;
        }

        char c = getc(fd);
        if (c == EOF)
        {
            fclose(fd);
            continue;
        }
        fclose(fd);

        /* Check duplicate file */
        File_info *temp = *head;
        int flag = 0;

        while (temp)
        {
            if (strcmp(temp->file_name, argv[i]) == 0)
            {
                flag = 1;
                break;
            }
            temp = temp->f_link;
        }

        if (flag == 1)
        {
            continue;
        }

        /* Create new node */
        File_info *new = malloc(sizeof(File_info));
        if (new == NULL)
        {
            return 0;
        }

        strcpy(new->file_name, argv[i]);
        new->f_link = NULL;

        if (*head == NULL)
        {
            *head = new;
        }
        else
        {
            temp = *head;
            while (temp->f_link != NULL)
            {
                temp = temp->f_link;
            }
            temp->f_link = new;
        }

        valid_file_found = 1;
    }

    return valid_file_found;   // return 1 if at least one valid file added, else 0
}