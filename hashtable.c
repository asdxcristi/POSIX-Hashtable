/* Tema1 SO,Bucur Ionut-Cristian,333CA
 */

#include"hashtable.h"
#include"hash.h"


/* Allocs memory for the hashtable and initilizes it's componets
 * Components:
 * -size
 * -container(LinkedList)
 */
void initialize_hash(const unsigned int size, HashTable **hash_table)
{
	unsigned int i;

	(*hash_table) = calloc(1, sizeof(HashTable));
	DIE(hash_table == NULL, ERROR_INIT_HASH);
	(*hash_table)->size =  size;
	(*hash_table)->container = calloc(size, sizeof(LinkedList *));
	DIE((*hash_table)->container == NULL, ERROR_INIT_HASH);

	for (i = 0; i < size; i++) {
		(*hash_table)->container[i] = calloc(1, sizeof(LinkedList));
		DIE((*hash_table)->container[i] == NULL, ERROR_INIT_CONTAINER);
	}
}


/* Frees memory used by the hashtable and it's componets
 */
void destruct_hash(HashTable **hash_table)
{
	unsigned int i;
	Node *current_node;
	Node *prev_node;

	DIE(!hash_table, ERROR_NULL_HASH);

	for (i = 0; i < (*hash_table)->size; i++) {
		current_node = (*hash_table)->container[i]->first;

		while (current_node != NULL) {
			free(current_node->word);
			current_node->word = NULL;
			prev_node = current_node;
			current_node = current_node->next;
			free(prev_node);
			prev_node = NULL;
		}
		free((*hash_table)->container[i]);
		(*hash_table)->container[i] = NULL;
	}
	free((*hash_table)->container);
	(*hash_table)->container = NULL;
	free(*hash_table);
	*hash_table = NULL;
}

/*Destructs the current hash_table and allocs a new one
 */
void clear_hash(HashTable **hash_table)
{
	int size;

	DIE(!hash_table, ERROR_NULL_HASH);
	size = (*hash_table)->size;
	destruct_hash(hash_table);
	initialize_hash(size, hash_table);
}

/* Return the node coresponding to the searched word in the hash_table
 * Returns NULL if not found
 */
Node *get_node_by_word(const char *word, HashTable **hash_table)
{
	Node *current_node;
	LinkedList *current_bucket;
	unsigned int position;

	DIE(!hash_table, ERROR_NULL_HASH);
	position = hash(word, (*hash_table)->size);
	DIE(position > (*hash_table)->size - 1, ERROR_HASH_FUNCTION);

	current_bucket = (*hash_table)->container[position];
	current_node = current_bucket->first;

	while (current_node != NULL) {
		if (!strcmp(current_node->word, word))
			return current_node;
		current_node = current_node->next;
	}

	return NULL;
}

/* Returns true if the word exists in hash_table
 */
bool is_word_in_hash(char *word, HashTable **hash_table)
{
	Node *found_node = NULL;

	DIE(!hash_table, ERROR_NULL_HASH);
	found_node = get_node_by_word(word, hash_table);
	return found_node != NULL;
}

/* Unsafe stuff, MUST receive index < hashtable->size
 * Much security much trust in user
 */
LinkedList *get_bucket_by_index(const unsigned int index,
							HashTable **hash_table){
	DIE(!hash_table, ERROR_NULL_HASH);
	return (*hash_table)->container[index];
}

/* Returns the bucket where the word MIGHT be
 * Doesn't matter if it exists or not
 */
LinkedList *get_bucket_by_word(const char *word, HashTable **hash_table)
{
	unsigned int position;

	DIE(!hash_table, ERROR_NULL_HASH);
	position = hash(word, (*hash_table)->size);
	DIE(position > (*hash_table)->size - 1, ERROR_HASH_FUNCTION);
	return (*hash_table)->container[position];
}

/* Creates a new node containing the given word
 * prev and next are initialized to NULL
 */
Node *create_new_node(const char *word)
{
	Node *new_node;

	new_node = calloc(1, sizeof(Node));
	DIE(new_node == NULL, ERROR_NEW_NODE);
	new_node->word = calloc(1 + strlen(word), sizeof(char));
	DIE(new_node->word == NULL, ERROR_ALLOC_WORD);
	strcpy(new_node->word, word);
	new_node->prev = NULL;
	new_node->next = NULL;
	return new_node;
}

/* Adds word to the hashtable's container(LinkedList)
 */
void add_word(const char *word, HashTable **hash_table)
{
	LinkedList *current_bucket;
	Node *new_node;

	DIE(!hash_table, ERROR_NULL_HASH);
	current_bucket = get_bucket_by_word(word, hash_table);

	new_node = create_new_node(word);

	if (!current_bucket->first) {
		current_bucket->first = new_node;
		current_bucket->last = new_node;

	} else {
		current_bucket->last->next = new_node;
		new_node->prev = current_bucket->last;
		current_bucket->last = new_node;
	}
}

/* Removes the word from the hash_tables's container,
 * Does nothing if the word doesn't exist
 */
void remove_word(const char *word, HashTable **hash_table)
{
	Node *node;
	int bucket_nr;

	DIE(!hash_table, ERROR_NULL_HASH);
	node = get_node_by_word(word, hash_table);
	if (node) {
		bucket_nr = hash(word, (*hash_table)->size);

		if (node->prev)
			node->prev->next = node->next;
		else
			(*hash_table)->container[bucket_nr]->first = node->next;

		if (node->next)
			node->next->prev = node->prev;
		else
			(*hash_table)->container[bucket_nr]->last = node->prev;

		free(node->word);
		node->word = NULL;
		free(node);
	}
}

/* Resizes hash_tables with the new_size size
 */
void resize_hash(const unsigned int new_size, HashTable **hash_table)
{
	unsigned int i;
	HashTable *new_hash_table = NULL;
	LinkedList *current_bucket = NULL;
	Node *current_node = NULL;

	DIE(!hash_table, ERROR_NULL_HASH);
	initialize_hash(new_size, &new_hash_table);

	for (i = 0; i < (*hash_table)->size; i++) {
		current_bucket = get_bucket_by_index(i, hash_table);
		current_node = current_bucket->first;
		while (current_node != NULL) {
			add_word(current_node->word, &new_hash_table);
			current_node = current_node->next;
		}

	}

	destruct_hash(hash_table);
	*hash_table = new_hash_table;

}

/* Prints the hash_table's bucket to the fp
 */
void print_bucket(FILE *fp, LinkedList *bucket)
{
	Node *current_node;

	DIE(!bucket, ERROR_NULL_BUCKET);
	current_node = bucket->first;
	while (current_node != NULL) {
		DIE(fprintf(fp, "%s ", current_node->word) < (int)
			strlen(current_node->word + 2), ERROR_FILE_WRITE);
		current_node = current_node->next;
	}
	if (bucket->first)
		DIE(fprintf(fp, "\n") < (int) strlen("\n"), ERROR_FILE_WRITE);
}

/* Prints ALL the hash_table's buckets to the fp
 */
void print_all(FILE *fp, HashTable **hash_table)
{
	unsigned int i;

	DIE(!hash_table, ERROR_NULL_HASH);
	DIE(!fp, ERROR_FP_ARGUMENT_NULL);
	for (i = 0; i < (*hash_table)->size; i++)
		print_bucket(fp, (*hash_table)->container[i]);
}
