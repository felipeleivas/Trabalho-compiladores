#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"

#define HASH_SIZE 997

struct hashItem {
    char *value;
    char *key;
    int type;
    struct hashItem *next;
};
typedef struct hashItem HASH_ITEM;

struct hashTable {
    int size;
    struct hashItem **items;
};
typedef struct hashTable HASH_TABLE;

HASH_TABLE* createHashTable(int size);
int generateIndex(char* key, int size);
HASH_ITEM* pushItem(HASH_TABLE* hashTable, char* key, char* value,int type);
HASH_ITEM* createItem(char* key, char* value, int type);
char* getItem(HASH_TABLE* hashTable, char *key);
void printHashTable(HASH_TABLE* hashTable);
void checkUndeclaredHash(HASH_TABLE* hashTable);
#endif