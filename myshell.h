#ifndef MYSHELL_H
#define MYSHELL_H

/*
 * myshell_h - Header file for myshell
 * Contains all function prototypes, structures, and macros for myshell.
 * This shell supports input and output redirection, piping, and background
 * processes. Built-in commands include cd, exit, env, setenv, and unsetenv.
 *
 * Authors: Joy Emojorho and John Ebhohimen
 */

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>
#include <stdarg.h>
#include <ctype.h>

/*macros*/
#define PATH_MAX_LENGTH 4096
#define PATH_SEPARATOR ":"
#define PROMPT "$ "
#define MAX_TOKENS 1024
#define BUFFER_SIZE 1024

/* read and write input/output */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/*
 * command chaining is used to execute multiple commands
 * sequentially or conditionally
 */
#define CMD_NORM	0	/* Normal command */
#define CMD_OR		1	/* Command with "or" condition */
#define CMD_AND		2	/* Command with "and" condition */
#define CMD_CHAIN	3	/* Command chaining */

/*
 * convert a string to a number
 * convert letters to lowercase or treat the number as unsigned
 */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* Input parsing */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* History file to be used */
#define HIST_FILE	".custom_shell_history"
#define HIST_MAX	4096

/*
 * Environment variables: an external variable
 * that contains the environment variables of the shell
 */
extern char **environ;
extern __sighandler_t signal(int __sig, __sighandler_t __handler);

/* Struct declarations */

/*
 * struct list_t - contains singly linked list
 * @str: a string
 * @number: the integer field
 * @next: points to the next node
 *
 * Description: This struct represents a node in a singly linked list
 * of strings and integers
 */
typedef struct list_s
{
    char *str;
    int number;
    struct list_s *next;
} list_t;


/*
 * struct liststr -  represents a node in a singly linked list of strings
 *
 * @number: the integer field
 * @str: a string
 * @next_node: points to the next node
 *
 *
 * Description: This structure represents a node in a singly linked list of
 * strings and integers. It contains an integer value, a string value, and a
 * pointer to the next node in the list. This structure is used to implement
 * history functionality in the shell, where each command entered by the user
 * is stored in a linked list for later retrieval.
 */
typedef struct liststr_s
{
        int number;
        char *str;
        struct liststr_s *next_node;
} liststr;

/**
 * struct info_s - holds information about the shell
 *
 * @args: the command line arguments
 * @env: the environment variables
 * @status: the exit status of the last command
 * @line_count: the error count
 * @history: the list of command history
 * @isatty: whether the shell is attached to a terminal
 * @pid: the process ID of the shell
 * @input_fd: the file descriptor for input
 * @output_fd: the file descriptor for output
 */
typedef struct info_s
{
	char **args;
	char *cmd_name;
	char **env;
	int linecount_flag;
	unsigned int line_count;
	char* filename;
	int status;
	char *cmd_path;
	struct liststr_s *history;
	int isatty;
	int type;
	pid_t pid;
	int input_fd;
	int output_fd;
	char **argv;
	int err_num;
	int interactive;

} info_t;

/**
 * struct builtin_table - Searches for built-in commands and executes them
 */
typedef struct builtin_table
{
	char *cmd_name;
	char *type;
	void (*function)(void);
	int (*func)(info_t *);
	int (*cmd_func)(info_t *);
} builtin_table;


/**
 * struct cmd_info - contains information about a command
 * @arg_str: a string generated from getline containing arguments
 * @args: an array of strings generated from arg_str
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on, count this line of input
 * @fname: the program filename
 * @local_env: linked list local copy of the environment variables
 * @history: the history node
 * @alias: the alias node
 * @envp: custom modified copy of the envir var from the LL local_env
 * @env_changed: on if environment variables were changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd ; chain buffer, for memory management
 * @cmd_buf_type: the type of command chaining (||, &&, or ;)
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct cmd_info
{
	char *arg_str;
	char **args;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *local_env;
	list_t *history;
	list_t *alias;
	char **envp;
	int env_changed;
	int status;
	char **cmd_buf;	/* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type;
	int readfd;
	int histcount;
} cmd_info_t;

/* initialize struct info_t with NULLs and 0s */
#define MY_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - struct for a built-in command
 * and its corresponding function
 * @type: the string representation of the built-in command
 * @func: a function pointer to the implementation of the built-in command
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_struct;

/* Function prototypes for hsh_loop.c */
int start_hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_exec_cmd(info_t *);

/* Function prototypes for command_parser.c */
int is_command(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_command_path(info_t *, char *, char *);

/* Function prototypes for loophsh.c */
int loophsh(char **);

/* Function prototypes for error_handling.c */
void error_puts(char *);
int error_putchar(char);
int putfd(char c, int fd);
int puts_fd(char *str, int fd);

/* Function prototypes for string_utils.c  */
int str_length(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *string_concat(char *, char *);

/* Function prototypes for string1_utils.c */
char *string_copy(char *, char *);
char *string_duplicate(const char *);
void _puts(char *);
int _putchar(char);

/* Function prototypes for string_operations.c  */
char *string_copy_n(char *, char *, int);
char *string_concatenate_n(char *, char *, int);
char *string_find_char(char *, char);

/* Function prototypes for tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* Function prototypes for reallocation_functions.c */
char *_memset(char *, char, unsigned int n);
void free_tokens(char **);
void *realloc_array(void *, unsigned int, unsigned int);

/* Function prototypes for memory.c */
int free_ptr(void **);

/* Function prototypes for integer.c */
int interactive(info_t *);
int is_delimiter(char, char *);
int is_alpha(int);
int to_integer(char *);

/* Function prototypes for error_utils.c */
int err_to_integer(char *);
void print_error(info_t *, char *);
int print_digits(int, int);
char *to_string(long int, int, int);
void remove_comments(char *);

/* Function prototypes for shellbuiltins.c */
int exit_(info_t *);
int cd_(info_t *);
int help_(info_t *);

/* Function prototypes for shellbuiltins1.c */
int history_(info_t *);
int unset_alias(info_t *, char *);
int set_alias(info_t *, char *);
int alias_(info_t *);

/* Function prototypes for lineinput.c */
ssize_t get_input(info_t *, char **, size_t *);
ssize_t getlinE(info_t *);
ssize_t read_buf(info_t *, char **, size_t *);
int get_line(info_t *, char **, size_t *);
void sigint_handler(int);

/* Function prototypes for getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* Function prototypes for envvars.c */
int env_(info_t *);
char *getenv_(info_t *, const char *);
int setenv_(info_t *);
int unsetenv_(info_t *);
int populate_envvar(info_t *);

/* Function prototypes for getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* Function prototypes for file_history.c */
char *get_history_file_path(info_t *info);
int write_history(info_t *info);
int read_history_file(info_t *info);
int add_to_history(info_t *info, char *, int);
int renumber_history_list(info_t *info);

/* Function prototypes for linkedlist.c */
list_t *add_node_list(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_lists(const list_t *);
int delete_node_at_idx(list_t **, unsigned int);
void free_linked_list(list_t **);

/* Function prototypes for linkedlist1.c */
size_t list_length(const list_t *);
char **list_to_string(list_t *);
size_t print_lists(const list_t *);
list_t *find_node_starts(list_t *, char *, char);
ssize_t get_node_idx(list_t *, list_t *);

/* Function prototypes for varsubst.c */
int var_chain(info_t *, char *, size_t *);
void check_var_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_variables(info_t *);
int replace_str(char **, char *);

#endif /* MYSHELL_H */
