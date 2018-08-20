#include "hash.h"
#include "tokens.h"

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

void pushItem(HASH_TABLE* hashTable, char* key, char* value) {
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

	} else {
		newItem = createItem(key, value);

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
    }
}

int generateIndex(char* key, int size) {
    int hashval = 5381;
	int i = 0;

	// Convert our string to an integer
	while(hashval < 2147483647 && i < strlen(key)) {
		hashval = ((hashval << 5) + hashval) + key[i];
		i++;
	}

    return hashval % size;
}

HASH_ITEM* createItem(char* key, char* value) {
    HASH_ITEM *newItem;
    if((newItem = malloc(sizeof(HASH_ITEM))) == NULL) {
        return NULL;
    }
    newItem->key = strdup(key);
    newItem->value = strdup(value);
    newItem->next = NULL;

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
            printf(" >>Item:\n   -key: %s\n   -value: %s\n", hashItem->key, hashItem->value);
            hashItem = hashItem->next;
        }
    }
}

// just for test
/*
int main( int argc, char **argv ) {

	HASH_TABLE *hashtable = createHashTable(3);
	pushItem( hashtable, "k1", "charlie" );
	pushItem( hashtable, "k2", "pinky" );
	pushItem( hashtable, "k3", "blinky" );
	pushItem( hashtable, "k6", "katy perry");
	pushItem( hashtable, "k4", "floyd" );
	pushItem( hashtable, "k5", "maroon5" );
	pushItem( hashtable, "k1", "coldplay" );
	pushItem( hashtable, "k5", "rihanna");

    printHashTable(hashtable);

	return 0;
}
*/