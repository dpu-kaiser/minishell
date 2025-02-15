/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:14:49 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/25 15:41:33 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "debug_tools.h"
# include "ast.h"
# include "token.h"
# include "env.h"
# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include <fcntl.h>

int				init(void);
int				init_signal_handling(void);

void			repl(const char *prompt, t_env **env, int *promptflag);

t_node			*parse(t_token *tokens, t_env **env);
t_node			*parse_cmd(t_token *tokens, t_env **env);
t_redirection	*collect_redirs(t_token **tokens, t_env *env,
					t_list **create_files);

void			print_ast(t_node *ast);

int				eval(t_node *node, t_env **env);
char			*get_cmd_path(char *cmd, t_env *env, int *return_code);
int				execute_cmd(t_cmd *cmd, t_env **env);
char			*format_string(char *str, t_env *env, int is_literal);
void			set_return_code(int return_code, t_env **env);
int				handle_redirections(t_redirection *redirs);
void			*error(int err_code, char *err_text, int exit_code,
					int *ret_code);
void			*command_not_found_error(char *cmd, int *return_code,
					char *cmd_path, char **split_path);
char			*read_heredoc(char *delimiter);
int				handle_input_redirection(t_redirection *redir);
int				handle_output_redirection(t_redirection *redir);
int				handle_redirections(t_redirection *redirs);
int				handle_pipe_parent(int p[2], t_node *node, t_env **env);
int				handle_pipe_child(int p[2], t_node *node, t_env **env,
					int in_fd);
int				open_file(char *path, int flags, int mode);
int				eval_rec(t_node *node, t_env **env, int in_fd);
int				create_files(t_list *files);
void			q4fc(t_list **queue, t_redirection *redir);
void			i_love_the_norme(t_token **cur, t_token **tokens);

typedef struct s_minidata
{
	t_env		*env;
	t_list		**create_files;
}				t_minidata;

#endif
