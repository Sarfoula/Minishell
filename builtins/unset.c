/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:16:36 by yallo             #+#    #+#             */
/*   Updated: 2023/11/28 16:28:56 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset(char *name)
{
	char *value;

	value = getenv(name);
	return (0);
}
// int main(int argc, char **argv, char **envp)
// {
// 	unset("yallo");
// 	export(envp);
// }
