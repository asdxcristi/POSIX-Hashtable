#include"utils.h"
#include"hashtable.h"
#include"commands.h"

#define ERROR_USAGE "Usage: ./tema1 SIZE_HASHTABLE"
#define MIN_ARGC 2


int main(int argc, char **argv)
{
	unsigned int size;
	int i;
	FILE *fp;
	char command_buffer[MAX_COMMAND_SIZE];
	HashTable *hash_table = NULL;

	DIE(argc < MIN_ARGC, ERROR_USAGE);

	DIE(!is_number(argv[1]), ERROR_SIZE);

	size = strtoul(argv[1], NULL, DEFAULT_NUMBER_BASE);


	initialize_hash(size, &hash_table);


	if (argc == MIN_ARGC) {
		memset(command_buffer, 0, MAX_COMMAND_SIZE);
		while (fgets(command_buffer, MAX_COMMAND_SIZE, stdin) != NULL) {
			if (!strcmp(command_buffer, "\n")) {
				memset(command_buffer, 0, MAX_COMMAND_SIZE);
				continue;
			}
			resolve_command(command_buffer, &hash_table);
			memset(command_buffer, 0, MAX_COMMAND_SIZE);
		}
	} else {
		for (i = 2; i < argc; i++) {
			fp = fopen(argv[i], READ_FILE_MODE);
			DIE(!fp, ERROR_FILE_OPEN);
			memset(command_buffer, 0, MAX_COMMAND_SIZE);
			while (fgets(command_buffer,
						MAX_COMMAND_SIZE, fp) != NULL) {
				if (!strcmp(command_buffer, "\n")) {
					memset(command_buffer, 0,
						   MAX_COMMAND_SIZE);
					continue;
				}
				resolve_command(command_buffer, &hash_table);
				memset(command_buffer, 0, MAX_COMMAND_SIZE);
			}
			fclose(fp);
		}
	}

	destruct_hash(&hash_table);
	return 0;
}
