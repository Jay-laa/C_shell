#include "myshell.h"

/**
* get_input - buffers chained commands
* @info: parameter struct
* @buffer: address of buffer
* @buffer_size: address of len var
*
* Return: bytes read
*/
ssize_t get_input(info_t *info, char **buffer, size_t *buffer_size)
{
	ssize_t bytes_read = 0;
	size_t size_p = 0;

	if (!buffer_size)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytes_read = getline(buffer, &size_p, stdin);
#else
		bytes_read = _getline(info, buffer, &size_p);
#endif
		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{
				(buffer)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->histcount++);
			{
				*buffer_size = bytes_read;
				info->cmd_buf = buffer;
			}
		}
	}
	return (bytes_read);
}

/**
* getlinE - reads user input from stdin
* @info: struct containing shell info
*
* Return: number of bytes read
*/
ssize_t get_line(info_t *info)
{
	static char *chain_buf;
	static size_t chain_start, chain_end, chain_len;
	ssize_t bytes_read = 0;
	char **arg_ptr = &(info->arg), *command_start;

	_putchar(BUF_FLUSH);

	bytes_read = input_buffer(info, &chain_buf, &chain_len);
	if (bytes_read == -1) /* EOF */
		return (-1);

	if (chain_len)
	{
		chain_end = chain_start; /* init new iterator to current buf position */
		command_start = chain_buf + chain_start;

		check_command_chain(info, chain_buf, &chain_end, chain_start, chain_len);

		while (chain_end < chain_len) /* iterate to semicolon or end */
		{
			if (is_command_chain(info, chain_buf, &chain_end))
				break;
			chain_end++;
		}

		chain_start = chain_end + 1;
		if (chain_start >= chain_len)
		{
			chain_start = chain_len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*arg_ptr = command_start;
		return (_strlen(command_start));
	}

	*arg_ptr = chain_buf;
	return (bytes_read);
}

/**
* read_buf - reads data from a file descriptor into a buffer
* @info: pointer to the parameter struct
* @buffer: pointer to the buffer
* @buffer_size: pointer to the size of the buffer
*
* Return: number of bytes read
*/
ssize_t read_buf(info_t *info, char *buffer, size_t *buffer_size)
{
	ssize_t bytes_read = 0;

	if (*buffer_size)
	return (0);

	bytes_read = read(info->readfd, buffer, READ_BUF_SIZE);
	if (bytes_read >= 0)
	*buffer_size = bytes_read;

	return (bytes_read);
}

/**
* get_line - reads the next line of input from STDIN
* @info: struct containing information about the current command
* @buffer: address of pointer to buffer, preallocated or NULL
* @buf_size: size of preallocated ptr buffer if not NULL
*
* Return: length of the string read, or -1 on failure
*/
int get_line(info_t *info, char **buffer, size_t *buf_size)
{
	static char read_buf[READ_BUF_SIZE];
	static size_t read_buf_start, read_buf_end;
	size_t line_size;
	ssize_t read_result = 0, line_len = 0;
	char *line = NULL, *new_line = NULL, *end_of_line;

	line = *buffer;
	if (line && buf_size)
		line_len = *buf_size;
	if (read_buf_start == read_buf_end)
		read_buf_start = read_buf_end = 0;

	read_result = read_buf(info, read_buf, &read_buf_end);
	if (read_result == -1 || (read_result == 0 && read_buf_end == 0))
		return (-1);

	end_of_line = _strchr(read_buf + read_buf_start, '\n');
	line_size = end_of_line ? 1 + (unsigned int)
		(end_of_line - read_buf) : read_buf_end;
	new_line = _realloc(line, line_len,
			line_len ? line_len + line_size : line_size + 1);
	if (!new_line) /* MALLOC FAILURE! */
		return (line ? free(line), -1 : -1);

	if (line_len)
		_strncat(new_line, read_buf + read_buf_start,
				line_size - read_buf_start);
	else
		_strncpy(new_line, read_buf + read_buf_start,
				line_size - read_buf_start + 1);

	line_len += line_size - read_buf_start;
	read_buf_start = line_size;
	line = new_line;

	if (buf_size)
		*buf_size = line_len;
	*buffer = line;
	return (line_len);
}

/**
* sigint_handler - handles the SIGINT signal, blocking CTRL-C
* @sig_num: the signal number
*
* Return: void
*/
void sigint_handler(_attribute_((unused)) int sig_num)
{
	_puts("\033[0;31m\n"); /* set color to red */
	_puts("$ ");
	_puts("\033[0m"); /* reset color */
	_putchar(BUF_FLUSH);
}
