#include "header.h"

int create_DB(Hash_t *arr, File_info *head)
{
    if (head == NULL)
    {
        return 0;  // No files to process
    }

    while (head)
    {
        if (openfile(arr, head->file_name) == 0)
        {
            return 0;  // Failed to open/process a file
        }

        head = head->f_link;
    }

    printf("\033[1;34mINFO : DATABASE created successfully!\033[0m\n");
    return 1;  // Success
}

int openfile(Hash_t *arr, char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        return 0;

    char write[100];

    while (fscanf(fp, "%s", write) != EOF)
    {
        int i;

        /* Determine hash index based on first character */
        if (write[0] >= 'a' && write[0] <= 'z')
            i = (write[0] - 'a') % 26;
        else if (write[0] >= 'A' && write[0] <= 'Z')
            i = (write[0] - 'A') % 26;
        else
            i = 26; // Non-alphabetic characters

        /* If word exists already in hash, skip inserting new main node */
        if (validation(arr, write, filename, i))
            continue;

        write[19] = '\0'; // Limit word size to 20

        /* Insert new Main_node if index is empty */
        if (arr[i].link == NULL)
        {
            Main_node *new = malloc(sizeof(Main_node));
            if (new == NULL)
                return 0;

            strcpy(new->word, write);
            new->file_count = 1;
            new->m_link = NULL;
            new->s_link = NULL;
            arr[i].link = new;

            /* Insert new Sub_node for the file */
            Sub_node *new1 = malloc(sizeof(Sub_node));
            if (new1 == NULL)
                return 0;

            strcpy(new1->file_name, filename);
            new1->word_count = 1;
            new1->s_link = NULL;
            new->s_link = new1;
        }
        else
        {
            /* Traverse to end of main linked list to insert new word */
            Main_node *temp = arr[i].link;
            while (temp->m_link != NULL)
                temp = temp->m_link;

            Main_node *new = malloc(sizeof(Main_node));
            if (new == NULL)
                return 0;

            strcpy(new->word, write);
            new->file_count = 1;
            new->m_link = NULL;
            new->s_link = NULL;
            temp->m_link = new;

            /* Insert Sub_node for file */
            Sub_node *new1 = malloc(sizeof(Sub_node));
            if (new1 == NULL)
                return 0;

            strcpy(new1->file_name, filename);
            new1->word_count = 1;
            new1->s_link = NULL;
            new->s_link = new1;
        }
    }

    fclose(fp);
    return 1;
}

int validation(Hash_t *arr, char *name, char *filename, int i)
{
    Main_node *temp = arr[i].link;

    while (temp)
    {
        /* If word matches */
        if (strcmp(temp->word, name) == 0)
        {
            Sub_node *temp1 = temp->s_link;

            /* Traverse Sub_nodes to check if file exists */
            while (temp1)
            {
                if (strcmp(temp1->file_name, filename) == 0)
                {
                    temp1->word_count++;  // Increment word count for this file
                    return 1;
                }
                temp1 = temp1->s_link;
            }

            /* File not found → create new Sub_node */
            temp->file_count++;

            Sub_node *new1 = malloc(sizeof(Sub_node));
            if (new1 == NULL)
                return 0;

            strcpy(new1->file_name, filename);
            new1->word_count = 1;
            new1->s_link = NULL;

            /* Insert Sub_node at end of list */
            if (temp->s_link == NULL)
            {
                temp->s_link = new1;
            }
            else
            {
                Sub_node *temp2 = temp->s_link;
                while (temp2->s_link != NULL)
                    temp2 = temp2->s_link;
                temp2->s_link = new1;
            }

            return 1;
        }

        temp = temp->m_link; // Move to next Main_node
    }

    return 0; // Word not found → needs new Main_node
}