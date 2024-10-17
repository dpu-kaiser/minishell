/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:53:39 by dkaiser           #+#    #+#             */
/*   Updated: 2024/09/13 16:26:16 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

char				*env_get(t_env *env, char *name);
void				env_export(t_env *env, char *name, char *value);
void				env_unset(t_env *env, char *name);
char				**env_to_strlst(t_env *env);
t_env				**env_from_strlst(char **lst);

