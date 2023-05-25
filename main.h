#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

/*coverting values and chars*/
#define SWITCH_UNSIGNED		2
#define CONVERT_TO_LOWERCASE	1

/*size of buffer used for reading/writing data*/
#define READ_BUF_SIZE 1024
#define BUFFER_FLUSH -1
#define WRITE_BUF_SIZE 1024

/*Parsing and tokenizing input*/
#define ENABLE_GETLINE 0
#define ENABLE_STRTOK 0

/*Different types of modes of commands*/
#define COMMAND_AND		2
#define COMMAND_CHAIN		3
#define COMMAND_DEFAULT		0
#define COMMAND_OR		1

extern char **environ;

/*shell history*/
#define HISTORY_FILE	".my_shell_history"
#define MAX_HISTORY_SIZE	4096

#define DATA_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


/**
 * struct listnode - represents a singly linked list
 *
 * @value: the integer associated with nodes
 * @str: the string associated with the node
 * @next: a pointer to next node in the linked list
 */

typedef struct listnode
{
	int value;
	char *str;
	struct listnode *next;
} listn_t;


/**
 * struct programdata - this hold the data and information related
 *                      when executing a command
 * @arg: this is used to represent a single arguement
 * @argv: this is used to represent an array of strings
 * @path: stores the path information
 * @argc: stores the number of arguements
 * @line_number: this represents the line count related to command execution
 * @error_num: this stores the error number or code
 * @linenumber_flag: this represents a flag related to the line count
 * @filenm: this stores the file name
 * @envs: this is a linked list for storing environmental variables
 * @hist: this is a linked list for storing command history
 * @aliases: a linked list for storing command aliases
 * @environ: this is an array of environmental variables
 * @envs_change: a flag that shows if an environment has changed
 * @exec_status: status info related to plrogram execution
 * @comm_buff: a pointer to a command chain buffer to manage memory
 * @comm_buff_type: this is the type of command chain buffer
 * @rd_fd: this is the read file descriptor
 * @histnum: this represents the history count
 */

typedef struct programdata
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_number;
	int error_num;
	int linenumber_flag;
	char **comm_buff;
	listn_t *envs;
	listn_t *hist;
	listn_t *aliases;
	char **environ;
	int envs_change;
	int exec_status;
	char *filenm;
	int rd_fd;
	int comm_buff_type;
	int histnum;
} command_t;

/**
 * struct builtin_command - represents a pointer to a char(name) and
 *                    a pointer to the associated function(members)
 * @name: the name of the built-in function
 * @func: the associated function
 */

typedef struct builtin_command
{
	char *name;
	int (*func)(command_t *);
} command_table;

/*parsing*/
int exec_cmd(command_t *, char *);
char *_substr(char *, int, int);
char *get_path(command_t *, char *, char *);


/*errorfunctions*/
void _errputs(char *);
int _errputchar(char s);
int put_c_fd(char c, int fd);
int put_s_fd(char *string, int fd);

/*error*/
int print_integer(int , int );
int err_atoi(char *str);
void display_error(command_t *data, char *errorinfo);
char *num_to_base(long int number, int base, int flag);
void delete_comments(char *str);

/*built_in*/
int _changeDirectory(command_t *data);
int _exitprogram(command_t *data);
int print_help(command_t *data);

/*stringfunction*/
char *_strcat_(char *dest, char *src);
int _strlen_(char *);
char *is_prefix(const char *haystack, const char *needle);
int _strcmp_(char *str1, char *str2);

/*allhistory*/
int store_history(command_t *data);
char *find_history_file(command_t *data);
int read_history(command_t *data);
int renumber_hist(command_t *data);
int add_to_history(command_t *data, char *buffer, int linenum);

/*listfunction1*/
listn_t *new_head(listn_t **head, const char *str, int value);
listn_t *append_node(listn_t **head, const char *str, int value);
void release_list(listn_t **head_list);
size_t display_list_strings(const listn_t *head);
int unlink_node_at_index(listn_t **head, unsigned int index);

/*lists*/
ssize_t find_node_index(listn_t *h, listn_t *node);
listn_t *find_node_prefix(listn_t *node, char *pref, char c);
size_t display_list(const listn_t *head);
char **list_to_array(listn_t *head);
size_t list_count(const listn_t *head);

/*memory*/
int let_free(void **p);

/*memory1*/
void *_reallocate(void *ptr, unsigned int oldSize, unsigned int newSize);
char *_memset_(char *m, char x, unsigned int n);
void free_arr(char **pArr);

/*environ*/
char *search_env(command_t *data, const char *varname);
int mod_env_var(command_t *data);
int unset_env(command_t *data);
int display_env(command_t *data);
int init_env_list(command_t *data);

/*strings*/
void _puts(char *s);
char *_strcpy_(char *dest, char *src);
int _putchar(char c);
char *_strdup_(const char *s);

/*shell_loop*/

void fork_exec(command_t *data);
void get_cmd(command_t *data);
int get_builtin(command_t *data);
int hsh(command_t *data, char **av);
	
/*main*/
int main(int ac, char **av);

/*getenv*/
int rm_env_variable(command_t *data, char *envar);
int _setenv_(command_t *data, char *envar, char *value);
char **_getenviron(command_t *data);

/*findinfo*/
void initialize_data(command_t *data, char **av);
void reset_info(command_t *data);
void data_free(command_t *data, int full);

/*exit*/
char *_strchr_(char *str, char c);
char *_strncpy_(char *dest, char *src, int c);
char *_strncat_(char *dest, char *src, int b);

/*alias*/
int modify_alias(command_t *data);
int detect_chain(command_t *data, char *buffer, size_t *ptr);
void verify_chain(command_t *data, char *buf, size_t *pt, size_t n, size_t len);
int substitute_var(command_t *data);
int update_string(char **prev, char *new);

/*getline*/
ssize_t buffer_input(command_t *data, char **buff, size_t *len);
ssize_t input_chain(command_t *data);
ssize_t read_buffer(command_t *data, char *buf, size_t *p);
int _readline(command_t *data, char **ptr, size_t *length);
void handleSIGINT(__attribute__((unused))int signal_num);

/*builtinfunctions*/
int _setAlias(command_t *data, char *string);
int _unsetAlias(command_t *data, char *string);
int display_alias(listn_t *node);
int handle_alias(command_t *data);
int show_history(command_t *data);

/*atoi*/
int _atoi(char *str);
int _isalpha(int c);
int is_delimeter(char c, char *delimeter);
int is_interactive(command_t *data);

/*error*/
int print_integer(int value, int fd);
void display_error(command_t *data, char *errorinfo);
int err_atoi(char *str);
char *num_to_base(long int number, int base, int flag);
void delete_comments(char *str);


/*tokenize*/
char **splitstr1(char *s, char *del);
char **splitstr2(char *string, char delim);


#endif









