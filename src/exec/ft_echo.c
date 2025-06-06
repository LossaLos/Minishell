/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevot <fprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:25:19 by lmattern          #+#    #+#             */
/*   Updated: 2024/09/03 14:20:37 by fprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mandatory/exec.h"

/*
Writes the arguments to the standard output followed by a newline (or not with 
option -n).
*/

void	go_through_options(char **args, int *i, bool *option)
{
	int	j;

	while (args[*i] && !ft_strncmp(args[*i], "-n", 2))
	{
		j = 0;
		while (args[*i][j] && args[*i][j] == '-')
			j++;
		if (args[*i][j] != 'n')
			break ;
		while (args[*i][j] && args[*i][j] == 'n')
			j++;
		if (args[*i][j])
			break ;
		*option = true;
		(*i)++;
	}
}

int	ft_echo(char **args)
{
	int		i;
	bool	option;

	i = 1;
	option = false;
	go_through_options(args, &i, &option);
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i++ + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!option)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

/*
Check if the command is a builtin and execute it if it is
*/
int	checking_forked_builtins(t_data *data, t_node *node)
{
	int			status;
	const char	*str;

	str = (const char *)node->expanded_args[0];
	if (ft_strncmp(str, "/", ft_strlen(str) == 0))
		return (0);
	else if (ft_strncmp(str, "echo", 5) == 0)
		status = ft_echo(node->expanded_args);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		status = ft_pwd();
	else if (ft_strncmp(str, "env", 4) == 0)
		status = ft_env(node->expanded_args, data->mini_env);
	else
		return (0);
	free_forked_data_structure(&data);
	close_std_fds();
	exit(status);
}
