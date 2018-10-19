#include "hash.h"
#include "util.h"

HASH_TABLE* createHashTable(int size) {
    int i;
    HASH_TABLE* hashTable = NULL;

    //Allocate the table
    if((hashTable = (HASH_TABLE*) malloc(sizeof(HASH_TABLE))) == NULL) {
        return NULL;
    }

    //Allocate pointers to the head items
    if((hashTable->items = (HASH_ITEM**) malloc(sizeof(HASH_ITEM) * size)) == NULL) {
        return NULL;
    }
    for(i=0; i < size; i++) {
        hashTable->items[i] = NULL;
    }

    hashTable->size = size;

    return hashTable;
}

HASH_ITEM* pushItem(HASH_TABLE* hashTable, char* key, char* value,int type) {
    HASH_ITEM *newItem = NULL;
    HASH_ITEM *nextItem = NULL;
    HASH_ITEM *lastItem = NULL;
    int index = generateIndex(key, hashTable->size);

    nextItem = hashTable->items[index];

    while(nextItem != NULL && (strcmp(key, nextItem->key) != 0)) {
        lastItem = nextItem;
        nextItem = nextItem->next;
    }

    // This item already exists
	if( nextItem != NULL && strcmp(key, nextItem->key) == 0) {
		nextItem->value = strdup( value );
        return nextItem;

	} else {
		newItem = createItem(key, value, type);

		// We're at the start of the linked list in this index
		if( nextItem == hashTable->items[index] ) {
			newItem->next = nextItem;
			hashTable->items[index] = newItem;
	
		// We're at the end of the linked list in this index
		} else if ( nextItem == NULL ) {
			lastItem->next = newItem;
	
		// We're in the middle of the list
		} else  {
			newItem->next = nextItem;
			lastItem->next = newItem;
		}
        return newItem;
    }
}

int generateIndex(char* key, int size) {
    int hashval = 1;
	int i = 0;

	// Convert our string to an integer
	while(hashval < 2147483647 && i < strlen(key)) {
		hashval += key[i];
		i++;
	}
    
    return hashval % size;
}

HASH_ITEM* createItem(char* key, char* value, int type) {
    HASH_ITEM *newItem;
    if((newItem = malloc(sizeof(HASH_ITEM))) == NULL) {
        return NULL;
    }
    newItem->key = strdup(key);
    newItem->value = strdup(value);
    newItem->next = NULL;
    newItem->type = type;
    return newItem;
}

char* getItem(HASH_TABLE* hashTable, char *key) {
    HASH_ITEM *hashItem = NULL;
    int index = generateIndex(key, hashTable->size);

    hashItem = hashTable->items[index];
    while(hashItem != NULL) {
        if (hashItem->key != NULL && strcmp(key, hashItem->key) == 0) {
            break;
        }

        hashItem = hashItem->next;
    }
    return hashItem->value;
}

void printHashTable(HASH_TABLE* hashTable) {
    int i;    
    HASH_ITEM *hashItem = NULL;
    printf("HashTable - Index:\n");

    for(i=0; i<hashTable->size; i++) {
        printf("[%d]\n", i);
        hashItem = hashTable->items[i];
        while(hashItem != NULL) {
            if(hashItem->type == SYMBOL_LIT_INT)
                printf(" >>Item:\n   -key: %s\n   -value: %s\n   -type: SYMBOL_LIT_INT\n", hashItem->key, hashItem->value);
            if(hashItem->type == SYMBOL_LIT_FLOAT)
                printf(" >>Item:\n   -key: %s\n   -value: %s\n   -type: SYMBOL_LIT_FLOAT\n", hashItem->key, hashItem->value);
            if(hashItem->type == SYMBOL_LIT_STRING)
                printf(" >>Item:\n   -key: %s\n   -value: %s\n   -type: SYMBOL_LIT_STRING\n", hashItem->key, hashItem->value);
            if(hashItem->type == SYMBOL_LIT_CHAR)
                printf(" >>Item:\n   -key: %s\n   -value: %s\n   -type: SYMBOL_LIT_CHAR\n", hashItem->key, hashItem->value);
            if(hashItem->type == SYMBOL_TK_IDENTIFIER)
                printf(" >>Item:\n   -key: %s\n   -value: %s\n   -type: SYMBOL_TK_IDENTIFIER\n", hashItem->key, hashItem->value);
            hashItem = hashItem->next;
        }
    }
}


void checkUndeclaredHash(HASH_TABLE* hashTable) {
    HASH_ITEM *item;

    int i;
    for (int i = 0; i < HASH_SIZE; ++i)
    {
        for(item = hashTable->items[i];  item; item = item->next) {
            if(item->type == TK_IDENTIFIER) {
                fprintf(stderr, "Undeclared symbol %s in hash\n", item->value);
            }
        }
    }
}