// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

unsigned int count = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 261100;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);

    // if no word can be found by that index in the table
    if (table[index] == NULL)
    {
        return false;
    }
    // if there are some word by that index in the table
    else
    {
        // make that word into lower case
        char temp[LENGTH + 1];
        int c = strlen(word);
        for (int i = 0; i < c; i++)
        {
            temp[i] = tolower(word[i]);
        }
        temp[c] = '\0';

        //loop through all the words in that index
        node *ptr = table[index];
        while (ptr != NULL)
        {
            // return true when the word is matched
            if (strcmp(ptr->word, temp) == 0)
            {
                return true;
            }
            ptr = ptr->next;
        }
        // return false when the word cannot be matched
        return false;
    }
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int id = toupper(word[0]) - 'A' + 1;
    int sum = 0;
    for (int i = 1; word[i] != '\0'; i++)
    {
        sum += (toupper(word[i]) - 'A');
    }
    char strid[N];
    char strsum[N];
    sprintf(strid, "%d", id);
    sprintf(strsum, "%d", sum);
    strcat(strid, strsum);
    int index = atoi(strid);
    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // make sure all the pointer in the table point to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    // Open file
    FILE *file = fopen(dictionary, "r");

    // make sure it can be found
    if (file == NULL)
    {
        return false;
    }
    // store word temporarily for copying
    char temp[LENGTH + 1];

    // read formatted data until there is no data left
    while (fscanf(file, "%s", temp) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        //copy word from temp to the node
        strcpy(n->word, temp);
        int index = hash(n->word);

        // table point to that load if there is no node pointed before
        if (table[index] == NULL)
        {
            table[index] = n;
            n->next = NULL;
        }
        // new node point to old node, then table point to new node to linked all the nodes in the same index
        else
        {
            n->next = table[index];
            table[index] = n;
        }
        //count the size of the dictionary
        count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // loop through all the table
    for (int i = 0; i < N; i++)
    {
        //create temporary pointer pointing to where the table is pointer
        node *temp = table[i];

        // loop until the table is not pointing a node
        while (temp != NULL)
        {
            //table is pointing where the node, that temp is pointing, is pointing
            table[i] = temp->next;
            // free the memory that the temp is pointer
            free(temp);
            temp = table[i];
        }
    }
    return true;
}
