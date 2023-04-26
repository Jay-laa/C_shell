#include "myshell.h"

/**
* add_node_list - adds a node to the start of a linked list
* @head: address of pointer to head node
* @str: string field of the new node
* @idx: index of the node used by history
* Return: size of list
*/
list_t *add_node_list(list_t **head, const char *str, int idx)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset2((void *)new_head, 0, sizeof(list_t));
	new_head->number = idx;
	if (str)
	{
		new_head->str = string_duplicate(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
* add_node_end - adds a node to the end of the list
* @head: address of pointer to head node
* @str: str field of node
* @num: node index used by history
* Return: pointer to the new node
*/
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *curr_node;

	if (!head)
		return (NULL);

	curr_node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset2((void *)new_node, 0, sizeof(list_t));
	new_node->number = num;
	if (str)
	{
		new_node->str = string_duplicate(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (curr_node)
	{
		while (curr_node->next)
			curr_node = curr_node->next;
		curr_node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
* print_liststr - prints only the string element of a list_t linked list
* @head: pointer to the first node of the list
* Return: the size of the list
*/
size_t print_liststr(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return (count);
}

/**
* delete_node_at_idx - deletes node at given index
* @head: address of pointer to first node
* @idx: index of node to delete
* Return: 1 on success, 0 on failure
*/
int delete_node_at_idx(list_t **head, unsigned int idx)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!idx)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == idx)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
* free_linked_list - frees all nodes of a list
* @head: address of pointer to head node
* Return: void
*/
void free_linked_list(list_t **head)
{
	list_t *current_node, *next_node, *head_node;

	if (!head || !*head)
		return;
	head_node = *head;
	current_node = head_node;
	while (current_node)
	{
		next_node = current_node->next;
		free(current_node->str);
		free(current_node);
		current_node = next_node;
	}
	*head = NULL;
}
