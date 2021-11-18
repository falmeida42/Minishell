#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include "libft.h"
#include "parser.h"
#include "map.h"

typedef struct	s_mini {
	char	**argv;
	char	*str;
	int		pid;
	bool	exit;
	t_map	*env;
} t_mini;

t_mini	g_mini;

//error management
void	error_output(char type);
//error management

//free utility
void	free_struct(char *input);
void	free_argv();

//commands.c
void	ft_pwd(void);
void	ft_exit(char *input);
void	ft_echo(void);
void	ft_cd(void);
void	ft_exec(void);
void	ft_env(void);
int		ft_export(void);
void	ft_unset(void);
//commands.c

void	get_signal(int signal);

//main.c
char    *pwd(void);
//main.c

// env variable
int		env_unset(char *key);
t_map	*env_set(char *key, char *value);
char	*env_get(char *key);

#endif
