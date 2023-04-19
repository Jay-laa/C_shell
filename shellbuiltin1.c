#include "'myshell.h"

/**
 * past - prints the history list, one command by line, preceded
 * with line numbers, starting at 0.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int past(info_t *info)
{
    /* Call print_list to display the history */
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - removes the alias associated with the given string
 * @info: structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @str: the string representing the alias
 *
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *equal_sign_pos, temp;
	int ret;

	equal_sign_pos = _strchr(str, '=');
	if (!equal_sign_pos)
		return (1);
	temp = *equal_sign_pos;
	*equal_sign_pos = 0;
	ret = delete_node_at_idx(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*equal_sign_pos = temp;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: structure containing potential arguments
 * @alias_str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *alias_str)
{
	char *equal_sign_pos;

	equal_sign_pos = _strchr(alias_str, '=');
	if (!equal_sign_pos)
		return (1);
	if (!*++equal_sign_pos)
		return (unset_alias(info, alias_str));

	unset_alias(info, alias_str);
	return (add_node_end(&(info->alias), alias_str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @alias_node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *alias_node)
{
	char *equal_sign_pos = NULL, *alias_str = NULL;

	if (alias_node)
	{
		equal_sign_pos = _strchr(alias_node->str, '=');
		for (alias_str = alias_node->str; alias_str <= equal_sign_pos; alias_str++)
			_putchar(*alias_str);
		_putchar('\'');
		_puts(equal_sign_pos + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * nickname - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int nickname(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
