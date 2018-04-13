/* Tema1 SO,Bucur Ionut-Cristian,333CA
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_	1

#define ADD_COMMAND "add"
#define REMOVE_COMMAND "remove"
#define FIND_COMMAND "find"
#define CLEAR_COMMAND "clear"
#define PRINT_BUCKET_COMMAND "print_bucket"
#define PRINT_COMMAND "print"
#define RESIZE_COMMAND "resize"
#define RESIZE_DOUBLE_ARGUMENT "double"
#define RESIZE_HALVE_ARGUMENT "halve"

#define ADD_COMMAND_USAGE_ERROR "[BAD FORMAT]Expected: add <word>"
#define REMOVE_COMMAND_USAGE_ERROR "[BAD FORMAT]Expected: remove <word>"
#define FIND_COMMAND_USAGE_ERROR "[BAD FORMAT]Expected: find <word> [output_file]"
#define CLEAR_COMMAND_USAGE_ERROR "[BAD FORMAT]Expected: clear"
#define PRINT_BUCKET_COMMAND_USAGE_ERROR "[BAD FORMAT]Expected: print_bucket <bucket_index> [output_file]"
#define PRINT_BUCKET_COMMAND_ARGUMENT_ERROR "[BAD ARGUMENT]Bad index"
#define PRINT_COMMAND_USAGE_ERROR "[BAD FORMAT]Expected: print [output_file]"
#define RESIZE_COMMAND_USAGE_ERROR "[BAD FORMAT]Expected: resize [double|halve]"

#define UNKNOW_COMMAND "[BAD COMMAND]Known commans:[add|remove|find|clear|print|print_bucket|resize]"

#define FIND_RESULT_TRUE "True"
#define FIND_RESULT_FALSE "False"

#include"hashtable.h"

void add_command_handler(char *argument, HashTable **hash_table);

void remove_command_handler(char *argument, HashTable **hash_table);

void find_command_handler(char *argument, HashTable **hash_table);

void print_command_handler(char *argument, HashTable **hash_table);

void print_bucket_command_handler(char *argument, HashTable **hash_table);

void clear_command_handler(char *argument, HashTable **hash_table);

void resize_command_handler(char *argument, HashTable **hash_table);

void resolve_command(char *full_command, HashTable **hash_table);

#endif
