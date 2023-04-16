#include "myshell.h"

/**
 * str_length - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int str_length(char *str)
{
	int len = 0;

	if (!str)
		return (0);

	while (*str++)
		len++;

	return (len);
}

/**
 * _strcmp - performs lexicographic comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative value if str1 < str2,
 * positive value if str1 > str2, 0 if str1 == str2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with prefix
 * @prefix: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of prefix or NULL
 */
char *starts_with(const char *prefix, const char *needle)
{
	while (*needle)
		if (*needle++ != *prefix++)
			return (NULL);
	return ((char *)prefix);
}

/**
 * string_concat - concatenates two strings
 * @str1: the first string
 * @str2: the second string
 *
 * Return: pointer to concatenated string
 */
char *string_concat(char *str1, char *str2)
{
	char *ret = str1;

	while (*str1)
		str1++;
	while (*str2)
		*str1++ = *str2++;
	*str1 = *str2;
	return (ret);
}
