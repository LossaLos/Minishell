/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevot <fprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:10:35 by lmattern          #+#    #+#             */
/*   Updated: 2024/09/03 14:20:37 by fprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mandatory/exec.h"

/*
Prints the environment variables unless there are too many arguments.
*/
int	ft_env(char **args, t_env *mini_env)
{
	t_env	*tmp;

	if (args[1])
		return (ft_eprintf(MS"env: too many args\n"), EXIT_FAILURE);
	tmp = mini_env;
	while (tmp)
	{
		if (tmp->is_local)
		{
			tmp = tmp->next;
			continue ;
		}
		else if (tmp->value && tmp->value[0])
			printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
