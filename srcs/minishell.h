/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 13:49:06 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/06 13:49:07 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** --------------------------------- Defines -----------------------------------
*/

#ifndef MINISHELL_H
# define MINISHELL_H
# define S_Q 1
# define D_Q 2
# define S_CHEVRON O_TRUNC
# define D_CHEVRON O_APPEND

# define HEREDOC "./.heredoc"
# define CMD 1
# define ARG 2
# define INPUT 4
# define DINPUT 8
# define OUTPUT 16
# define DOUTPUT 32
# define VAR 64

/*
** -------------------------- External Headers ---------------------------------
*/

# include "libft.h"
# include <limits.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>

/*
** ------------------------- Structure Definitions -----------------------------
*/

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
	struct s_token	*previous;
}					t_token;

typedef struct s_allcmd
{
	int				i_type;
	int				o_type;
	char			*cmd;
	char			*cmdpath;
	t_token			*inputf;
	t_token			*inputl;
	t_token			*dinputf;
	t_token			*dinputl;
	t_token			*outputf;
	t_token			*outputl;
	t_token			*doutputf;
	t_token			*doutputl;
	t_token			*argf;
	t_token			*argl;
	t_token			*varf;
	t_token			*varl;
	struct s_allcmd	*next;
	struct s_allcmd	*previous;
}					t_allcmd;

typedef struct s_ms
{
	int			index;
	int			g_envp_len;
	int			last_output;
	int			tab_size;
	char		quoteflag;
	char		tokenflag;
	char		*line;
	char		cd[PATH_MAX + 1];
	char		*inputdata;
	int			fd_pipe;
	char		**tab;

	t_token		*env_first;
	t_token		*env_last;
	t_allcmd	*allcmd;
	t_allcmd	*first_cmd;
	t_allcmd	*last_cmd;
}					t_ms;

typedef struct s_var
{
	int		name_length;
	int		start;
	int		value_length;
	char	*value;
}					t_var;

typedef struct s_pipe
{
	int		index;
	int		split_flag;
}					t_pipe;

/*
** ------------------------- Enum Definitions ----------------------------------
*/

typedef enum e_error
{
	CMD_NOT_FOUND,
	EXPORT_UNVALID_IDENTIFIER,
	UNSET_UNVALID_IDENTIFIER,
	UNVALID_PATH,
	TOO_MANY_ARGS,
	HOME_NOT_SET,
	PATH,
	IS_DIRECTORY,
	UNEXPECTED_TOKEN,
	NUMERIC_ARGUMENT_REQUIRED,
	SYNTAX_ERROR,
	NO_SUCH_FILE_DIRECTORY,
	I_REDIRECTION_ERROR,
	ERROR_RETRIEVING_CURRENT_DIRECTORY
}				t_elem_error;

/*
** -------------------------- Global variables ---------------------------------
*/

typedef struct s_environment
{
	int		g_pid;
	int		output_ctrls;
	int		is_ctrl;
	int		heredoc;
	int		fd_heredoc;
	int		fd_in;
	int		fd_out;
}				t_environment;

t_environment	g_env;

/*
** -----------------------------------------------------------------------------
** ------------------------------- Sources -------------------------------------
** -----------------------------------------------------------------------------
*/

/*
** ---------------------------------- init.c -----------------------------------
*/

void	ms_init_env_list(t_ms *ms, char *envp[]);
void	ms_init_cmd(t_ms *ms);
int		ms_add_last(char *content, t_ms *ms,
			t_token **first, t_token **last);
int		ms_add_last2(char *content, t_ms *ms,
			t_token **first, t_token **last);

/*
** --------------------------------- quotes.c ----------------------------------
*/

char	ms_quoteflag(t_ms *ms, char c);
void	ms_remove_quotes(t_ms *ms, char *token);

/*
** --------------------------------- parsing ------------------------------------
*/

int		ms_parsing(t_ms *ms);
char	**ms_pipe_split(t_ms *ms, char *line);
int		ms_dollar(t_ms *ms, char **token);
char	**ft_split_quote(char const *s, t_ms *ms);

/*
** --------------------------------- path.c ----------------------------------
*/
char	*ms_join_path(char const *s1, char const *s2);
int		ms_path(t_ms *ms, char *bash_cmd, t_allcmd *allcmd);

/*
** ---------------------------------- utils.c ----------------------------------
*/

char	*ms_get_var_value(t_token *env, char *var, int size);

/*
** ---------------------------------- error.c -----------------------------------
*/

void	error_msg(int error, char *str, t_ms *ms);

/*
** ---------------------------------- free.c -----------------------------------
*/

void	ms_free_all_lists(t_ms *ms);
void	ms_free_tokenlist(t_token **token);
void	ms_free_and_init(char **str);
void	ms_free_and_init_dtab(char **tab);

/*
** ------------------------------------ token.c --------------------------------
*/

int		ms_token_to_struct(t_ms *ms, t_allcmd *allcmd, char *content);
char	*ms_get_next_token(t_ms *ms, char *line);
int		ms_split_in_tokens(t_ms *ms);
void	ms_record_quotef(t_ms *ms);

/*
** --------------------------------- token_utils.c -----------------------------
*/

t_token	*get_token(char *content, t_token *token);
void	remove_env_token_from_list(t_ms *ms, t_token *token);
int		ms_get_index(char *content, int *sign);
int		get_var_name(t_ms *ms, t_token **token,
			char *content, int index);
void	update_var(t_ms *ms, t_token *var);

/*
** --------------------------------- commands ----------------------------------
*/

int		ms_builtins(t_ms *ms, t_allcmd *allcmd);
void	ms_echo(t_ms *ms, t_token *args);
void	ms_export_unset(t_ms *ms, t_token *temp,
			void (*f)(t_ms *, char *, int, int));
void	ms_export(t_ms *ms, char *content, int index, int sign);
void	ms_unset(t_ms *ms, char *content, int index, int sign);
void	ms_cd(t_ms *ms, t_allcmd *allcmd);
void	ms_env(t_ms *ms, t_token *env, char declare);
void	ms_pwd(t_ms *ms);
void	ms_exit(t_ms *ms, t_token *argf);
void	ms_execve(t_ms *ms, t_allcmd *allcmd);

/*
** ---------------------------------- fork.c ----------------------------------
*/

void	ms_fork(t_allcmd *allcmd, t_ms *ms);

/*
** ------------------------------- redirections.c ------------------------------
*/

int		ms_redirections(t_ms *ms, t_allcmd *allcmd);
int		ms_all_id_redirection(t_ms *ms, t_token *input);
int		get_fd(t_ms *ms, char *path, int o_flag, mode_t mode);

/*
** ------------------------------- control.c ----------------------------------
*/

void	rl_replace_line(const char *text, int clear_undo);
void	ft_sigint(int n);
void	ft_sigquit(int n);

#endif
