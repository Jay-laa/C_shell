#include "myshell.h"

/**
* input_buffer - buffers chained commands
* @info: parameter struct
* @buffer: address of buffer
* @buffer_size: address of len var
* Return: bytes read
*/
ssize_t input_buffer(info_t *info, char **buffer, size_t *buffer_size)
{
	ssize_t bytes_read = 0;
	size_t size_p = 0;

	if (!*buffer_size)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigint_handler);
#if USE_GETLINE
		bytes_read = getline(buffer, &size_p, stdin);
#else
		bytes_read = _getlinE(info, buffer, &size_p);
#endif
		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{
				(*buffer)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			add_to_history(info, *buffer, info->histcount++);
			{
				*buffer_size = bytes_read;
				info->cmd_buf = *buffer;
			}
		}
	}
	return (bytes_read);
}

/**
* get_input - reads user input from stdin
* @info: struct containing shell info
* Return: number of bytes read
*/
ssize_t get_input(info_t *info)
{
	static char *chain_buf;
	static size_t chain_start, chain_end, chain_len;
	ssize_t bytes_read = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	bytes_read = input_buffer(info, &chain_buf, &chain_len);
	if (bytes_read == -1) /* EOF */
		return (-1);
	if (chain_len)
	{
		chain_end = chain_start; /* init new iterator to current buf position */
		p = chain_buf + chain_start;

		check_var_chain(info, chain_buf, &chain_end, chain_start, chain_len);
		while (chain_end < chain_len) /* iterate to semicolon or end */
		{
			if (var_chain(info, chain_buf, &chain_end))
				break;
			chain_end++;
		}

		chain_start = chain_end + 1;
		if (chain_start >= chain_len)
		{
			chain_start = chain_len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (str_length(p));
	}

	*buf_p = chain_buf;
	return (bytes_read);
}

/**
* read_buffer - reads data from a file descriptor into a buffer
* @info: pointer to the parameter struct
* @buffer: pointer to the buffer
* @buffer_size: pointer to the size of the buffer
* Return: number of bytes read
*/
ssize_t read_buffer(info_t *info, char *buffer, size_t *buffer_size)
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
* _getlinE - reads the next line of input from STDIN
* @info: struct containing information about the current command
* @buffer: address of pointer to buffer, preallocated or NULL
* @buf_size: size of preallocated ptr buffer if not NULL
* Return: length of the string read, or -1 on failure
*/
int _getlinE(info_t *info, char **buffer, size_t *buf_size)
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

	read_result = read_buffer(info, read_buf, &read_buf_end);
	if (read_result == -1 || (read_result == 0 && read_buf_end == 0))
		return (-1);

	end_of_line = string_find_char(read_buf + read_buf_start, '\n');
	line_size = end_of_line ? 1 + (unsigned int)
		(end_of_line - read_buf) : read_buf_end;
	new_line = realloc_array(line, line_len, line_len ? line_len
			+ line_size : line_size + 1);
	if (!new_line) /* MALLOC FAILURE! */
		return (line ? free(line), -1 : -1);

	if (line_len)
		string_concatenate_n(new_line, read_buf + read_buf_start,
				line_size - read_buf_start);
	else
		string_copy_n(new_line, read_buf + read_buf_start,
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
* Return: void
*/
void sigint_handler(__attribute__((unused)) int sig_num)
{
	_puts("\033[0;31m\n"); /* set color to red */
	_puts("$ ");
	_puts("\033[0m"); /* reset color */
	_putchar(BUF_FLUSH);
}
