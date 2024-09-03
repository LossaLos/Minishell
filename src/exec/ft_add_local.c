/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_local.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevot <fprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:23:50 by lmattern          #+#    #+#             */
/*   Updated: 2024/09/03 14:20:37 by fprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mandatory/exec.h"

int	ft_add_local(char *arg, t_env **mini_env)
{
	char	*equal_pos;
	char	*name;
	char	*value;

	equal_pos = ft_strchr(arg, '=');
	name = NULL;
	value = NULL;
	name = ft_strndup(arg, equal_pos - arg);
	value = ft_strdup(equal_pos + 1);
	if (name == NULL || value == NULL)
		return (free(name), free(value), EXIT_FAILURE);
	return (add_or_update_env(mini_env, name, value, true));
}
