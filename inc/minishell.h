/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:31:31 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/22 23:59:21 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>

# include "../libft/inc/libft.h"
# include "../ft_printf/ft_printf.h"

# define SUCCESS 0
# define ERROR 404

/**
 * ERROR MESSAGES
*/
# define ERR_MALLOC "Memory allocation error\n"
# define ERR_EOF1 "minishell: unexpected EOF while looking for matching `"
# define ERR_EOF2 "\'\nminishell: syntax error: unexpected end of file\n"
# define ERR_EX ": numeric argument required\n"

/*
 * SIGNAL STATE
*/
# define IN_SHELL 1
# define IN_PROGRAM 2

extern int g_exit_status;

/*
		LITTERAL	--> (0)		An argument
		PIPE		-->	(1)		pipe (|)
		RI			-->	(2)		redirecting input (<)
		HEREDOC		-->	(3)		here documents (<<)
		RO			-->	(4)		redirecting output (>)
		ARO			-->	(5)		appending redirecting output (>>)
*/
typedef enum e_type
{
	LITTERAL,
	PIPE,
	RI,
	HEREDOC,
	RO,
	ARO,
}	t_type;

typedef struct s_token
{
	char			*token;
	t_type			type;
	bool			quoted;
	bool			empty;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char				*key;
	char				*values;
	struct s_env		*next;
}	t_env;

typedef struct s_heredoc
{
	int		fd_heredoc;
	char	*heredoc;
}	t_heredoc;

typedef struct s_exec
{
	char	**args;
	char	**envp;
	char	*path;
	int		fd_heredoc;
	int		sstdin;
	int		sstdout;
	int		in;
	int		out;
	t_heredoc	*hd;
}	t_exec;


/**
 * Tokenizer
*/
t_token	**tokenize(char *line, t_env *env);
void	replace_vars(t_token **token_lst, t_env *env);
void	skip_single_quotes(int *i, char *str);
bool	single_dollar(t_token *token);
char	*update_dollarless_token(t_token *token, int i, \
int marker, char *new_token);

/**
 * New Tokenizer fubction (need to delete some previous functions)
*/
void	replace_varsn(t_token **token_lst, t_env *env);
char	*update_token(char *token, int *i, int marker, char *updated_token);
char	*change_var(char *token, int *i, char *updated_token, t_env *env);
char	*single_dollarn(char *updated_token);
char	*double_dollar(char *updated_token);
char	*exit_status_var(char *updated_token);
bool	special_cases(char *token, char **updated_token, int *i);
void	remove_token_quotes(t_token **token_lst);

/**
 * t_token struct utils
*/
t_token	*create_new_token(char *str, int type);
void	add_back_token(t_token **token_lst, t_token *token);
t_token	*get_last_token(t_token *lst);
void	delete_first_token(t_token **token_lst);
char	*add_litteral_dollar(char *dollarless_token, int *i, char *tkn);
void	set_new_token(t_token *token, char *dollarless);
size_t	token_size(t_token *token_lst);
char	**token_lst_into_char(t_token *token_lst);
void	delete_token(t_token **token_lst, t_token *token);

/**
 * Environment
*/
t_env	*init_env(char **envp);

/**
 * t_env struct utils
*/
t_env	*get_last_env(t_env *lst);
t_env	*create_new_env(char *key, char *values);
char	*get_env_key(char *envp);
char	*get_env_values(char *envp);
char	**env_lst_into_char(t_env *env);
size_t	env_size(t_env *env);
char	*lookup_values(char *key, t_env *env);
void	add_back_env(t_env **env_lst, t_env *env);

/**
 * Utils
*/
int		ft_isspace(char c);
int		is_quote(char c);
int		is_metachar(char c);
int		is_double_redirection(char *str);
char	*ft_strndup(char *s1, size_t size);
int		ft_strcmp(char *s1, char *s2);
void	free_array(char **arr);
bool	closed_quotes(char *str);
bool 	unclosed_quotes(char *line);

//Builtins
int		pwd(void);
int		env_builtin(t_env *env);
int		echo(t_token *token_lst);
void	print_export(t_env *env);
int		cd(t_token	*token_lst, t_env *env);
int		unset(t_token *token_lst, t_env **env);
int		export(t_token *token_lst, t_env **env);
int	ft_exit(t_env *env, t_token **token, t_exec *exec);

//Exec
void	init_exec(t_exec *exec, t_heredoc *hd);
void	free_exec(t_exec *exec, t_token *token);
void	handle_command(t_token **token_lst, t_env *env);
int		check_args(t_token *token);
void	exec_command(t_exec	*exec);
int		is_bultin(t_token *token_lst);
int		exec_bultin(t_token *token_lst, t_env *env);
int		exec_exit(t_token **token, t_env *env, t_exec *exec);

//Redirections
t_exec	*handle_redirection(t_token **token_lst, t_env *env, t_heredoc *hd, int i);
t_heredoc	*check_heredocs(t_token	*token, t_env *env);
int		end_heredoc(t_token *token, char *line);
int		change_standard_fd(t_token *token_lst, t_exec *exec);
void	remove_redirection(t_token **head);
void	restore_fd(t_exec *exec, t_token *token);

//Pipex + Utils
int		pipex(t_token **token, t_env *env, int count, t_heredoc *hd);
size_t	count_pipes(t_token *token);
int		**setup_pipes(t_token *token);
void	free_pipes(int **pipes);
void	close_pipes(int **pipes, int limiter);
t_token	*get_command(t_token *token, int index);
int		translate_error(int	nbr);

/**
 * Freeing
*/
void	free_all(t_token **token_lst, t_env *env);
void	free_all_env(t_env *env_lst);
void	free_all_token(t_token **token_lst);

/**
 * Error management
*/
void	log_error(char *str);

/**
 * Signals management
*/
void	signal_handling(int status);
void	ctrl_d_handler(char *line, t_token **token_lst, t_env *env);

/**
 * Garbage collector  -- TO ERASE
*/
typedef struct s_gc_node
{
	struct s_gc_node	*prev;
	struct s_gc_node	*next;
	size_t				size;
}	t_gc_node;

/**
 * We keep the adress of the first and last node
 * to "travel" faster in the structure
*/
typedef struct s_gc_glob
{
	t_gc_node	*first_node;
	t_gc_node	*last_node;
	size_t		total_size;
	size_t		nb_allocs;
}	t_gc_glob;

void	gc_init(t_gc_glob *gc);
void	*gc_malloc(t_gc_glob *gc, size_t size);
void	gc_free(t_gc_glob *gc, void **ptr);
void	gc_free_all(t_gc_glob *gc);

/**
 * TO ERASE IN THE END
*/
void	print_env(t_env *env);

#endif
