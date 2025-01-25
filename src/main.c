/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:14:03 by dkaiser           #+#    #+#             */
/*   Updated: 2025/01/25 15:41:04 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_env		*env;
	static int	promptflag;

	env = NULL;
	promptflag = 0;
	if (!argc && !argv)
		return (1);
	if (init())
		return (1);
	getenvlst(&env, envp);
	set_return_code(0, &env);
	repl("Minishell $ ", &env);
	free_envlst(&env);
	return (0);
}
