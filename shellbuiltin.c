#include "myshell.h"

/**
 * exit_ - exits the shell
 * @info: pointer to a struct containing potential arguments.
 * used to maintain constant function prototype.
 *
 * Return: exits with a given exit status (0) if info->argv[0] != "exit"
 */
int exit_(info_t *info)
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
 * cd_ - changes the current directory of the process
 * @info: structure containing potential arguments
 *        constant function prototype
 *
 * Return: Always 0
 */
int cd_(info_t *info)
{
	char *current_dir, *new_dir, buffer[1024];
	int chdir_ret;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
		new_dir = _getenv(info, "HOME=");
		if (!new_dir)
			chdir_ret = /* what should this be? */
				chdir((new_dir = _getenv(info, "PWD=")) ? new_dir : "/");
		else
			chdir_ret = chdir(new_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = 0
			chdir((new_dir = _getenv(info, "OLDPWD=")) ? new_dir : "/");
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
		_set_envvar(info, "OLDPWD", _getenv(info, "PWD="));
		_set_envvar(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * help_ - prints help message to the standard output
 * @info: pointer to struct containing potential arguments
 * Return: 0 on success, or -1 on error
 */
int help_(info_t *info)
{
	char **args;

	args = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*args); /* temporary workaround */
	return (0);
}
