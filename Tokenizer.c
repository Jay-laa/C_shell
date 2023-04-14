#include "myshell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @input_str: the input string
 * @delim_str: the delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *input_str, char *delim_str)
{
	int idx1, idx2, word_len, char_idx, num_words = 0;
	char **str_arr;

	if (input_str == NULL || input_str[0] == 0)
		return (NULL);
	if (!delim_str)
		delim_str = " ";

	for (idx1 = 0; input_str[idx1] != '\0'; idx1++)
		if (!is_delim(input_str[idx1], delim_str) && (is_delim(input_str[idx1 + 1], delim_str) || !input_str[idx1 + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);

	str_arr = malloc((1 + num_words) * sizeof(char *));
	if (!str_arr)
		return (NULL);

	for (idx1 = 0, idx2 = 0; idx2 < num_words; idx2++)
	{
		while (is_delim(input_str[idx1], delim_str))
			idx1++;
		word_len = 0;
		while (!is_delim(input_str[idx1 + word_len], delim_str) && input_str[idx1 + word_len])
			word_len++;
		str_arr[idx2] = malloc((word_len + 1) * sizeof(char));
		if (!str_arr[idx2])
		{
			for (char_idx = 0; char_idx < idx2; char_idx++)
				free(str_arr[char_idx]);
			free(str_arr);
			return (NULL);
		}
		for (char_idx = 0; char_idx < word_len; char_idx++)
			str_arr[idx2][char_idx] = input_str[idx1++];
		str_arr[idx2][char_idx] = 0;
	}
	str_arr[idx2] = NULL;
	return (str_arr);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @delim: the delimiter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char delim)
{
	int idx, word_idx, word_len, char_idx, numwords = 0;
	char **words;

	if (str == NULL || str[0] == 0)
		return (NULL);

	for (idx = 0; str[idx] != '\0'; idx++)
	{
		if ((str[idx] != delim && str[idx + 1] == delim) ||
		    (str[idx] != delim && !str[idx + 1]) || str[idx + 1] == delim)
			numwords++;
	}

	if (numwords == 0)
		return (NULL);

	words = malloc((1 + numwords) * sizeof(char *));
	if (!words)
		return (NULL);

	for (idx = 0, word_idx = 0; word_idx < numwords; word_idx++)
	{
		while (str[idx] == delim && str[idx] != delim)
			idx++;

		word_len = 0;
		while (str[idx + word_len] != delim && str[idx + word_len] && str[idx + word_len] != delim)
			word_len++;

		words[word_idx] = malloc((word_len + 1) * sizeof(char));
		if (!words[word_idx])
		{
			for (char_idx = 0; char_idx < word_idx; char_idx++)
				free(words[char_idx]);
			free(words);
			return (NULL);
		}

		for (char_idx = 0; char_idx < word_len; char_idx++)
			words[word_idx][char_idx] = str[idx++];

		words[word_idx][char_idx] = 0;
	}

	words[word_idx] = NULL;
	return (words);
}
