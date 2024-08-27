/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:04:38 by lumarque          #+#    #+#             */
/*   Updated: 2024/06/04 16:25:50 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <ncurses.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <term.h>

# define GREEN "\033[1m\033[32m"
# define RED "\033[1m\033[31m"
# define BLUE "\033[0;34m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

# define STOP 0
# define CONTINUE 1
# define RESTORE 2

# define FALSE 0
# define TRUE 1

# define EXEC 420
# define REDIR 421
# define PIPE 422
# define HEREDOC 423
# define APPEND 424

# define MAXARGS 50

# define SPACES " \t\n\v\f\r"
# define OPERATORS "<|>"

# define BAD_OP "|&;()"
# define UNSUPPORT "&*(){};\\"
# define NOT_EXP "|></ \t\n\v\f\r"

# define ERROR_HEAD "minishell: "
# define ERROR_QUOTE "unclosed quotes"
# define ERROR_SYNTAX "syntax error near unexpected token `"
# define ERROR_HERE_DOC "unexpected EOF while looking for matching `"
# define ERROR_OPT "options are not supprted"

# define SIGRESTORE 1
# define SIGHEREDOC 2
# define SIGCHILD 3
# define SIGIGNORE 4

extern int			g_exit;

typedef struct s_env
{
	char	**e_name;
	char	**e_content;
	int		size_env;
}				t_env;

typedef struct s_cmd
{
	int	type;
}				t_cmd;

typedef struct s_pipe
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}				t_pipe;

typedef struct s_redir
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	int		mode;
	int		fd;
}				t_redir;

typedef struct s_here
{
	int		type;
	char	*eof;
	int		mode;
	int		fdin;
	int		fdout;
	t_cmd	*cmd;
}				t_here;

typedef struct s_exec
{
	int		type;
	char	*argv[MAXARGS];
}				t_exec;

typedef struct s_shell
{
	char	*user_line;
	int		size_line;
	char	*ps;
	char	*es;
	t_env	env;
	t_env	env_sort;
	char	**envp;
	t_cmd	*cmd;
	int		status;
	int		pid;
	int		flag_pipe;
	char	*oldpwd;
	int		exp_quote;
}				t_shell;

// env_and_export
void				init_shell_and_env(t_shell *shell, t_env *env);
void				update_env(t_env *env, char *name, char *new_value);
char				*env_get(t_env *env, char *name);
char				*env_get_exp(t_env *env, char *name);
void				selection_sort_env(t_env *env, int i, int j);

// expand
void				expand_arg(t_shell *shell, char **arg);
int					expand_free(char *key, int i, int j, char **line);
int					expand(char *key, int i, int j, char **line);
void				trim_quotes(char *arg, int *len);
void				arg_insert_null(char *arg);

// process_line file
int					prepare_line(t_shell *shell);

// parser
t_cmd				*mk_exec(void);
t_cmd				*mk_pipe(t_cmd *left, t_cmd *right);
t_cmd				*mk_redir(char *file, int mode, int fd, t_cmd *cmd);
t_cmd				*mk_here(char *eof, t_cmd *cmd);
int					parse(t_shell *shell);
int					peek(t_shell *shell, char *op);
int					gettoken(t_shell *sh, char **token);
t_cmd				*parsepipe(t_shell *shell);

// run_cmd
void				run_cmd(t_shell *shell, t_cmd *cmd);
void				run_exec(t_shell *shell, t_exec *cmd);
void				run_redir(t_shell *shell, t_redir *cmd);
void				check(int result, char *msg, int exit);
int					check_fork(void);
void				run_heredoc(t_shell *shell, t_here *here);

// built-in
int					run_builtin(t_shell *shell, t_exec *cmd);
void				ms_echo(t_exec *cmd);
void				ms_cd(t_shell *shell, t_exec *cmd);
bool				ms_chdir(t_shell *shell, char *path);
void				ms_pwd(t_shell *shell, t_exec *cmd);
void				ms_export(t_shell *shell, t_exec *cmd);
void				ms_unset(t_shell *shell, t_exec *cmd);
void				ms_env(t_shell *shell, t_exec *cmd);
void				ms_exit(t_shell *shell, t_exec *cmd);

// sig
void				signal_handler(int sig);

// error_frees
int					print_error_syntax(t_shell *shell, char *msg, int exit);
int					print_error(t_shell *shell, char *msg, char *msg2,
						int exit);
int					print_error_unsupport(t_shell *sh, char *msg, int exit);
int					print_error_export(t_shell *sh, char *cmd, char *arg,
						int exit);
void				free_exit(t_shell *shell);
void				free_env(t_env *env);
void				free_cmd(t_cmd *cmd);
void				free_split(char **split);
void				clean_exit(t_shell *shell);

#endif