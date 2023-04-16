#include "myshell.h"

/**
* clear_info - initializes fields of the info_t struct to NULL
* @info: pointer to the info_t struct to be initialized
*/
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
* set_info - initializes info_t struct
* @info: pointer to the info_t struct to initialize
* @av: pointer to an array of strings containing command-line arguments
*/
void set_info(info_t *info, char **av)
{
	int arg_count = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
	for (arg_count = 0; info->argv && info->argv[arg_count]; arg_count++)
		info->argc = arg_count;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
* free_info - frees info_t struct fields
* @info: pointer to the info_t struct
* @all: true if freeing all fields, false otherwise
*/
void free_info(info_t *info, int all)
{
	free_tokens(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (all)
	{
	if (!info->cmd_buf)
	free(info->arg);
	if (info->env)
	free_list(&(info->env));
	if (info->history)
	free_list(&(info->history));
	if (info->alias)
	free_list(&(info->alias));

	free_tokens(info->environ);
	info->environ = NULL;

	free_buffer((void **)info->cmd_buf);

	if (info->readfd > 2)
	close(info->readfd);

	_putchar(BUF_FLUSH);
	}
}
