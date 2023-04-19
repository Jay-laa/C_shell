#include "myshell.h"

/**
* interactive - returns true if shell is in interactive mode
* @info: pointer to struct containing shell information
*
* Return: 1 if interactive mode, 0 otherwise
*/
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
* is_delimiter - checks if character is a delimiter
* @ch: the character to check
* @delim: the delimiter string
*
* Return: 1 if true, 0 if false
*/
int is_delimiter(char **ch, char *delim)
{
	while (*delim)
	{
		if (*delim++ == **ch)
			return (1);
	}
	return (0);
}

/**
* is_alpha - checks for alphabetic character
* @ch: The character to input
* Return: 1 if ch is alphabetic, 0 otherwise
*/

int is_alpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
* to_integer - converts a string to an integer
* @s: the string to be converted
*
* Return: 0 if no numbers in string, converted number otherwise
*/

int to_integer(char *s)
{
	int index, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (index = 0; s[index] != '\0' && flag != 2; index++)
	{
	if (s[index] == '-')
	sign *= -1;

	if (s[index] >= '0' && s[index] <= '9')
	{
	flag = 1;
	result *= 10;
	result += (s[index] - '0');
	}
	else if (flag == 1)
	flag = 2;
	}

	if (sign == -1)
	output = -result;
	else
	output = result;

	return (output);
}
