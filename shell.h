#ifndef SHELL
#define SHELL

#include <wait.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * struct list - linked list for environmental variables
 * @var: holds environmental variable string
 * @next: points to next node
 */
typedef struct list
{
	char *var;
	struct list *next;
} myli_t;


int prompt(char **en);
void *_realloc(void *ptr, unsigned int oldSize, unsigned int newSize);
size_t get_line(char **str);
int leng_str(char *str, int pos, char delm);
char *ignore_space(char *input);
char **token_zer(char *str, char *delim);
char **c_str_tok(char *str, char *delm);
char *st_cat(char *dest, char *src);
char *dup_s(char *str);
char *copy_str(char *destination, char *source);
int comp_str(char *str1, char *str2);
int c_d(char **str, myli_t *envList, int num);
int built_in(char **token, myli_t *env, int num, char **command);
void not_inter(myli_t *env);
char *w_hch(char *str, myli_t *env);
int ex_ct(char **str, myli_t *env, int num, char **command);
int _execve(char **command, myli_t *envList, int num);
void fr_dbptr(char **stringArray);
void fr_linkl(myli_t *list);
int pr_env(char **command, myli_t *envList);
char *br_env(char *variableTitle, myli_t *envList);
myli_t *environ_ll(char **env);
myli_t *add_endde(myli_t **head, char *str);
size_t print_list(myli_t *head);
int del_node_index(myli_t **head, int index);
int unput_env(myli_t **env, char **str);
int put_env(myli_t **env, char **str);
int find_env(myli_t *env, char *variable_name);
void cant_find(char *user_command, int command_number, myli_t *env);
void cantchange_dir(char *str, int c_n, myli_t *env);
void illegal_numb(char *argument, int command_number, myli_t *env);
char *con_atos(int number);
int mcount_del(char *str, char delim);
char *rem_del(char *str, char delim);
int count_del(char *str, char delim);
int exe_cd(myli_t *envList, char *curDir, char *newDir, char *erMsg, int liNum);
int con_set(myli_t **env, char *name, char *dir);
char *conc_s(char *destination, char *source);
int custi(char *str);
void c_dir(myli_t *envList, char *currentDir);
char *str_dup(char *str, int excludeBytes);
void ctrl_D(int characters_read, char *user_command, myli_t *env);
void ctrl_c(int signal);
char *space_ig(char *input);
void cm_frexit(char **cmd, myli_t *envList);
int zero_count(int number);


#endif
