#include "header.h"

int search_db(Hash_t *arr, char *word)
{
    int c;

    /* Determine hash index from first character */
    if (word[0] >= 'a' && word[0] <= 'z')
        c = (word[0] - 'a') % 26;
    else if (word[0] >= 'A' && word[0] <= 'Z')
        c = (word[0] - 'A') % 26;
    else
        c = 26; // Non-alphabetic characters

    /* If no words exist at this index */
    if (arr[c].link == NULL)
        return 0; // Word not found

    Main_node *temp = arr[c].link;

    /* Traverse Main_nodes at this index */
    while (temp)
    {
        if (strcmp(temp->word, word) == 0)
        {
            /* Word found → print details */
            printf("\n\033[1;34mDETAILS :\033[0m\n'%s' is present in %d file(s):\n", temp->word, temp->file_count);

            Sub_node *temp1 = temp->s_link;
            while (temp1)
            {
                printf("In File: %s  %d time(s)\n", temp1->file_name, temp1->word_count);
                temp1 = temp1->s_link;
            }

            return 1; // Success
        }

        temp = temp->m_link; // Move to next word
    }

    return 0; // Word not found
}