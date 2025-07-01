/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:00:00 by YOURLOGIN         #+#    #+#             */
/*   Updated: 2025/06/30 17:54:06 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <termios.h>
# include <dirent.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "minishell$ "

extern uint8_t	g_sigint;

/**
 * file: optional (nullable), used if append or redir flags are specified
 * pseudo_stdin: stdin if < or << is specified, -1 otherwise
 * heredoc: amount of heredocs specified in the command,
 *			the terminate character (like EOF) will be set to *arg*
 *			and will reference only to the last heredoc,
 *			can be 0 if none is specified
 * is_redir: flag, 1 if > is specified in the command, 0 otherwise
 * is_append: flag, 1 if >> is specified, 0 otherwise
 */
typedef struct s_cmd_settings
{
	int				pseudo_stdin;
	int				pseudo_stdout;
	int				heredoc;
	uint_fast8_t	failed;
	uint_fast8_t	is_append;
}	t_cmd_settings;

typedef struct s_cmd
{
	int				argc;
	char			**args;
	t_cmd_settings	settings;
}	t_cmd;

typedef struct s_pipeline
{
	t_cmd	**cmds;
	int		amount;
}	t_pipeline;

typedef struct s_state
{
	uint8_t			status;
	t_pipeline		pipeline;
	char			**env;
	t_list			*export_list;
	uint_fast8_t	end;
	char			pid[10];
	char			pwd[PATH_MAX];
}	t_state;

/**
** pipe.c
** Estructura auxiliar para los pipes child de los cmds
*/
typedef struct s_pipe_args
{
	t_cmd	*cmd;
	t_state	state;
	int		input_fd;
	int		pipe_write_fd;
	int		is_last;
}	t_pipe_args;

typedef struct s_cmd_args
{
	t_cmd	*cmd;
	char	***env;
	int		input_fd;
	int		pipe_write_fd;
	int		is_last;
}	t_cmd_args;

/**
 * Convenience type to know if a string is allocated using malloc
 * and needs to be freed,
 * this enables more efficient ways of doing things.
 */
typedef struct s_str
{
	char			*str;
	uint_fast8_t	is_malloc;
}	t_str;

typedef struct s_slice
{
	char	*str;
	size_t	len;
}	t_slice;

typedef struct s_parse_result
{
	char	*end_pos;
	t_cmd	*command;
}	t_parse_result;

typedef struct s_chr_res
{
	char			*s;
	uint_fast8_t	quote;
}	t_chr_res;

/**
** prompt.c
*/
char			*read_prompt(void);

/**
** signal.c
*/
void			init_signals(void);
void			handle_sigint_heredoc(int sig);
void			restore_signals(void);

/**
** builtin
*/
int				exec_builtin(t_cmd *cmd, char ***env,
					t_state *state, uint_fast8_t is_main);
int				is_builtin(char *cmd);
int				ft_cd(char **args, int argc, char ***env, t_state *state);
void			ft_exit(t_cmd *cmd, t_state *state, uint_fast8_t end);
int				ft_echo(char **args, int outfd);
int				ft_env(char **env, int outfd);
int				ft_export(char **args, char ***env, t_state *state);
int				ft_pwd(int outfd, t_state *state);
int				ft_unset(char **args, char ***env, t_state *state);

/**
* env
*/
char			**copy_env(char **envp);
void			free_env(char **env);
t_str			get_env(char *str, char **env, uint8_t status);
char			*inject_env(char *dst, char **env, t_state *state,
					t_chr_res (*delchr)(char *));
int				set_env_value(char ***env, const char *entry, char *value);
int				envlen(char **env);
t_chr_res		envchr(char *str);
char			*gen_pair(char *key, char *value);
int				is_in_list(t_list *list, const char *key);
int				is_in_env(char **env, const char *key);
void			remove_from_export_list(t_list **list, const char *key);
char			*get_value(const char *env_entry);
char			*get_key(const char *env_entry);

/**
** executor
*/
int				execute_pipeline(t_pipeline *pipe, char ***env, t_state *state);
char			*get_command_path(char *cmd, char **env);
int				run_child(t_cmd *cmd, char **env);
int				handle_pipe(t_cmd **cmds, int i, int amount[2], t_state *state);
int				handle_heredoc(t_cmd_settings *settings,
					char *eof, uint_fast8_t env, t_state *state);
int				execute_command_no_fork(t_cmd *cmd, char **env);

/**
** parser
*/
int				parse_full_command(char *str, t_state *state);
int				clean_pipeline(t_pipeline *pipe);
int				clean_cmd(t_cmd *cmdd);
t_slice			get_arg(char *str, t_state *state);
int				count_quotes(char *str);
void			settings_zero(t_cmd_settings *set);
t_parse_result	parse_symbols(t_cmd *cmd, char *str, t_state *state);
int				validate_token(char *str, t_state *state);
char			*skip_whitespaces(char *str);
char			*inject_astsk(char *dst);
uint_fast8_t	is_consecutive_quote(char *str);
char			*rev_quotes(char *str, size_t len);

/**
* PID
*/
void			ft_get_pid(char buffer[10]);

/**
 * others
 */
void			print_error(char *msg, uint8_t code,
					uint8_t exit_code, t_state *state);
void			print_error_no_state(char *msg, uint8_t code);
void			*error_return(char *msg, uint8_t code,
					uint8_t exit_code, t_state *state);
void			close_safe(int fd);
void			*clean_return(void *ptr);
int				is_whitespace(char c);
char			*argdelimitchr(char *str);
char			*cmddelimitchr(char *str);
int				is_cmd_delimiter(char ch);
int				is_arg_delimiter(char ch);
char			*ft_strjoin3(t_slice s1, t_slice s2, t_slice s3);

#endif
