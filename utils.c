/* Tema1 SO,Bucur Ionut-Cristian,333CA
 */

#include"utils.h"

/* Checks if the input string is a positive number
 */
bool is_number(char *input)
{
	int length;
	int i;

	length = strlen(input);
	for (i = 0; i < length; i++)
		if (!isdigit(input[i]))
			return false;
	return true;
}
/* Returns the number of character c
 * occurences in string
 */
int nr_of_occurences_of_char(char *string, char c)
{
	int i;

	for (i = 0; string[i]; string[i] == c ? i++ : *string++)
		;

	return i;
}
