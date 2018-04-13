/* Tema1 SO,Bucur Ionut-Cristian,333CA
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_	1

#define ERROR_INIT_HASH "Error on initializing hash_table"
#define ERROR_INIT_CONTAINER "Error on initializing container"
#define ERROR_NULL_HASH "Hash is NULL"
#define ERROR_HASH_FUNCTION "Index out of bounds[BAD hash_function,BAD!]"
#define ERROR_FP_ARGUMENT_NULL "Fp is NULL"
#define ERROR_NULL_BUCKET "Bucket is NULL"
#define ERROR_NEW_NODE "Creating new node"
#define ERROR_ALLOC_WORD "Alloc word size"

#include"utils.h"

typedef struct HashTable HashTable;

typedef struct Node Node;

typedef struct LinkedList LinkedList;


struct HashTable {
	unsigned int size;

	LinkedList **container;

};


struct LinkedList {
	Node *first;
	Node *last;

};


struct Node {
	char *word;
	Node *next;
	Node *prev;

};


void initialize_hash(const unsigned int size, HashTable **hash_table);

void destruct_hash(HashTable **hash_table);

void clear_hash(HashTable **hash_table);

Node *get_node_by_word(const char *word, HashTable **hash_table);

bool is_word_in_hash(char *word, HashTable **hash_table);

LinkedList *get_bucket_by_index(const unsigned int index,
							HashTable **hash_table);

LinkedList *get_bucket_by_word(const char *word, HashTable **hash_table);

Node *create_new_node(const char *word);

void add_word(const char *word, HashTable **hash_table);

void remove_word(const char *word, HashTable **hash_table);

void resize_hash(const unsigned int new_size, HashTable **hash_table);

void print_bucket(FILE *fp, LinkedList *bucket);

void print_all(FILE *fp, HashTable **hash_table);





#endif
