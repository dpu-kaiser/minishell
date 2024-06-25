/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:08:43 by dkaiser           #+#    #+#             */
/*   Updated: 2024/06/25 12:26:57 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int status);

int	init_signal_handling(void)
{
	if (signal(SIGINT, &handle_sigint) == SIG_ERR)
		return (1);
	return (0);
}

static void	handle_sigint(__attribute__((unused)) int status)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
