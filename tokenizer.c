#include "myshell.h"

/**
* **strtow- splits a string into words. Repeat delimiters are ignored
* @string: the input string
* @delim: the delimeter string
* Return: a pointer to an array of strings, or NULL on failure
*/
char **strtow(char *string, char *delim)
{
	int i, j, k, m, num_words = 0;
	char **words;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; string[i] != '\0'; i++)
	if (!is_delimiter(string[i], delim) && (is_delimiter(string[i + 1],
						delim) || !string[i + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	words = malloc((1 + num_words) * sizeof(char *));
	if (!words)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delimiter(string[i], delim))
			i++;
		k = 0;
		while (!is_delimiter(string[i + k], delim) && string[i + k])
			k++;
		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			words[j][m] = string[i++];
		words[j][m] = 0;
	}
	words[j] = NULL;
	return (words);
}

/**
* **strtow2 - splits a string into words
* @str: the input string
* @delim: the delimiter character
* Return: a pointer to an array of strings, or NULL on failure
*/
char **strtow2(char *str, char delim)
{
	int i, j, k, m, num_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delim && str[i + 1] == delim) ||
		    (str[i] != delim && !str[i + 1]) || str[i + 1] == delim)
			num_words++;
	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (str[i] == delim && str[i] != delim)
			i++;
		k = 0;
		while (str[i + k] != delim && str[i + k] && str[i + k] != delim)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
