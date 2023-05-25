Simple_shell in C programming team project
==========================================

Simple_shell repository contains everything needed in coding your own shell.The shell program can interact with  the operating system to execute commands.It uses system calls to interact with the operating system and manage processes.The commands are in executable files which can be found in directories in the system's search path.

# Requirements

### General
- The editors allowed are vi, vim and emacs
- Files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
- There should be a README.md file at the root of the folder of the project
- The shell should not have memoty leaks
- There should be no more than 5 functions in a file
- An author's file at the root of your repository


### Allowed files and system calls:
- access (man 2 access)
- chdir (man 2 chdir)
- close (man 2 close)
- closedir (man 3 closedir)
- execve (man 2 execve)
- exit (man 3 exit)
- _exit (man 2 _exit)
- fflush (man 3 fflush)
- fork (man 2 fork)
- free (man 3 free)
- getcwd (man 3 getcwd)
- getline (man 3 getline)
- isatty (man 3 isatty)
- kill (man 2 kill)
- malloc (man 3 malloc)
- open (man 2 open)
- opendir (man 3 opendir)
- perror (man 3 perror)
- read (man 2 read)
- readdir (man 3 readdir)
- signal (man 2 signal)
- stat (__xstat) (man 2 stat)
- lstat (__lxstat) (man 2 lstat)
- fstat (__fxstat) (man 2 fstat)
- strtok (man 3 strtok)
- wait (man 2 wait)
- waitpid (man 2 waitpid)
- wait3 (man 2 wait3)
- wait4 (man 2 wait4)
- write (man 2 write)

### Use this to compile:
`
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
`

This wil compile all the '.c' files and change the output's name to 'hsh'.

### Testing the output:
=============
$ ./hsh

($) 

hsh main.c shell.c

$ exit
$


Immediately after compilation, a file will be created called **hsh** that can be executed by entering  ```./hsh``` in your shell.

The output after the execution of program should look like this:
```
$|
```
A  prompt in the shape of a dollar sign and then you can enter your command in the shell.

## Implementation of a Shell Program

This process is divided into three parts:


### Parsing

This part involves parsing the entered input to separate components which are the command and the arguments or any piping symbols.

### Executing

This takes place after parsing where the shell needs to execute the commands and the arguments.This leads to the creation of a new process that uses the fork and exec system calls.

### Built-in commands

Apart from the external commands , the shell  has the built in commands and they provide basic functionality such as displaying output.



## Built-in Functions

Built-in functions  are mainly executd by parent process so as to modify the state of the parent. If child executes, ,the changes will not be there when the child exits thus the functions are called in execute instead of creating a whole new process.


