/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fprevot <fprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:37:09 by lmattern          #+#    #+#             */
/*   Updated: 2024/09/03 14:20:37 by fprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_putstr_fd(const char *s, int fd)
{
	size_t	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	if (write(fd, &(*s), len) < 0)
		return (-1);
	return (len);
}
