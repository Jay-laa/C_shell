#include "myshell.h"

/**
 * err_to_integer - converts a string to an integer with error checking
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int err_to_integer(char *s)
{
	int idx = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* why does this make main return 255? */
	for (idx = 0;  s[idx] != '\0'; idx++)
	{
		if (s[idx] >= '0' && s[idx] <= '9')
		{
			result *= 10;
			result += (s[idx] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints an error message to standard error
 * @info: a pointer to the parameter and return information structure
 * @error_type: string containing error type to be printed
 * Return: void
 */
void print_error(info_t *info, char *error_type)
{
	_eputs(info->filename);
	_eputs(": ");
	print_digits(info->line_number, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_type);
}

/**
 * print_digits - function prints a decimal (integer) number (base 10)
 * @num: the number to print
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_digits(int num, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, char_count = 0;
	unsigned int abs_num, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (num < 0)
	{
		abs_num = -num;
		__putchar('-');
		char_count++;
	}
	else
		abs_num = num;
	current = abs_num;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_num / i)
		{
			__putchar('0' + current / i);
			char_count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	char_count++;

	return (char_count);
}
/**
 * to_string- converts a number to a string in the specified base
 * @n: the number to convert
 * @b: the base to use for conversion
 * @f: flags to modify conversion behavior
 *
 * Return: pointer to resulting string
 */
char *to_string(long int n, int b, int f)
{
	static char *a;
	static char buf[50];
	char s = 0;
	char *p;
	unsigned long num = n;

	if (!(f & CONVERT_UNSIGNED) && n < 0)
	{
		num = -n;
		s = '-';
	}
	a = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buf[49];
	*p = '\0';

	do {
		*--p = a[num % b];
		num /= b;
	} while (num != 0);

	if (s)
		*--p = s;

	return (p);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @str: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *str)
{
	int idx;

	for (idx = 0; str[idx] != '\0'; idx++)
	if (str[idx] == '#' && (!idx || str[idx - 1] == ' '))
	{
		str[idx] = '\0';
		break;
	}
}
