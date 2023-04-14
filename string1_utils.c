#include "myshell.h"

/**
*string_copy - copies a string
*@destination: the destination
*@source: the source
*Return: pointer to destination
*/
char *string_copy(char *destination, char *source)
{
	int i = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[i])
	{
		destination[i] = source[i];
		i++;
	}
	destination[i] = 0;
	return (destination);
}

/**
 * string_duplicate - duplicates a string
 * @source_string: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *string_duplicate(const char *source_string)
{
	int string_length = 0;
	char *duplicated_string;

	if (source_string == NULL)
		return (NULL);
	while (*source_string++)
		string_length++;
	duplicated_string = malloc(sizeof(char) * (string_length + 1));
	if (!duplicated_string)
		return (NULL);
	for (string_length++; string_length--;)
		duplicated_string[string_length] = *--source_string;
	return (duplicated_string);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		_putchar(str[index]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @ch: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char ch)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}
