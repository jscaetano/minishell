/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:48:07 by marvin            #+#    #+#             */
/*   Updated: 2023/05/07 20:48:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "macros.h"
# include "env.h"

//! Cd command
void		ft_cd(char **tokens);

//! Echo command
void		ft_echo(char **tokens);

//! Env command
char		*get_env(char *str);
void		ft_env(char **tokens);

//! Exit command
bool		_is_longlong(char *num);
void		ft_exit(char **args);

//! Export command
bool		is_assignment(t_token *token);
t_env		*_env_find(t_list *envlist, char *key);
void		_export_from_temp_list(char *name);
void		export_directly(t_list **envlist, char *assignment);
void		ft_export(char **tokens);

//! Unset command
bool		_env_key_cmp(t_env *env, char *key);
void		ft_unset(char **tokens);

#endif