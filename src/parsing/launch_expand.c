/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevot <fprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:49:39 by lmattern          #+#    #+#             */
/*   Updated: 2024/09/03 14:20:37 by fprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mandatory/parse.h"

void	process_redirections_and_filenames(t_token *token, t_g_data *g_data)
{
	char	*tmp;

	if (redirection_outside_quotes(token->value))
	{
		token->io_list = parse_io_from_command(token->value, token->g_data);
		if (g_sigint == 2)
			return ;
		tmp = ft_strdup(token->value);
		if (!tmp)
		{
			free_io_list(token->io_list);
			free_lexed(g_data->lexed);
			fail_exit_shell(g_data);
		}
		free(token->value);
		token->value = del_redir(tmp, 0, 0);
		if (!token->value)
		{
			free(tmp);
			free_io_list(token->io_list);
			free(token);
			fail_exit_shell(g_data);
		}
		free(tmp);
	}
}

void	handle_expanded_token(t_token *token, t_g_data *g_data)
{
	if (((token->value[0] == -1) && !token->value[1]) || token->value[0] == 0)
	{
		token->is_empty = true;
		token->expanded = malloc(sizeof(char *) * 2);
		if (!token->expanded)
		{
			free(token->value);
			free_io_list(token->io_list);
			fail_exit_shell(g_data);
		}
		token->expanded[0] = ft_strdup("EMPTY");
		if (!token->expanded[0])
		{
			free(token->expanded);
			free(token->value);
			free_io_list(token->io_list);
			fail_exit_shell(g_data);
		}
		token->expanded[1] = NULL;
	}
	else
	{
		token->is_empty = false;
		token->expanded = expander(token->value, token->g_data);
	}
}

void	expe(t_token *lexed, t_g_data *g_data)
{
	t_token	*fir;

	fir = lexed;
	while (lexed != NULL)
	{
		lexed->first = fir;
		if (lexed->type == T_WORD)
		{
			process_redirections_and_filenames(lexed, g_data);
			if (g_sigint == 2)
				return ;
			lexed->is_add_local = check_local(lexed->value);
			handle_expanded_token(lexed, g_data);
		}
		lexed = lexed->next;
	}
}

void	launch_expand(t_g_data *g_data)
{
	expe(g_data->lexed, g_data);
	if (g_sigint == 2)
		return ;
}
