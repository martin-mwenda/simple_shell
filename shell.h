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
} myli_t

int prompt(char **env);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
size_t get_line(char **str);
int leng_str(char *str, int pos, char delm);
char *ignore_space(char *str);
char **token_zer(char *str, char *delm);
char **c_str_tok(char *str, char *delm);
char *st_cat(char *dest, char *src);
char *dup_s(char *str);
char *copy_str(char *dest, char *src);
int comp_str(char *s1, char *s2);
int c_d(char **str, myli_t *env, int num);
int built_in(char **token, myli_t *env, int num, char **command);
void not_inter(myli_t *env);
char *w_hch(char *str, myli_t *env);
int ex_tc(char **s, myli_t *env, int num, char **command);
int _execve(char *argv[], myli_t *env, int num);
void fr_dbptr(char **str);
void fr_linkl(myli_t *list);
int pr_env(char **str, myli_t *env);
char *br_env(char *str, myli_t *env);
myli_t *environ_ll(char **env);
myli_t *add_endde(myli_t **head, char *str);
size_t print_list(myli_t *h);
int del_node_index(myli_t **head, int index);
int _unsetenv(myli_t **env, char **str);
int _setenv(myli_t **env, char **str);
int find_env(myli_t *env, char *str);
void cant_find(char *str, int num, myli_t *env);
void cantchange_dir(char *str, int c_n, myli_t *env);
void illegal_numb(char *str, int c_n, myli_t *env);
char *con_atos(int num);

#endif
