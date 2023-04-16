#include "myshell.h"

/**
 * start_hsh - main shell loop
 * @info: pointer to the info_t struct containing info about the shell
 * @av: array of arguments from main()
 *
 * Return: 0 on success, 1 on error, or an error code
 */
int start_hsh(info_t *info, char **av)
{
	ssize_t read_status = 0;	/* Status of input read */
	int builtin_result = 0;		/* Return value of built-in commands */

	while (read_status != -1 && builtin_result != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_putchar(BUF_FLUSH);
		read_status = get_input(info, NULL, NULL);
		if (read_status != -1)
		{
			set_info(info, av);
			builtin_result = find_builtin(info);
			if (builtin_result == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_result == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_result);
}

/**
 * find_builtin - searches for a built-in command in the command line
 * @info: pointer to struct containing current command line information
 *
 * Return: integer status code:
 * -1 if built-in not found,
 * 0 if built-in executed successfully,
 * 1 if built-in found but not successful,
 * -2 if built-in signals exit()
 */
int find_builtin(info_t *info)
{
	int index, builtin_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", (int (*)(info_t *)) exit_},
		{"env", (int (*)(info_t *)) env_},
		{"help", (int (*)(info_t *)) help_},
		{"history", (int (*)(info_t *)) history_},
		{"setenv", (int (*)(info_t *)) setenv_},
		{"unsetenv", (int (*)(info_t *)) unsetenv_},
		{"cd", (int (*)(info_t *)) cd_},
		{"alias", (int (*)(info_t *)) alias_},
		{NULL, NULL}
	};

	for (index = 0; builtintbl[index].type; index++)
		if (strcmp(info->argv[0], builtintbl[index].type) == 0)
		{
			info->line_count++;
			builtin_ret = builtintbl[index].func(info);
			break;
		}
	return (builtin_ret);
}

/**
 * find_cmd - finds and executes a command in PATH
 * @info: pointer to the info_t struct containing command info
 *
 * This function finds a command
 * in the directories listed in the PATH environment variable
 * and executes it. If the command is not found, it prints an error message.
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *cmd_path = NULL;
	int index, arg_count;

	info->cmd_path = info->argv[0];

	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	for (index = 0, arg_count = 0; info->args[index]; index++)
		if (!is_delim(info->args[index], " \t\n"))
			arg_count++;

	/* If there are no arguments, return */
	if (!arg_count)
		return;

	cmd_path = find_path(info, getenv(info, "PATH="), info->argv[0]);

	if (cmd_path)
	{
		info->cmd_path = cmd_path;
		fork_exec_cmd(info);
	}
	else
	{
	/* If the command is not found, print an error message */
		if ((interactive(info) || getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && find_cmd(info, info->argv[0]))
			fork_exec_cmd(info);
		else if (*(info->args) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a process and executes the command
 * @info: pointer to struct containing
 * information about the command to be executed
 *
 * Return: void
 */
void fork_exec_cmd(info_t *info)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		if (execve(info->cmd_path, info->argv, get_env(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
