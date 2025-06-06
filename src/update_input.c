/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevot <fprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:53:28 by lmattern          #+#    #+#             */
/*   Updated: 2024/09/03 14:20:37 by fprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mandatory/parse.h"
#include "../inc/mandatory/exec.h"

void	clean_exit_update_input(t_g_data *g_data)
{
	int	last_exit_status;

	last_exit_status = g_data->last_exit_status;
	free(g_data->in_put);
	free(g_data->in_putsave);
	write(STDOUT_FILENO, "exit\n", 5);
	ft_clear_memory(g_data);
	free(g_data);
	close_std_fds();
	exit(last_exit_status);
}

void	free_ressources(char *tmp, char *prompt, t_g_data *g_data)
{
	ft_free(tmp);
	ft_free(prompt);
	ft_free(g_data->join);
	ft_free(g_data->path);
	if (!g_data->in_put)
		clean_exit_update_input(g_data);
}

char	*display_error_code(t_g_data *g_data, char *tmp)
{
	char	*prefix;
	char	*prompt;

	prompt = NULL;
	prefix = ft_calloc(10, sizeof(char));
	ft_sprintf(prefix, "[%d]", g_data->last_exit_status);
	prompt = ft_strjoin(prefix, tmp);
	ft_free(prefix);
	return (prompt);
}

char	*ft_get_cwd(void)
{
	char	*cwd;
	char	*home;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp)
	{
		home = getenv("HOME");
		if (!home)
			home = "";
		if (home && home[0] && ft_strnstr(tmp, home, ft_strlen(home)))
		{
			cwd = ft_strjoin("~", tmp + ft_strlen(home));
			free(tmp);
		}
		else
			cwd = tmp;
	}
	else
		cwd = ft_strdup("");
	return (cwd);
}

void	update_input(t_g_data *g_data, char *pre_input)
{
	char	*prompt;
	char	*prefix;
	char	*cwd;
	char	*tmp;

	g_data->t = 0;
	cwd = ft_get_cwd();
	prefix = ft_strjoin(cwd, "$ ");
	ft_free(cwd);
	if (pre_input && pre_input[0])
		tmp = ft_strjoin(pre_input, prefix);
	else
		tmp = ft_strdup(prefix);
	ft_free(prefix);
	if (g_data->last_exit_status)
		prompt = display_error_code(g_data, tmp);
	else
		prompt = ft_strdup(tmp);
	if (prompt)
		g_data->in_put = readline(prompt);
	else
		g_data->in_put = readline("$> ");
	free_ressources(tmp, prompt, g_data);
}
