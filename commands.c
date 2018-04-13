/* Tema1 SO,Bucur Ionut-Cristian,333CA
 */

#include"commands.h"

/* Implements add command
 * Format: add <word>
 */
void add_command_handler(char *argument, HashTable **hash_table)
{
	DIE(!argument ||
		strlen(argument) < 1 ||
		nr_of_occurences_of_char(argument, ' ') > 0,
			ADD_COMMAND_USAGE_ERROR);

	if (is_word_in_hash(argument, hash_table))
		return;

	add_word(argument, hash_table);
}

/* Implements remove command
 * Format: remove <word>
 */
void remove_command_handler(char *argument, HashTable **hash_table)
{
	DIE(!argument || strlen(argument) < 1 ||
		nr_of_occurences_of_char(argument, ' ') > 0,
		REMOVE_COMMAND_USAGE_ERROR);
	remove_word(argument, hash_table);
}

/* Implements find command
 * Format: find <word>
 */
void find_command_handler(char *argument, HashTable **hash_table)
{
	FILE *fp = DEFAULT_OUTPUT;
	bool result;
	char *word;
	char *file_name;

	DIE(!argument || strlen(argument) < 1 ||
		nr_of_occurences_of_char(argument, ' ') > 1,
		FIND_COMMAND_USAGE_ERROR);

	word = strtok(argument, " ");
	DIE(!word, FIND_COMMAND_USAGE_ERROR);

	file_name = strtok(NULL, " ");

	result = is_word_in_hash(argument, hash_table);


	if (file_name) {
		fp = fopen(file_name, DEFAULT_OUTPUT_MODE);
		DIE(!fp, ERROR_FILE_OPEN);
	}

	DIE(fprintf(fp, "%s\n", result?FIND_RESULT_TRUE:FIND_RESULT_FALSE) <
		(int)strlen(result?FIND_RESULT_TRUE:FIND_RESULT_FALSE) + 1,
		ERROR_FILE_WRITE);

	if (fp != DEFAULT_OUTPUT)
		fclose(fp);
}

/* Implements add command
 * Format: add <word>
 */
void print_command_handler(char *argument, HashTable **hash_table)
{
	char *file_name;
	FILE *fp = DEFAULT_OUTPUT;

	DIE(nr_of_occurences_of_char(argument, ' ') > 0,
		PRINT_COMMAND_USAGE_ERROR);
	file_name = strtok(argument, " ");
	if (file_name) {
		fp = fopen(file_name, DEFAULT_OUTPUT_MODE);
		DIE(!fp, ERROR_FILE_OPEN);
	}

	print_all(fp, hash_table);

	if (fp != DEFAULT_OUTPUT)
		fclose(fp);
}

/* Implements print_bucket command
 * Format: print_bucket <bucket_index> [output_file]
 */
void print_bucket_command_handler(char *argument, HashTable **hash_table)
{
	unsigned int index_of_bucket;
	char *file_name;
	char *_index_of_bucket;
	FILE *fp = DEFAULT_OUTPUT;

	DIE(!argument ||
		strlen(argument) < 1 ||
		nr_of_occurences_of_char(argument, ' ') > 1,
		PRINT_BUCKET_COMMAND_USAGE_ERROR);

	_index_of_bucket = strtok(argument, " ");
	DIE(!_index_of_bucket, PRINT_BUCKET_COMMAND_ARGUMENT_ERROR);

	DIE(!is_number(_index_of_bucket),
		PRINT_BUCKET_COMMAND_ARGUMENT_ERROR);
	index_of_bucket = strtoul(_index_of_bucket, NULL, DEFAULT_NUMBER_BASE);

	DIE((index_of_bucket > (*hash_table)->size-1),
		PRINT_BUCKET_COMMAND_ARGUMENT_ERROR);

	file_name = strtok(NULL, " ");

	if (file_name) {
		fp = fopen(file_name, DEFAULT_OUTPUT_MODE);
		DIE(!fp, ERROR_FILE_OPEN);
	}

	print_bucket(fp, get_bucket_by_index(index_of_bucket, hash_table));

	if (fp != DEFAULT_OUTPUT)
		fclose(fp);
}

/* Implements clear command
 * Format: clear
 */
void clear_command_handler(char *argument, HashTable **hash_table)
{
	DIE(argument && strlen(argument) > 0, CLEAR_COMMAND_USAGE_ERROR);
	clear_hash(hash_table);
}

/* Implements resize command
 * Format: resize [double|halve]
 */
void resize_command_handler(char *argument, HashTable **hash_table)
{
	DIE(!argument ||
	strlen(argument) < 1 ||
	nr_of_occurences_of_char(argument, ' ') > 0,
		RESIZE_COMMAND_USAGE_ERROR);

	if (!strcmp(argument, RESIZE_DOUBLE_ARGUMENT))
		resize_hash((*hash_table)->size * 2, hash_table);
	else if (!strcmp(argument, RESIZE_HALVE_ARGUMENT))
		resize_hash((*hash_table)->size / 2, hash_table);
	else
		DIE(true, RESIZE_COMMAND_USAGE_ERROR);
}

/* Resolves the given command and arguments on the hash_table
 */
void resolve_command(char *full_command, HashTable **hash_table)
{
	char *command = strtok(full_command, " ");
	char *argument = NULL;
	char *last_char = NULL;

	DIE(!command, UNKNOW_COMMAND);

	argument = !command ? NULL : full_command + strlen(command) + 1;

	if (argument) {
		last_char = argument + strlen(argument) - 1;
		*last_char = (*last_char == '\n' ? '\0' : *last_char);
	}

	last_char = command + strlen(command) - 1;
	*last_char = (*last_char == '\n' ? '\0' : *last_char);


	if (!strcmp(command, ADD_COMMAND)) {
		add_command_handler(argument, hash_table);
		return;
	}
	if (!strcmp(command, FIND_COMMAND)) {
		find_command_handler(argument, hash_table);
		return;
	}
	if (!strcmp(command, PRINT_COMMAND)) {
		print_command_handler(argument, hash_table);
		return;
	}
	if (!strcmp(command, PRINT_BUCKET_COMMAND)) {
		print_bucket_command_handler(argument, hash_table);
		return;
	}
	if (!strcmp(command, CLEAR_COMMAND)) {
		clear_command_handler(argument, hash_table);
		return;
	}
	if (!strcmp(command, REMOVE_COMMAND)) {
		remove_command_handler(argument, hash_table);
		return;
	}
	if (!strcmp(command, RESIZE_COMMAND)) {
		resize_command_handler(argument, hash_table);
		return;
	}
	DIE(true, UNKNOW_COMMAND);
}
