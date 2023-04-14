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
		_eputchar(BUF_FLUSH);
		read_status = get_input(info);
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
 * find_builtin_command - searches for a built-in command in the command line
 * @info: pointer to struct containing current command line information
 *
 * Return: integer status code:
 * -1 if built-in not found,
 * 0 if built-in executed successfully,
 * 1 if built-in found but not successful,
 * -2 if built-in signals exit()
 */
int find_builtin_command(info_t *info)
{
	int index, builtin_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _exit_shell},
		{"env", _print_env},
		{"help", _show_help},
		{"history", _show_history},
		{"setenv", _set_envvar},
		{"unsetenv", _unset_envvar},
		{"cd", _ch_dir},
		{"alias", _manage_alias},
		{NULL, NULL}
	};

	for (index = 0; builtintbl[index].type; index++)
		if (_strcmp(info->argv[0], builtintbl[index].type) == 0)
		{
			info->line_count++;
			builtin_ret = builtintbl[index].func(info);
			break;
		}
	return (builtin_ret);
}

/**
 * find_command - finds and executes a command in PATH
 * @info: pointer to the info_t struct containing command info
 *
 * This function finds a command
 * in the directories listed in the PATH environment variable
 * and executes it. If the command is not found, it prints an error message.
 *
 * Return: void
 */
void find_command(info_t *info)
{
	char *cmd_path = NULL;
	int index, arg_count;

	info->cmd_name = info->argv[0];

	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	for (index = 0, arg_count = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			arg_count++;

	/* If there are no arguments, return */
	if (!arg_count)
		return;

	cmd_path = find_path(info, _getenv(info, "PATH="), info->argv[0]);

	if (cmd_path)
	{
		info->cmd_name = cmd_path;
		fork_cmd(info);
	}
	else
	{
	/* If the command is not found, print an error message */
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_exec_cmd - forks a process and executes the command
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
		if (execve(info->path, info->argv, get_environ(info)) == -1)
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
