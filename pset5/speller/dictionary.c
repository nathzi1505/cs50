// Implements a dictionary's functionality
// Murmurhash3 hashing function has been taken from GitHub path name : https://github.com/PeterScott/murmur3/blob/master/murmur3.c

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


#include "dictionary.h"

#define LIMIT 100000

unsigned int counter; // Declares a global variable to keep track of counter
uint32_t *hash;                // Output for the hash
uint32_t seed = 42;              // Seed value for hash
node *head[LIMIT]; // Declares a head pointer of type node

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    hash = malloc(4);
    char *lword = malloc(50);
    int i = 0;
    // To convert the entire string into lowercase
    for (i = 0; i < strlen(word); i++)
    {
        lword[i] = tolower(word[i]);
    }
    lword[i] = '\0';
    MurmurHash3_x86_32(lword, strlen(lword), seed, hash);
    *hash = *hash % LIMIT; // To get the hash value within limits
    int flag = 0;
    node *checker = head[*hash]->next;
    while (checker != NULL)
    {
        if (strcasecmp(checker->word, word) == 0) // Checking both strings
        {
            flag = 1;
            free(lword);
            free(hash);
            return true;
        }
        else
        {
            checker = checker->next; // Moving to the next link
        }
    }
    free(lword);
    free(hash);
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    hash = malloc(4);
    // Initialise all the next files
    for (int i = 0; i < LIMIT; i++)
    {
        head[i] = malloc(sizeof(struct node)); // Allocating memory for the head array of nodes
        head[i]->next = NULL;
    }
    FILE *file = fopen(dictionary, "r");
    // Error Checking : If dictionary not present
    if (file == NULL)
    {
        free(hash);
        return false;
    }
    char *word_dic = malloc(50);
    counter = 0; // Initialises the counter
    // Stores the dictionary word by word
    while (1)
    {
        char *c = fgets(word_dic, 50, file);
        int length = strlen(word_dic);
        word_dic[length - 1] = '\0';
        // get the hash value
        MurmurHash3_x86_32(word_dic, strlen(word_dic), seed, hash);
        *hash = *hash % LIMIT; // Gets the hash value within limits
        if (c != NULL)
        {
            word_dic[strlen(word_dic)] = '\0';
            node *dic_node = calloc(1, sizeof(struct node)); // Allocating and zeroing the new memory
            if (dic_node == NULL)
            {
                free(word_dic);
                free(hash);
                return 0;
            }
            strcpy(dic_node->word, word_dic); // Copying the word into the linked list
            if (head[*hash]->next == NULL)
            {
                head[*hash]->next = dic_node;
            }
            else
            {
                dic_node->next = head[*hash]->next;
                head[*hash]->next = dic_node;
            }
            counter ++;
        }
        else if (c == NULL && counter != 0)
        {
            fclose(file);
            free(word_dic);
            free(hash);
            return true; // Closes the loading function
        }
    }

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (counter != 0)
    {
        return counter;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *unloader = NULL;
    for (int i = 0; i < LIMIT; i++)
    {
        unloader = head[i];
        while (1)
        {
            if (unloader != NULL)
            {
                node *tmp = unloader;
                unloader = unloader->next; // Moves onto the next node
                free(tmp); // Deallocates memory to the nodes
            }
            else
            {
                break;
            }
        }
    }
    return true;
}