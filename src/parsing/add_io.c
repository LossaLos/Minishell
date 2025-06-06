/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevot <fprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:48:35 by lmattern          #+#    #+#             */
/*   Updated: 2024/09/03 14:20:37 by fprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mandatory/parse.h"

void	skip_whitespace(char **cursor)
{
	while (**cursor == ' ')
		(*cursor)++;
}

char	*extract_filename(char **cursor)
{
	char	*start;
	char	c;

	c = ' ';
	if (**cursor == '"' || **cursor == '\'')
	{
		if (**cursor == '"')
			c = '"';
		else if (**cursor == '\'')
			c = '\'';
		if (*cursor != NULL)
			(*cursor)++;
		if (*cursor != NULL)
			start = (*cursor)++;
	}
	else
		start = *cursor;
	while (**cursor && **cursor != c && **cursor != '>' && **cursor != '<')
		(*cursor)++;
	return (ft_strndup(start, *cursor - start));
}

void	initialize_and_add_io_node(t_io_bundle *io, t_io_node *new_io)
{
	if (!io->head)
	{
		io->head = new_io;
		io->tail = new_io;
	}
	else
	{
		io->tail->next = new_io;
		new_io->prev = io->tail;
		io->tail = new_io;
	}
}

char	*extract_filename_her(char **cursor, bool quote, char lquote)
{
	char	*start;

	start = (*cursor);
	while (ft_isspace((**cursor)))
		(*cursor)++;
	while (**cursor)
	{
		if ((**cursor) == '\'' || (**cursor) == '"')
		{
			if (lquote == 0)
			{
				lquote = (**cursor);
				quote = !quote;
			}
			else if ((**cursor) == lquote)
			{
				lquote = 0;
				quote = !quote;
			}
		}
		if (ft_isspace((**cursor)) && !quote)
			break ;
		(*cursor)++;
	}
	return (ft_strndup(start, *cursor - start));
}

void	add_new_io_node(t_io_bundle *io, char **cursor, t_g_data *data)
{
	t_io_node	*new_io;
	char		*filename;

	skip_whitespace(cursor);
	if (io->type == IO_HEREDOC)
	{
		filename = extract_filename_her(cursor, false, 0);
		data->her_file = filename;
	}
	else
		filename = extract_filename(cursor);
	if (!filename)
	{
		free_lexed(data->lexed);
		fail_exit_shell(data);
	}
	new_io = create_io_from_string(io->type, filename, data);
	if (g_sigint == 2)
		return ;
	free(filename);
	if (new_io == NULL)
		return (free_lexed(data->lexed), fail_exit_shell(data));
	initialize_and_add_io_node(io, new_io);
}
