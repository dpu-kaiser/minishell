/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:53:39 by dkaiser           #+#    #+#             */
/*   Updated: 2024/10/17 15:47:30 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

void	getenvlst(t_env **env, char **en);
void	free_envlst(t_env **env);

