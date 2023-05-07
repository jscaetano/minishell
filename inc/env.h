/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:46:06 by marvin            #+#    #+#             */
/*   Updated: 2023/05/07 20:46:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "macros.h"

typedef struct s_env
{
	char			*key;
	char			*value;
}	t_env;

//! Envlist
t_env		*env_new(char *key, char *value);
t_env		*env_copy(t_env	*env);
char		**envlist_to_matrix(t_list *envlist);
void		env_destroy(t_env *env);
t_list		*envlist(char **envp);

#endif