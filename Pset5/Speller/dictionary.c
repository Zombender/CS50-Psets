// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

unsigned int dictionarys = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int entra = hash(word);
    node *position = table[entra];
    char wordcheck[LENGTH + 1];

    strcpy(wordcheck, word);

    for(int i = 0; wordcheck[i];i++){
        wordcheck[i] = tolower(wordcheck[i]);
    }
    while(position != NULL){
        if(strcmp(position -> word, wordcheck)==0){
            return true;
        }
        position = position -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    const unsigned int Cons = 31;
    unsigned int hashval = 0;
    for(int i = 0; word[i] != '\0'; i++){
        unsigned int wordval= toupper(word[i]) - 'A';
        hashval = (hashval * Cons + wordval) % N;
    }
    return hashval;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    dictionarys = 0;
    // TODO
    FILE *file = fopen(dictionary,"r");
    if (file == NULL){
        printf("Error al abrir el archivo\n");
        return false;
    }

    char word_[LENGTH + 1];
    while(fscanf(file, "%s", word_) != EOF){
        node *nuevoN = malloc(sizeof(node));
        if(nuevoN == NULL){
            //fclose(file);
            return false;

        }
        strcpy(nuevoN->word, word_);

        unsigned int punt = hash(word_);

        nuevoN -> next = table[punt];
        table[punt] = nuevoN;
        dictionarys++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictionarys;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for(int i= 0; i<N;i++){
        node *aux = table[i];
        while(aux !=NULL){
            node *erase = aux->next;
            free(aux);
            aux = erase;
        }
    }
    return true;
}
