#include "myshell.h"

/**
* list_length - determines length of linked list
* @head: pointer to first node
* Return: size of list
*/
size_t list_lenght(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}
	return (count);
}

/**
* list_to_string - returns an array of strings of the list->str
* @head: pointer to first node
* Return: array of strings
*/

char **list_to_string(list_t *head)
{
	list_t *curr_node = head;
	size_t node_count = list_length(head), j;
	char **strs;
	char *curr_str;

	if (!head || !node_count)
		return (NULL);

	strs = malloc(sizeof(char *) * (node_count + 1));
	if (!strs)
		return (NULL);

for (node_count = 0; curr_node; curr_node = curr_node->next, node_count++)
	{
		curr_str = malloc(str_length(curr_node->str) + 1);
		if (!curr_str)
		{
			for (j = 0; j < node_count; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		curr_str = string_copy(curr_str, curr_node->str);
		strs[node_count] = curr_str;
	}

	strs[node_count] = NULL;
	return (strs);
}

/**
* print_lists - prints all elements of a list_t linked list
* @head: pointer to first node
* Return: size of list
*/
size_t print_lists(const list_t *head)
{
	size_t node_count = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		node_count++;
	}
	return (node_count);
}

/**
* find_node_starts - returns node whose string starts with prefix
* @head: pointer to list head
* @prefix: string to match
* @next_char: the next character after prefix to match
* Return: match node or null
*/
list_t *find_node_starts(list_t *head, char *prefix, char next_char)
{
	char *match = NULL;

	while (head)
	{
		match = starts_with(head->str, prefix);
		if (match && ((next_char == -1) || (*match == next_char)))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
* get_node_idx - gets the index of a node
* @head_ptr: pointer to list head
* @node_ptr: pointer to the node
* Return: index of node or -1
*/
ssize_t get_node_idx(list_t *head_ptr, list_t *node_ptr)
{
	size_t node_count = 0;

	while (head_ptr)
	{
		if (head_ptr == node_ptr)
			return (node_count);
		head_ptr = head_ptr->next;
		node_count++;
	}
	return (-1);
}
