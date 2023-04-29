#include "myshell.h"

/**
* var_chain - check if current char in buffer is a chain delimeter
* @info: the parameter struct
* @buf: the char buffer
* @p: address of current position in buf
* Return: 1 if chain delimeter, 0 otherwise
*/
int var_chain(info_t *info, char *buf, size_t *p)
{
	size_t pos = *p;

	if (buf[pos] == '|' && buf[pos + 1] == '|')
	{
		buf[pos] = 0;
		pos++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[pos] == '&' && buf[pos + 1] == '&')
	{
		buf[pos] = 0;
		pos++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[pos] == ';') /* found end of this command */
	{
		buf[pos] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = pos;
	return (1);
}

/**
* check_var_chain - checks to see if continue chaining based on last status
* @info: the parameter struct
* @buf: the char buffer
* @p: address of current position in buf
* @start_pos: starting position in buf
* @buf_len: length of buf
* Return: Void
*/
void check_var_chain(info_t *info, char *buf,
		size_t *p, size_t start_pos, size_t buf_len)
{
	size_t current_pos = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[start_pos] = 0;
			current_pos = buf_len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[start_pos] = 0;
			current_pos = buf_len;
		}
	}

	*p = current_pos;
}

/**
* replace_alias - replaces an alias in the tokenized string
* @info: the parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_alias(info_t *info)
{
	int i;
	list_t *match_node;
	char *match_ptr;

	for (i = 0; i < 10; i++)
	{
		match_node = find_node_starts(info->alias, info->argv[0], '=');
		if (!match_node)
			return (0);
		free(info->argv[0]);
		match_ptr = string_find_char(match_node->str, '=');
		if (!match_ptr)
			return (0);
		match_ptr = string_duplicate(match_ptr + 1);
		if (!match_ptr)
			return (0);
		info->argv[0] = match_ptr;
	}
	return (1);
}

/**
* replace_variables - replaces variables in the tokenized string
* @info: pointer to parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_variables(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_str(&(info->argv[i]),
			string_duplicate(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_str(&(info->argv[i]),
			string_duplicate(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = find_node_starts(info->env, &(info->argv[i][1]), '=');
		if (node)
		{
			replace_str(&(info->argv[i]),
			string_duplicate(string_find_char(node->str, '=') + 1));
			continue;
		}
		replace_str(&(info->argv[i]), string_duplicate(""));

	}
	return (0);
}

/**
* replace_str - replaces string
* @old: address of old string
* @new: new string
* Return: 1 if replaced, 0 otherwise
*/
int replace_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
