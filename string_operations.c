#include "myshell.h"

/**
* string_copy_n - copies a string from source to destination
* @destination: the destination string to be copied to
* @source: the source string to copy from
* @count: the number of characters to be copied
* Return: the concatenated string
*/
char *string_copy_n(char *destination, char *source, int count)
{
	int i, j;
	char *start = destination;

	i = 0;
	while (source[i] != '\0' && i < count - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < count)
	{
		j = i;
		while (j < count)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (start);
}

/**
* string_concatenate_n - Concatenates two strings
* @destination: The first string to be concatenated
* @source: The second string to concatenate to the first string
* @count: The maximum number of bytes to concatenate from the second string
*
* Return: The concatenated string
*/
char *string_concatenate_n(char *destination, char *source, int count)
{
	int dest_len = 0, src_len = 0;
	char *start = destination;

	while (destination[dest_len] != '\0')
		dest_len++;

	while (source[src_len] != '\0' && src_len < count)
	{
		destination[dest_len] = source[src_len];
		dest_len++;
		src_len++;
	}
	if (src_len < count)
		destination[dest_len] = '\0';

	return (start);
}

/**
* string_find_char - Locates a character in a string
* @string: The string to be searched
* @target: The character to look for
* Return: A pointer to the memory area containing the character
*/
char *string_find_char(char *string, char target)
{
	do {
		if (*string == target)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}
