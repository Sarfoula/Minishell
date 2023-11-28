/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:12:16 by yallo             #+#    #+#             */
/*   Updated: 2023/11/28 16:12:21 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	echo(char **str, int option)
{
	size_t	i;
	size_t	size;

	i = 0;
	while (str[i])
	{
		size = ft_strlen(str[i]);
		if (write(1, str[i], size + 1) == -1)
			return (1);
		if (str[i + 1])
			if (write(1, " ", 1)== -1)
				return (1);
		i++;
	}
	if (option != 0)
		return (0);
	if (write(1, "\n", 1) == -1)
		return (1);
	return (0);
}
