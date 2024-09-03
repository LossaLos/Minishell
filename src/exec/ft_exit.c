/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevot <fprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:10:35 by lmattern          #+#    #+#             */
/*   Updated: 2024/09/03 14:20:37 by fprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mandatory/exec.h"

long long	ft_strtol(const char *str, char *endptr, bool *error)
{
	long long	res;
	int			sign;
	int			digit;

	res = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		digit = *str - '0';
		if (sign == 1 && (LLONG_MAX - digit) / 10 < res)
			return (*error = true, LLONG_MAX);
		else if (sign == -1 && (LLONG_MIN + digit) / 10 > -res)
			return (*error = true, LLONG_MIN);
		res = res * 10 + digit;
		str++;
	}
	return (*endptr = *str, res * sign);
}

int	exiting_exit(int status, t_data **data, bool g_data, bool piped)
{
	if (g_data)
		ft_clear_memory((*data)->g_data);
	if (!piped)
		printf("exit\n");
	if (data && *data)
	{
		free((*data)->g_data);
		free_data_structure(data);
	}
	close_std_fds();
	exit(status);
	return (status);
}

int	ft_exit(char **args, t_data **data, bool piped)
{
	long long	status;
	char		endptr;
	bool		error;

	endptr = 0;
	error = false;
	if (args[1])
	{
		status = ft_strtol(args[1], &endptr, &error);
		if (endptr || error == true)
		{
			ft_eprintf(MS"exit: %s: numeric argument required\n", args[1]);
			exiting_exit(EXIT_SYNTAX_ERROR, data, true, piped);
		}
		if (args[2])
		{
			ft_eprintf("exit\n"MS"exit: too many arguments\n");
			return (EXIT_GENERAL_ERROR);
		}
		return (exiting_exit((int)(status % 256 + 256) % 256, \
		data, true, piped));
	}
	return (exiting_exit((*data)->g_data->last_exit_status, data, true, piped));
}
