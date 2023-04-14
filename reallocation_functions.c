#include "myshell.h"

/**
* _memset2 - fills memory with a constant byte
* @dest: the pointer to the memory area
* @val: the byte to fill *dest with
* @nbytes: the amount of bytes to be filled
* Return: (dest) a pointer to the memory area dest
*/
char *_memset2(char *dest, char val, unsigned int nbytes)
{
	unsigned int i;

	for (i = 0; i < nbytes; i++)
		dest[i] = val;
	return (dest);
}

/**
* free_strings - frees a string of strings
* @str_arr: string of strings
*/
void free_strings(char **str_arr)
{
	char **p = str_arr;

	if (!str_arr)
		return;
	while (*str_arr)
		free(*str_arr++);
	free(p);
}

/**
* realloc_array - dynamically reallocates a block of memory
* @old_ptr: pointer to previously allocated memory block
* @old_size: size of the previously allocated memory block in bytes
* @new_size: size of the new memory block in bytes
*
* Return: pointer to the new memory block
*/
void *realloc_array(void *old_ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!old_ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(old_ptr), NULL);
	if (new_size == old_size)
		return (old_ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)old_ptr)[old_size];
	free(old_ptr);
	return (new_ptr);
}
