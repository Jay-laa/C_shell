#include "myshell.h"

/**
* get_environ - Returns a copy of the string array containing environment variables
* @info: Pointer to struct containing shell info
*
* Return: Always 0
*/
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
	info->environ = list_to_strings(info->env);
	info->env_changed = 0;
	}

	return (info->environ);
}

/**
* _unsetenv - Remove an environment variable
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* @var: the string env var property
* Return: 1 on delete, 0 otherwise
*/
int _unsetenv(info_t *info, char *var)
{
	list_t *curr_node = info->env;
	size_t index = 0;
	char *p;

	if (!curr_node || !var)
		return (0);

	while (curr_node)
	{
		p = starts_with(curr_node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			curr_node = info->env;
			continue;
		}
		curr_node = curr_node->next;
		index++;
	}
	return (info->env_changed);
}

/**
* _setenv - Initialize a new environment variable,
* or modify an existing one
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* @variable: the string env var property
* @value: the string env var value
*  Return: Always 0
*/
int _setenv(info_t *info, char *variable, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
		return (0);

	buf = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, variable);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
