/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevot <fprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:20:33 by lmattern          #+#    #+#             */
/*   Updated: 2024/09/03 14:20:37 by fprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mandatory/exec.h"

/*
Updates the environment variables with the specified name and value.
*/
bool	has_updated(t_env *current, char *name, char *value, bool is_local)
{
	if (ft_strncmp(current->name, name, ft_strlen(name) + 1) == 0)
	{
		if (value && value[0])
		{
			free(current->value);
			current->value = value;
		}
		else
			ft_free(value);
		if (current->is_local == false)
			return (true);
		else
			return (current->is_local = is_local, true);
	}
	return (false);
}

/*
Processes a single export argument, assuming it's already validated.
*/
int	add_or_update_env(t_env **mini_env, char *name, char *value, bool is_local)
{
	t_env	*current;
	t_env	*last;
	t_env	*new_env;

	new_env = NULL;
	current = *mini_env;
	last = NULL;
	while (current != NULL)
	{
		if (has_updated(current, name, value, is_local))
		{
			free(name);
			return (EXIT_SUCCESS);
		}
		last = current;
		current = current->next;
	}
	new_env = ft_env_new_entrie(name, value, is_local);
	if (new_env == NULL)
		return (free(value), EXIT_FAILURE);
	if (last != NULL)
		last->next = new_env;
	else
		*mini_env = new_env;
	return (EXIT_SUCCESS);
}
