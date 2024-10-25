/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:14:03 by dkaiser           #+#    #+#             */
/*   Updated: 2024/10/25 15:53:10 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_env	*env;

	env = NULL;
	if (!argc && !argv)
		return (1);
	if (init())
		return (1);
	getenvlst(&env, envp);
	repl("Minishell $ ", &env);
}
