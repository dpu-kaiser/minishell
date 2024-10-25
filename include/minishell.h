/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:14:49 by dkaiser           #+#    #+#             */
/*   Updated: 2024/10/22 16:52:26 by chuhlig          ###   ########.fr       */
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

int				init(void);
int				init_signal_handling(void);

void			repl(const char *prompt, t_env **env);

t_list			*parse(t_token *tokens);
t_node			*parse_cmd(t_token *tokens);
t_redirection	*collect_redirs(t_token **tokens);

void			print_ast(t_node *ast);

int	eval(t_node *node, t_env **env);
#endif
