#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
#include "util.h"

#define DATATYPE_FLOAT 255
#define DATATYPE_FLOAT_VECTOR 256
#define DATATYPE_INT 257
#define DATATYPE_INT_VECTOR 258
#define DATATYPE_STRING 261
#define DATATYPE_BOOLEAN 262

#define HASH_SIZE 20
#define DATATYPE_MAX 10
struct hashItem {
    char *value;
    char *key;
    int type;
    int dataType[DATATYPE_MAX];
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
HASH_ITEM* makeTemp(HASH_TABLE hash);
#endif