#include "myshell.h"

/**
* _eputs - prints the input string to standard error
* @str: the string to be printed
*
* Return: nothing
*/
void _eputs(char *str)
{
	int index = 0;

	if (!str)
		return;

	while (str[index] != '\0')
	{
		_eputchar(str[index]);
		index++;
	}
}

/**
* _eputchar - writes the character ch to stderr
* @ch: The character to print
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _eputchar(char ch)
{
	static int idx;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || idx >= WRITE_BUF_SIZE)
	{
		write(2, buf, idx);
		idx = 0;
	}
	if (ch != BUF_FLUSH)
		buf[idx++] = ch;
	return (1);
}

/**
* putfd - writes the character c to given file descriptor
* @ch: The character to print
* @fd: The file descriptor to write to
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int putfd(char ch, int fd)
{
	static int buf_pos;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || buf_pos >= WRITE_BUF_SIZE)
	{
		write(fd, buf, buf_pos);
		buf_pos = 0;
	}

	if (ch != BUF_FLUSH)
		buf[buf_pos++] = ch;

	return (1);
}

/**
* puts_fd - writes the string to the specified file descriptor
* @str: the string to be written
* @fd: the file descriptor to write to
* Return: the number of characters written
*/
int puts_fd(char *str, int fd)
{
	int count = 0;

	if (!str)
		return (0);

	while (*str)
	{
		count += putfd(*str++, fd);
	}

	return (count);
}
