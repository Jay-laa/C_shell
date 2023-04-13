0x16. C - Simple Shell

This is a simple shell program written in C language. It can execute commands entered by the user and display their output. It supports basic features like command execution, piping,system call, bit manipulation, file managment, error handling ...
Shell is a simple UNIX command interpreter that replicates functionalities of the simple shell (sh).

List of allowed functions and system calls
access (man 2 access)
chdir (man 2 chdir)
close (man 2 close)
closedir (man 3 closedir)
execve (man 2 execve)
exit (man 3 exit)
_exit (man 2 _exit)
fflush (man 3 fflush)
fork (man 2 fork)
free (man 3 free)
getcwd (man 3 getcwd)
getline (man 3 getline)
getpid (man 2 getpid)
isatty (man 3 isatty)
kill (man 2 kill)
malloc (man 3 malloc)
open (man 2 open)
opendir (man 3 opendir)
perror (man 3 perror)
read (man 2 read)
readdir (man 3 readdir)
signal (man 2 signal)
stat (__xstat) (man 2 stat)
lstat (__lxstat) (man 2 lstat)
fstat (__fxstat) (man 2 fstat)
strtok (man 3 strtok)
wait (man 2 wait)
waitpid (man 2 waitpid)
wait3 (man 2 wait3)
wait4 (man 2 wait4)
write (man 2 write)

Requirements
To run this shell, you will need a Unix-based operating system and a C compiler. The following tools and libraries are also required:

GNU Compiler Collection (GCC)
Allowed editors: vi, vim, emacs
All files were compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
codes use the Betty style.
The simple shell has no known memory leaks

Installation
Clone this repository onto your local machine.
git clone https://github.com/Jay-laa/simple-shell.git

cd in to the cloned directory: cd simple_shell

Create an executable using:
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

Run the shell program.
either in interative mode ./hsh or non-interactive mode echo "pwd" | ./hsh

Examples
Example of error with sh:

$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
Same error with our program hsh:

$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$

Usage

This shell supports basic Unix commands and features, including:

Running executables in the current directory or in directories listed in the PATH environment variable.
Command line arguments.
Piping between commands.
Input/output redirection using the '<' and '>' characters.
To exit the shell, type exit

Contribute?
If you would like to contribute to this project, please fork the repository and submit a pull request.

Bugs
No known bugs exists within the program as of this writing.

Authors
JOY EMOJORHO | https://github.com/Jay-laa
JOHN EBHOHIMEN |https://github.com/mudiajohn

License
Given the open source nature of the project, no special licenses or license whatsoever is needed to use, modify, and redistribute the simple_shell program. 
