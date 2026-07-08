#include "header.h"

int save_db(Hash_t *arr, char *file)
{
    FILE *fd = fopen(file, "w");  // Open file for writing
    if (fd == NULL)
    {
        printf("Error opening file!\n");
        return 0;  // Failure
    }

    /* Traverse all 27 hash indexes */
    for (int i = 0; i < 27; i++)
    {
        if (arr[i].link == NULL)
            continue;  // Skip empty indexes

        fprintf(fd, "#%d;", i);  // Write index marker

        Main_node *temp = arr[i].link;

        /* Traverse all Main_nodes (words) in this index */
        while (temp)
        {
            /* Write word and total file count */
            fprintf(fd, "%s;%d;", temp->word, temp->file_count);

            Sub_node *sub_temp = temp->s_link;

            /* Write all Sub_nodes (file names and word counts) */
            while (sub_temp)
            {
                fprintf(fd, "%s;%d;", sub_temp->file_name, sub_temp->word_count);
                sub_temp = sub_temp->s_link;
            }

            temp = temp->m_link;  // Move to next word
        }

        fprintf(fd, "#\n");  // End of this index
    }

    fclose(fd);  // Close file
    printf("\033[1;34m\nINFO : DATABASE saved successfully!\033[0m\n");

    return 1;  // Success
}