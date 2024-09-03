/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevot <fprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:45:34 by lmattern          #+#    #+#             */
/*   Updated: 2024/09/03 14:20:37 by fprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mandatory/exec.h"

size_t	ft_env_size(t_env *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	free_mini_env(t_env *mini_env)
{
	t_env	*tmp;

	while (mini_env)
	{
		tmp = mini_env;
		mini_env = mini_env->next;
		ft_free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

t_env	*ft_env_last(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_env_add_back(t_env **lst, t_env *new)
{
	t_env	*last_node;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last_node = ft_env_last(*lst);
		last_node->next = new;
	}
}
