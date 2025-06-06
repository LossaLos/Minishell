/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevot <fprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:32:22 by fprevot           #+#    #+#             */
/*   Updated: 2024/09/03 14:20:37 by fprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mandatory/parse.h"

void	imoremore_quote(char *arg, int *i, char c)
{
	(*i)++;
	while (arg[*i] && arg[*i] != c)
		(*i)++;
}

void	imore(int size, int *i)
{
	int	k;

	k = -1;
	while (++k < size)
		(*i)++;
}

void	skip_space(char *input, int *index)
{
	while (input[*index] == ' ')
		(*index)++;
}

bool	is_previous_heredoc(int i, char *res)
{
	int	j;

	if (i == 0)
		return (true);
	j = i - 1;
	while (res && j > 0 && res[j] != '>' && res[j] != '<')
		j--;
	if (res[j] == '<' && res[j - 1] == '<')
		return (false);
	else
		return (true);
}

bool	is_end(char *str, int i)
{
	while (str[i] != '\0')
	{
		if (!ft_isspace(str[i]))
			return (false);
		i++;
	}
	return (true);
}
