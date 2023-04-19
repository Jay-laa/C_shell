#include "myshell.h"

/**
 * halt - exits the shell
 * @info: pointer to a struct containing potential arguments.
 * used to maintain constant function prototype.
 *
 * Return: exits with a given exit status (0) if info->argv[0] != "exit"
 */
int halt(info_t *info)
{
	int exit_status;

	if (info->argv[1]) /* If there is an argument after "exit" */
	{
		exit_status = err_to_integer(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = err_to_integer(info->argv[1]);
		return (-2);
	}
	info->err_num = -1; /* set error number to default */
	return (-2);
}

/**
 * change - changes the current directory of the process
 * @info: structure containing potential arguments
 *        constant function prototype
 *
 * Return: Always 0
 */
int change(info_t *info)
{
	char *current_dir, *new_dir, buffer[1024];
	int chdir_ret;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
		new_dir = getenv_(info, "HOME=");
		if (!new_dir)
			chdir_ret = /* what should this be? */
				chdir((new_dir = getenv_(info, "PWD=")) ? new_dir : "/");
		else
			chdir_ret = chdir(new_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!getenv_(info, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(getenv_(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = 0;
			chdir((new_dir = getenv_(info, "OLDPWD=")) ? new_dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);

	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", getenv_(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * assist - prints help message to the standard output
 * @info: pointer to struct containing potential arguments
 * Return: 0 on success, or -1 on error
 */
int assist(info_t *info)
{
	char **args;

	args = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*args); /* temporary workaround */
	return (0);
}
