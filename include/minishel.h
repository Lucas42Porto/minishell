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
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>


# define FALSE 0
# define TRUE 1

# define EXEC 420
# define PIPE 421
# define REDIR 422
# define HEREDOC 423
# define APPEND 424

# define MAXARGS 50

# define SPACES " \t\n\v\f\r"
# define OPERATORS "<|>"

# define ERROR_HEAD "minishell: "
# define ERROR_QUOTES "unclosed quotes"
# define ERROR_SYNTAX_PIPE "syntax error near unexpected token `|'"
# define ERROR_SYNTAX_PIPE2 "syntax error near unexpected token `||'"

# define SIGRESTORE 1
# define SIGHEREDOC 2
# define SIGCHILD 3
# define SIGIGNORE 4

extern int	g_exit;

typedef struct	s_env
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

typedef struct	s_redir
{
	int		type;
	char	*file;
	int		mode;
	int		fd;
	t_cmd	*cmd;
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
	int	type;
	char	*argv[MAXARGS];
}				t_exec;


typedef struct	s_shell
{
	t_env	env;
	char	**envp;

	char	**paths;

	char	*user_line;
	int		size_line;

	char	*ps;
	char	*es;

	t_cmd	*cmd;
}				t_shell;		

void	init_env_and_path(t_shell *shell, t_env *env);
void	extract_paths(t_shell *shell, char *path, int i);
char 	*get_content_env(t_shell *shell, char *name, int i);
void	init_env(t_shell *shell, t_env *env, char **tmp, int i);
void	malloc_name_content(t_env *env, char **envp, int i);
char	**ft_split_env(char **env, char **result, int *i);

void	ft_exec_cd(char *cmd, char *path, int ntokens);
void	ft_exec_pwd(char *cmd);
void	ft_exec_echo(char **cmd_args, char *cmd, int ntokens, int len_cmd);
void	ft_exec_env(t_shell *shell, char *cmd, int len_cmd, int i);
void	ft_exec_exit(t_shell *shell, char *cmd, char *arg, int ntokens);
void	ft_exec_cmd(t_shell *shell, char *line);
void	ft_skip_space(char **str);
int		ft_count_tokens(char **cmd_args);

void	ft_error(char *header, char *subheader, char *msg);
void	free_split(char **split);

void	clean_exit(t_shell *shell, char *exit_code);

int	lexer(t_shell *shell);
int	parse(t_shell *sh);

t_cmd	*mk_pipe(t_cmd *left, t_cmd *right);
t_cmd	*mk_redir(char *file, int mode, int fd, t_cmd *subcmd);
t_cmd	*mk_exec(void);

t_cmd	*parsepipe(t_shell *sh);
t_cmd	*parseexec(t_shell *sh);
t_cmd	*parseredir(t_shell *sh, t_cmd *cmd);

int	peek(t_shell *sh, char *tok);
int	gettoken(t_shell *sh, char **token);


#endif