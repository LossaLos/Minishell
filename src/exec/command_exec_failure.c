/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec_failure.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevot <fprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:00:32 by lmattern          #+#    #+#             */
/*   Updated: 2024/09/03 14:20:37 by fprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mandatory/exec.h"

/*
Prints an error message and exit the child process.
*/
int	heredoc_dup2_creation_failure(int pipefd[2])
{
	perror(MS"dup2 error");
	close_pipe_fds(pipefd);
	return (EXIT_DUP2_FAILURE);
}

/*
Prints an error message and exit the child process.
*/
int	handle_permission_denied(const char *context)
{
	if (ft_strchr(context, '/'))
	{
		ft_eprintf(MS"%s: Permission denied\n", context);
		return (EXIT_INVALID_COMMAND);
	}
	else
		ft_eprintf("%s: command not found\n", context);
	return (EXIT_COMMAND_NOT_FOUND);
}

/*
Prints an error message and exit the child process.
*/
int	handle_command_not_found(const char *context)
{
	if (ft_strchr(context, '/'))
		ft_eprintf(MS"%s: No such file or directory\n", context);
	else
		ft_eprintf("%s: command not found\n", context);
	return (EXIT_COMMAND_NOT_FOUND);
}

/*
Prints an error message and exit the child process.
*/
void	command_exec_failure(t_data *data, const char *context, int error_code)
{
	int	status;

	status = EXIT_COMMAND_NOT_FOUND;
	if (error_code == EXIT_COMMAND_NOT_FOUND)
		status = handle_command_not_found(context);
	else if (error_code == EXIT_PERMISSION_DENIED)
		status = handle_permission_denied(context);
	else if (error_code == EXIT_IS_A_DIRECTORY)
	{
		if (ft_strchr(context, '/'))
		{
			status = EXIT_INVALID_COMMAND;
			ft_eprintf(MS"%s: Is a directory\n", context);
		}
		else
			ft_eprintf("%s: command not found\n", context);
	}
	else
		ft_eprintf(MS"%s: %s\n", context, strerror(errno));
	free_forked_data_structure(&data);
	close_std_fds();
	exit(status);
}
