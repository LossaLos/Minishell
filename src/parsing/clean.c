/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevot <fprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:11:48 by fprevot           #+#    #+#             */
/*   Updated: 2024/09/03 14:20:37 by fprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mandatory/parse.h"

void	ft_clear_memory(t_g_data *g_data)
{
	free_mini_env(g_data->mini_env);
	free(g_data->in_put);
	free(g_data->in_putsave);
	rl_clear_history();
}

void	free_data(t_data *data)
{
	if (data == NULL)
		return ;
	free_tree(data->ast);
}

void	free_forked_data_structure(t_data **data)
{
	free_forked_data(*data);
	free((*data)->g_data);
	free(*data);
}

void	free_data_structure(t_data **data)
{
	if (*data == NULL)
		return ;
	free_data(*data);
	free(*data);
}

void	fail_exit_shell(t_g_data *g_data)
{
	ft_clear_memory(g_data);
	free_data_structure(&g_data->data);
	free(g_data);
	rl_clear_history();
	printf("Fatal error: failed to allocate memory.\n");
	exit(EXIT_FAILURE);
}
