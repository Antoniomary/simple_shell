#ifndef SHELL_H
#define SHELL_H

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define true 1
#define false 0

#define NO 0
#define YES 1

#define INT_MODE true
#define NON_INT_MODE false

#define SH_NAME info->av[0] /* for shell program name */
#define FILENAME info->av[1] /* for file as input to shell */

#define NONFILE 1 /* filename exists not as regular file */
#define ISFILE 2 /* filename exist as regular file */

#define NUL 0
#define OR 1
#define AND 2
#define SEMI 3

#define NO_ERROR 0
#define ERROR 1

extern char **environ;

/**
 * struct _alias_t - a struct to hold an alias.
 * @name: pointer to the name for the command or text to be aliased.
 * @val: pointer to the value to be substituted for name.
 * @name_val: pointer to both name and val in the format name=value.
 * @next: pointer to next node.
 */
typedef struct _alias_t
{
	char *name;
	char *val;
	char *name_val;
	struct _alias_t *next;
} alias_t;

/**
 * struct variables - a struct to hold variables.
 * @name: pointer to the name for the text to be substituted..
 * @val: pointer to the value to be substituted for name.
 * @next: pointer to next node.
 */
typedef struct variables
{
	char *name;
	char *val;
	struct variables *next;
} var_t;

/**
 * struct shell_t - a struct to necessary information that concern the shell.
 * @fd: holds the file descriptor number.
 * @sh_mode: specifies if shell is in interactive mode or not.
 * @nth_line: hold the nth number of command given to shell.
 * @av: argument vector pass to the program i.e after running shell.
 * @argc: command line argument count used to start shell program.
 * @argv: command line argument vector used to start shell program.
 * @env_size: defines the number of environment variables.
 * @env: defines the environment variables.
 * @exit_status: holds the exit status code of immediate command.
 * @exit: a flag variable to determine when to exit the shell.
 * @alias_head: head node to a struct.
 * @var_head: head node to a struct.
 */
typedef struct shell_t
{
	int fd;
	int sh_mode;
	unsigned int nth_line;
	char **av;
	int argc;
	char **argv;
	int env_size;
	char **env;
	int exit_status;
	int exit;
	alias_t *alias_head;
	var_t *var_head;
} list;

/**
 * struct builtin_funcs - a struct.
 * @name: first argument.
 * @func: second argument (a function pointer).
 */
typedef struct builtin_funcs
{
	char *name;
	int (*func)(list *);
} Builtins;

int (*parser(char *command))(list *info);


/********************* SH_START_UP********************************/
void sh_start_up(list *info, char **av);
void shell_init(list *info);
int env_init(list *info);
void var_init(list *info);

/********************* BUILT-INS ********************************/
int _cd(list *info);
int _exit_(list *info);
int _env(list *info);
int _mysetenv(list *info);
int _myunsetenv(list *info);


/********************* SUB1_MAIN ********************************/
void display_prompt(void);
char *read_line(list *info);
char **token_input(list *info, char *line);
void find_path(list *info, char **path, char *command);
int execute_cmd(list *info);

/********************* SUB2_MAIN ********************************/
void sig_hand(int signum);
int is_all_var_def(list *info);
void define_user_var(list *info);
void sort_var_from_cmd(list *info);


/********************* SYNTAX_CHECKER ****************************/
int syntax_error_check(list *info, char *line);
int unclosed_quote(list *info, char *s);
int check_cmd_separators(list *info, char *s);
int check_error(list *info, char *s, int *cmd, int *sep, int one, int c);

/********************* WHICH FUNCTION ****************************/
char *_which(list *info, char *cmd);


/********************* GETLINE FUNCTION **************************/
int _getline(char **line, size_t *n, int fd);


/********************* STRTOK FUNCTION ***************************/
char *_strtok(char *str, const char *delim);
char *_strtok_o_quote(char *s, const char *delim);
char *strcmd_and_sep(char *s, const char *delim, char *sep, char **saveptr);


/********************* FUNCTION TO REMOVE COMMENT ****************/
int remove_quotes_comment(char **argv);
int remove_comment(char *line);

/********************* SUBSTITUTE_VAR_ALIAS **********************/
void substitute_var_alias(list *info);
char *get_alias(alias_t *head, char *str);
char *get_var(var_t *head, char *str);


/********************* UTILS_STR1 ********************************/
int _strlen(const char *s);
char *_strcpy(char *dest, char *src);
char *_strncpy(char *dest, char *src, int n);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, int n);

/********************* UTILS_STR2 ********************************/
char *_strdup(char *s);
char *_strchr(const char *s, int c);
char *str_concat(const char *s1, const char *s2, char c);
char *_strcat(char *str, char *s1, char *s2, char *s3, char *s4);
char *str_dup_cat(char *s1, char *s2, char *s3, char *s4);

/********************* UTILS_I/O *********************************/
int _putchar(int c);
int eputchar(int c);
void _puts(const char *s, int newline);
void eputs(const char *s1, const char *s2, const char *s3, int newline);
void _perror(char *s, unsigned int n, char *s1, char *s2, char *s3, char *s4);

/********************* UTILS_CTYPE *******************************/
int _isdigit(int c);
int _isallowed(int c);
int _isalpha(int c);
int is_op(int c);
int _isspace(int c);

/********************* UTILS_ALLOC *******************************/
char *alloc(int size);
int realloc_env(list *info);
void *_realloc(void *ptr, int old_size, int new_size);


/********************* UTILS ************************************/
int isfile(list *info, char *filename);
int get_exit_status(const char *s);
char *_itoa(int n, char *num);
char *space_skipper(char *entry);
char *ignore_quotes(char *s, int c);

/********************* UTILS1 ***********************************/
int custom_atoi(char *num);

char *_getenv(list *info, const char *name);
int _setenv(list *info, const char *name, const char *value, int overwrite);
int _unsetenv(list *info, const char *name);

/********************* ALIAS ************************************/
alias_t *creat_alias(char *entry);
int add_replace_alias(alias_t **head, alias_t *new);
int find_print_alias(alias_t *head, char *name);
int print_alias(alias_t *head);
void free_alias(alias_t *head);

/********************* VARIABLES ************************************/
var_t *creat_var(char *entry);
void add_replace_var(var_t **head, var_t *new);
void free_var(var_t *head);
void update_exitstatus_var(list *info);
int is_all_var_def(list *info);

/********************* FREE ************************************/
void free_env(list *info);
void free_env_alias_vars(list *info);

#endif /* SHELL_H */
