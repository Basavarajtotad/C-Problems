#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1000

// Function to compute the hash name for a given type
unsigned long fun_hash(const char *type) {
    unsigned long hash = 0;
    int c;
    while ((c = *type++)) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash % TABLE_SIZE;
}

// Structure for type-name pairs
typedef struct {
    char *type;
    char *name;
} typenamePair;


// Structure for a hash table
typedef struct {
    typenamePair *table[TABLE_SIZE];
} MyHashTB;

// Initialize a hash table
void initialize(MyHashTB *hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
}

// Insert a type-name pair into the hash table
void insert(MyHashTB *hashTable, const char *type, const char *name) {
    unsigned long index = fun_hash(type);

    // Check if the type already exists
    if (hashTable->table[index] != NULL && strcmp(hashTable->table[index]->type, type) == 0) {
        printf("type already exists.\n");
        return;
    }

    typenamePair *newPair = (typenamePair *)malloc(sizeof(typenamePair));
    newPair->type = strdup(type);
    newPair->name = strdup(name);

    hashTable->table[index] = newPair;
}

// Retrieve the name associated with a given type
const char *get(MyHashTB *hashTable, const char *type) {
    unsigned long index = fun_hash(type);

    if (hashTable->table[index] != NULL && strcmp(hashTable->table[index]->type, type) == 0) {
        return hashTable->table[index]->name;
    }

    return "Removed";
}

// Remove a type-name pair from the hash table
void removetype(MyHashTB *hashTable, const char *type) {
    unsigned long index = fun_hash(type);

    if (hashTable->table[index] != NULL && strcmp(hashTable->table[index]->type, type) == 0) {
        free(hashTable->table[index]->type);
        free(hashTable->table[index]->name);
        free(hashTable->table[index]);
        hashTable->table[index] = NULL;
        return;
    }

    printf("type not found.\n");
}

// Main function
int main() {
    MyHashTB hashTable;
    initialize(&hashTable);

    insert(&hashTable, "one", "company name : cyient");
    insert(&hashTable, "two", "Place : electronic");
    insert(&hashTable, "three", "TYpe : city");

    printf("%s\n", get(&hashTable, "one"));
    printf("%s\n", get(&hashTable, "two"));
    printf("%s\n", get(&hashTable, "three"));
    printf("%s\n", get(&hashTable, "four"));

    removetype(&hashTable, "two");
    printf("%s\n", get(&hashTable, "two"));

    // removetype(&hashTable, "three");
    printf("%s\n", get(&hashTable, "three"));

    return 0;
}
