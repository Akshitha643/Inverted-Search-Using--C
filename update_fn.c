#include "header.h"

int update_db(Hash_t *arr, File_info *head)
{
    char backup_file[100];
    printf("Enter backup file name: ");
    scanf("%s", backup_file);

    /* Open backup file for reading */
    FILE *fp = fopen(backup_file, "r");
    if (!fp)
    {
        perror("fopen");  // Print system error
        return 0;         // Failure
    }

    char ch;

    /* Read until EOF */
    while (fscanf(fp, " %c", &ch) == 1)
    {
        if (ch != '#')
            continue;  // Skip until index marker found

        int index;
        fscanf(fp, "%d;", &index);  // Read hash index

        /* Process all words under this index */
        while (1)
        {
            char word[100];
            int file_count;

            /* Read word and its file count */
            if (fscanf(fp, "%[^;];%d;", word, &file_count) != 2)
                break;  // End of index or format error

            /* Create new Main_node */
            Main_node *m_new = malloc(sizeof(Main_node));
            if (!m_new)
            {
                fclose(fp);
                return 0;
            }

            word[19] = '\0'; // Limit word to 20 chars
            strcpy(m_new->word, word);
            m_new->file_count = file_count;
            m_new->s_link = NULL;
            m_new->m_link = NULL;

            Sub_node *sub_tail = NULL;

            /* Read all Sub_nodes (files) for this word */
            for (int i = 0; i < file_count; i++)
            {
                char fname[100];
                int w_count;

                fscanf(fp, "%[^;];%d;", fname, &w_count);

                /* Remove file from File_info list if present */
                File_info *prev = NULL;
                File_info *temp = head;

                while (temp)
                {
                    if (strcmp(temp->file_name, fname) == 0)
                    {
                        if (prev)
                            prev->f_link = temp->f_link;
                        else
                            head = temp->f_link;

                        free(temp);
                        break;
                    }
                    prev = temp;
                    temp = temp->f_link;
                }

                /* Create Sub_node */
                Sub_node *s_new = malloc(sizeof(Sub_node));
                if (!s_new)
                {
                    fclose(fp);
                    return 0;
                }

                strcpy(s_new->file_name, fname);
                s_new->word_count = w_count;
                s_new->s_link = NULL;

                /* Link Sub_node to Main_node */
                if (!m_new->s_link)
                    m_new->s_link = sub_tail = s_new;
                else
                {
                    sub_tail->s_link = s_new;
                    sub_tail = s_new;
                }
            }

            /* Insert Main_node into hash table */
            if (!arr[index].link)
                arr[index].link = m_new;
            else
            {
                Main_node *t = arr[index].link;
                while (t->m_link)
                    t = t->m_link;
                t->m_link = m_new;
            }

            /* Check next character; break if new index or EOF */
            int c = fgetc(fp);
            if (c == '#' || c == EOF)
                break;

            ungetc(c, fp); // Put character back if not '#' or EOF
        }
    }

    fclose(fp);
    printf("\033[1;34m\nINFO : Database updated successfully\033[0m\n");
    return 1; // Success
}