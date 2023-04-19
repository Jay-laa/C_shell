#include "myshell.h"

/**
 * is_command - Determines if a file is an executable command
 * @info: Pointer to the info struct containing command info
 * @path: Path to the file to check
 *
 * Return: 1 if the file is an executable command, 0 otherwise
 */

int is_command(info_t *info, char *path)
{
	struct stat file_info;

	(void)info;

	if (!path || stat(path, &file_info))
		return (0);

	if (file_info.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars - duplicates characters from a string
 * @str: the string to copy characters from
 * @start: the index to start copying from
 * @stop: the index to stop copying at
 *
 * Return: pointer to new buffer
 */
char *duplicate_chars(char *str, int start, int stop)
{
	static char buffer[1024];
	int v, w = 0;

	for (w = 0, v = start; v < stop; v++)
	{
		if (str[v] != ':')
		{
			buffer[w] = str[v];
			w++;
		}
	}
	buffer[w] = '\0';
	return (buffer);
}

/**
 * find_command_path - finds the full path of a command in the PATH string
 * @info: the info struct
 * @path_str: the PATH string
 * @cmd: the command to find
 *
 * Return: the full path of cmd if found or NULL
 */
char *find_command_path(info_t *info, char *path_str, char *cmd)
{
	int index = 0, start_pos = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_str[index] || path_str[index] == ':')
		{
			path = duplicate_chars(path_str, start_pos, index);
			if (!*path)
				strcat(path, cmd);
			else
			{
				strcat(path, "/");
				strcat(path, cmd);
			}
			if (is_command(info, path))
				return (path);
			if (!path_str[index])
				break;
			start_pos = index;
		}
		index++;
	}
	return (NULL);
}
