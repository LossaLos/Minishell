/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   applying_redirections_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevot <fprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:00:32 by lmattern          #+#    #+#             */
/*   Updated: 2024/09/03 14:20:37 by fprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mandatory/exec.h"
#include "../../inc/mandatory/parse.h"

/*
Handles the ambiguous redirection error (if the filename is empty)
*/
bool	handle_ambiguous(t_io_node	*current)
{
	if (current->expanded_value[0] && current->expanded_value[0][0] == -4)
		return (ft_eprintf(MS"filename: ambiguous redirect\n"), false);
	if (current->type == IO_HEREDOC)
		return (true);
	if (current->expanded_value[0] && current->expanded_value[0][0] == -1)
		return (ft_eprintf(MS"filename: ambiguous redirect\n"), false);
	return (true);
}

/*
print an error message and return the exit code.
*/
int	command_redirection_failure(const char *context, int exit_code)
{
	ft_eprintf(MS"%s: %s\n", context, strerror(errno));
	return (exit_code);
}
