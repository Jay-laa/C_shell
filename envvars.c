#include "myshell.h"

/**
* context - prints the current environment
* @info: pointer to a struct containing potential arguments.
*  Used to maintain constant function prototype.
* Return: Always 0
*/
int context(info_t *info)
{
	print_liststr(info->env);
	return (0);
}
/**
* getenv_ - gets the value of an environment variable
* @info: Structure containing information about the shell
* @name: Name of the environment variable
* Return: Pointer to the value of the environment variable if found,
* otherwise NULL.
*/
char *getenv_(info_t *info, const char *name)
{
	list_t *env_node = info->env;
	char *value;

	while (env_node)
	{
	value = starts_with(env_node->str, name);
	if (value && *value)
	return (value);
	env_node = env_node->next;
	}
	return (NULL);
}

/**
* assign - Initialize a new environment variable,
*             or modify an existing one
* @info: Structure containing potential arguments.
*        Used to maintain constant function prototype.
* Return: Always 0.
*/
int assign(info_t *info)
{
	if (info->args != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
* unassign - Remove an environment variable
* @info: Structure containing command arguments and environment variables
* Used to maintain constant function prototype.
* Return: Always 0
*/
int unassign(info_t *info)
{
	int i;

	if (info->args == 1)
	{
		_eputs("Missing arguments. Please specify one or more env var to remove.\n");
		return (1);
	}
	for (i = 1; i < info->args; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
* populate_envvar - populates environment linked list
* @info: Structure containing potential arguments
* This function populates the environment linked list with the current
* environment variables.
* Return: Always 0
*/
int populate_envvar(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
