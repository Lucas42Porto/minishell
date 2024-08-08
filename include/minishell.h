/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:04:38 by lumarque          #+#    #+#             */
/*   Updated: 2024/08/08 01:01:07 by lumarque         ###   ########.fr       */
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

# define PROMPT_BEGIN "┎─── "
# define PROMPT_END "\n┖─❯ "

# define STOP 0
# define CONTINUE 1
# define RESTORE 2

# define EXEC 300
# define REDIR 301
# define PIPE 302
# define HERE_DOC 303
# define APPEND 304

# define MAXARGS 50

# define SPACES " \t\n\v\f\r"
# define OPERATORS "|><"
# define NOT_EXP "|></ \t\n\v\f\r"
# define OPANDSP "|>< \t\n\v\f\r"

# define ERROR_TITLE "minishell: "
# define ERROR_QUOTE "unclosed quotes"
# define ERROR_SINTAX "syntax error"
# define ERROR_HERE_DOC "unexpected EOF while looking for matching `"
# define ERROR_QUOTES "unclosed quotes"
# define ERROR_SYNTAX_PIPE "syntax error near unexpected token `|'"
# define ERROR_SYNTAX_PIPE2 "syntax error near unexpected token `||'"

# define SIGRESTORE 1
# define SIGHEREDOC 2
# define SIGCHILD 3
# define SIGIGNORE 4

extern int			g_exit;

typedef struct s_cmd
{
	int				type;
}					t_cmd;

// typedef struct s_env
// {
// 	char			*key;
// 	char			*value;
// 	int				visible;
// 	int				index;
// 	struct s_env	*next;
// }					t_env;

typedef struct	s_env
{
	char	**e_name;
	char	**e_content;
	int		size_env;
}				t_env;

typedef struct s_shell
{
	char			*user_line;
	char			*prompt;
	char			*ps;
	char			*es;
	int				size_line;
	t_env			env;
	t_cmd			*cmd;
	int				status;
	int				envp_size;
	int				pid;
	char			**envp;
	char			**paths;
}					t_shell;

typedef struct s_exec
{
	int				type;
	char			*argv[MAXARGS];
}					t_exec;

typedef struct s_redir
{
	int				type;
	t_cmd			*cmd;
	char			*file;
	int				mode;
	int				fd;
}					t_redir;

typedef struct s_here
{
	int				type;
	t_cmd			*cmd;
	char			*eof;
	int				mode;
	int				fdin;
	int				fdout;
}					t_here;

typedef struct s_pipe
{
	int				type;
	t_cmd			*left;
	t_cmd			*right;
}					t_pipe;

// process_line file
int					process_line(t_shell *shell);
int					inside_quotes(t_shell *shell);

// envp1 file - convert
void				convert_envp_to_linked_lists(char **envp, t_shell *shell);
void				convert_envp_to_char(t_shell *shell);

// envp2 file - add
void				create_update_envp_lists(t_shell *shell, char *key,
						char *value, int visible);

// envp3 file - export/get/print
void				env_export(t_shell *shell, char *key, char *value,
						int visible);
char				*env_get(char *key, t_shell *shell);
void				envp_print(t_shell *shell);

// envp4 file - modify
bool				env_mod(t_shell *shell, char *target, char *new_value);

// envp5 file - rm
void				env_rm(char *key, t_shell *shell);
void				ft_envlstdelone(t_env *lst, void (*del)(void *));

// envp6 file - clear
void				ft_envlstclear(t_env *lst, void (*del)(void *));

// Parser
t_cmd				*exec_cmd(void);
t_cmd				*pipe_cmd(t_cmd *left, t_cmd *right);
t_cmd				*redir_cmd(t_cmd *cmd, char *file, int mode, int fd);
int					parse_cmd(t_shell *shell);
int					peek(t_shell *shell, char *op);
int					gettoken(t_shell *sh, char **token);
t_cmd				*parsepipe(t_shell *shell);

// Expand
void				expand_arg(t_shell *shell, char **arg);
int					expand_free(char *key, int i, int j, char **line);
int					expand(char *key, int i, int j, char **line);
void				trim_quotes(char *arg, int *len);
void				arg_insert_null(char *arg);

// error_frees
int					print_error_syntax(t_shell *shell, char *msg, int exit);
int					print_error(t_shell *shell, char *msg, char *msg2,
						int exit);
void				free_exit(t_shell *shell);
int					error_inside(t_shell *shell, char *cmd, char *arg,
						int error_code);
void				free_cmd(t_cmd *cmd);

// run_cmd
void				run_cmd(t_shell *shell, t_cmd *cmd);
void				run_exec(t_shell *shell, t_exec *cmd);
void				run_redir(t_shell *shell, t_redir *cmd);
void				run_pipe(t_shell *shell, t_pipe *cmd);
void				wait_children(t_shell *shell);
void				check(int result, char *msg, int exit);
int					check_fork(void);
t_cmd				*here_cmd(t_cmd *cmd, char *eof);
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

//temp rennan
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
//

// signals
void				signal_handler(int sig);

#endif