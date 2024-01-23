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

// TODO: Choose number of buckets in the hash table
const unsigned int N = 65536;

// Hash table
node *table[N];

// Number of words loaded in the dictionary
unsigned int loaded_words = 0;

// Custom case-insensitive string comparison function
int strcasecmp_custom(const char *s1, const char *s2)
{
    while (*s1 != '\0' && *s2 != '\0')
    {
        if (tolower(*s1) != tolower(*s2))
        {
            return (int) (tolower(*s1) - tolower(*s2));
        }
        s1++;
        s2++;
    }
    return (int) (*s1 - *s2);
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Custom hash function - simple sum of ASCII values
    unsigned int hash_value = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash_value += tolower(word[i]);
    }
    return hash_value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Initialize table
    for (unsigned int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Read words from dictionary and insert into hash table
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            return false;
        }

        // Copy word to the node
        strcpy(new_node->word, word);

        // Hash word to get the index
        unsigned int index = hash(word);

        // Insert node at the beginning of the linked list
        new_node->next = table[index];
        table[index] = new_node;

        // Increment the loaded word count
        loaded_words++;
    }

    // Close dictionary file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return loaded_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Free memory for each linked list
    for (unsigned int i = 0; i < N; i++)
    {
        node *current = table[i];
        while (current != NULL)
        {
            node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    return true;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to get the index
    unsigned int index = hash(word);

    // Traverse the linked list at that index
    node *current = table[index];
    while (current != NULL)
    {
        // Compare the word in the node with the input word (case-insensitive)
        if (strcasecmp_custom(current->word, word) == 0)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}
