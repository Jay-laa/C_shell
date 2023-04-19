#include "myshell.h"

/**
* get_history_file_path - gets the path of history file
* @info: structure containing potential arguments.
*
*
* Return: allocated string containing history file
*/

char *get_history_file_path(info_t *info)
{
	char *buffer, *folder;

	folder = getenv_(info, "HOME=");
	if (!folder)
	return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(folder) + _strlen(HIST_FILE) + 2));
	if (!buffer)
	return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, folder);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
* write_history - creates a file, or appends to an existing file
* @info: the parameter struct
*
* Return: 1 on success, else -1
*/
int write_history(info_t *info)
{
	ssize_t fd;   /*file_descriptor. */
	char *hist_file = get_history_file_path(info);
	list_t *node = NULL;

	if (!hist_file)
		return (-1);

	fd = open(hist_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(hist_file);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
* read_history_file - reads history from file
* @info: the parameter struct
*
* Return: histcnt on success, 0 otherwise
*/
int read_history_file(info_t *info)
{
	int i, last = 0, linecnt = 0;
	ssize_t fd, rlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *fname = get_history_file_path(info);

	if (!fname)
		return (0);

	fd = open(fname, O_RDONLY);
	free(fname);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			add_to_history(info, buff + last, linecnt++);
			last = i + 1;
		}
	if (last != i)
		add_to_history(info, buff + last, linecnt++);
	free(buff);
	info->histcnt = linecnt;
	while (info->histcnt-- >= HIST_MAX)
		delete_node_at_idx(&(info->history), 0);
	renumber_history_list(info);
	return (info->histcnt);
}

/**
* add_to_history - adds entry to a history linked list
* @info: Structure containing potential arguments.
* @entry: buffer
* @line_count: the history linecount, histcount
*
* Return: Always 0
*/
int add_to_history(info_t *info, char *entry, int line_count)
{
	list_t *node = NULL;

	if (info->history)
	node = info->history;
	add_node_end(&node, entry, line_count);

	if (!info->history)
	info->history = node;
	return (0);
}

/**
* renumber_history_list - renumbers the history linked list after changes
* @info: struct containing potential arguments
*
* Return: the new hist count
*/
int renumber_history_list(info_t *info)
{
	list_t *current_node = info->history;
	int count = 0;

	while (current_node)
	{
		current_node->num = count++;
		current_node = current_node->next;
	}
	return (info->histcount = count);
}
