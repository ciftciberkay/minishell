/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:13:15 by femullao          #+#    #+#             */
/*   Updated: 2025/08/17 17:13:16 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdlib.h>

enum
{
	HEREDOC = 'H',
	APPEND = 'A',
	OUTPUT = 'O',
	INPUT = 'I',
	PIPE = 'P',
	CHAR = 'C',
	BLANK = 'B',
	DQUOTE = 'D',
	SQUOTE = 'S'
};

typedef struct s_redirects
{
	int					type;
	char				*name;
	int					heredoc_fd;
	int					exitflag;
	struct s_redirects	*next;
}	t_redirects;

typedef struct s_command
{
	char				**argv;
	t_redirects			*ret;
	pid_t				pid;
	int					the_flag;
	struct s_command	*next;
}	t_command;

typedef struct s_mini
{
	char		**menv;
	t_command	*cmd;
	t_redirects	*rd;
	char		**sub_pipes;
	char		*input;
	char		*tokenized;
	int			*pipe_locs;
	int			exitcode;
	int			exitcontrol;
}	t_mini;

typedef struct s_dctx
{
	const char	*in;
	int			i;
	int			sq;
	int			dq;
	char		*res;
	t_mini		*mini;
}	t_dctx;

void		execute_command(char **args, t_mini *mini);
char		*get_env_paths(char **env);
char		*get_cmd_from_paths(char *cmd, char **psb_paths, t_mini *mini);
char		*find_cmd_path(char **args, t_mini *mini);
void		check_pth(char *path, t_mini *mini);
void		execute(t_command *cmd, t_mini *mini);
void		ft_cmd_error(char *cmd, int flag, t_mini *mini);
void		ft_echo(char **args, t_mini *mini);
char		*get_from_env(char **env, char *arg);
void		ft_cd(char **arg, t_mini *mini);
char		**create_menv(char **env);
void		ft_env(char **env, t_mini *mini);
t_mini		*update_env(char *key, char *newdata, t_mini *mini);
void		ft_unset(t_mini *mini, char **arg);
void		ft_pwd(t_mini *mini);
void		ft_export(t_mini *mini, char **args);
void		ft_exit(char **arg, t_mini *mini);
void		print_error_export(t_mini *mini);
char		**ft_strlcpy_n_replace(char **dst, char **src);
void		add_env(t_mini *mini, char *arg);
int			check_chars(char *arg);
char		*get_value(char *line);
char		*get_key(char *line);
void		signal_handler(void);
void		free_pp(char **ptr);
int			is_directory(const char *path);;
void		ft_cmd_file_error(char *cmd, int flag, int exitflag, t_mini *mini);
int			handle_output_redirect(t_redirects *redirect, t_mini *mini);
int			handle_append_redirect(t_redirects *redirect, t_mini *mini);
int			handle_stdin_redirect(t_redirects *redirect, t_mini *mini, int fd);
void		set_stdin(int *in_fd, int pipe_fd[2], t_command *curr);
int			is_stdinrdr(t_command *cmd);
void		waiting_children(t_command *cmd, t_mini *mini, int the_flag);
void		chd_proc(t_command *cmd, int pipe_fd[2], int in_fd, t_mini *mini);
int			apply_redirects(t_command *cmd, t_mini *mini);
int			is_command_builtin(char *cmd);
void		execute_builtin(char **args, t_mini *mini);
void		only_one_builtin(t_command *cmd, t_mini *mini);
void		prepare_heredocs(t_command *cmd);
void		update_env_pwd(t_mini *mini, char *new_pwd, char *old_pwd);
void		ft_puterror_cd(char *ptr, char *to_free);
int			arg_counter(char **args);
void		handle_too_many_args(t_mini *mini);
void		handle_cd_error(char *pwd, t_mini *mini, char *arg);
int			allocate_pipe_arrays(t_mini *mini, int pipe_c);
void		find_pipe_locations(t_mini *mini);
int			process_quoted_string(char *str, int *i, char quote_char);
int			process_unquoted_string(char *str, int *i);
void		ft_strtrim_in_place(char *str);
int			ft_isspace(int c);
int			is_redirect_char(char c);
char		**ft_split_with_quotes(char *s, int j);
void		parse(t_mini *mini);
char		*tokenizer(char *input);
void		determine_pipe_locs_and_split(t_mini *mini);
void		get_sub_pipes(t_mini *mini, int pipe_c, int x);
void		mark_each(char *input, char *ret, int i);
int			is_heredoc(char *ret, int i);
int			is_append(char *ret, int i);
void		quotes_in(char *tokenized);
int			quote_check(char *input);
t_command	*create_command_node(void);
void		add_command_to_list(t_command **head, t_command *new_node);
char		**extract_argv(char *sub_pipe_str, t_mini *mini);
void		cleanup_str_for_argv(char *str, int i, int j);
void		parse_commands(t_mini *mini);
t_redirects	*create_redirect_node(int type, char *name);
void		add_redirect_to_list(t_redirects **head, t_redirects *new_node);
char		*get_redirect_name(t_mini *mini, char *str, int *idx);
t_redirects	*extract_redirects(t_mini *mini, char *sub_pipe_str);
void		free_split(char **arr);
void		free_redirects(t_redirects *redir_list);
void		free_commands(t_command *cmd_list);
void		free_parser(t_mini *mini);
int			check_syntax_errors(const char *input);
char		*process_dollar_signs(const char *input, t_mini *mini);
char		*expand_variable(const char *input, int *i, char **menv);
char		*ft_strjoin_free(char *s1, char *s2);
char		*exitcode_dollar(int exitcode);
void		append_one_ctx(t_dctx *c);
void		handle_squote_ctx(t_dctx *c);
void		handle_dquote_ctx(t_dctx *c);
void		handle_var_expand_ctx(t_dctx *c);
void		update_quote_status(char c, int *in_squote, int *in_dquote);
int			handle_input_redirect_type(char *str, int *i);
int			handle_output_redirect_type(char *str, int *i);
int			get_redirect_type(char *str, int *i);
int			process_input(t_mini *mini);
int			process_dollar(t_mini *mini);
void		execute_command_line(t_mini *mini);
void		shell_loop(t_mini *mini);
void		free_all(t_mini *mini);
char		*ft_substr_join(const char *str, size_t start, size_t end);

#endif