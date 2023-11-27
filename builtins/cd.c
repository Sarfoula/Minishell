/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:15:49 by yallo             #+#    #+#             */
/*   Updated: 2023/11/27 14:10:10 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd(const char *dir)
{
	if (chdir(dir) == -1)
		return (printf("Not working\n"), 1);
	return (0);
}

// int main(int argc, char **argv)
// {
// 	if (argc == 2)
// 		return (cd(argv[1]));
// 	printf("bad args\n");
// 	return (0);
// }
// NOT WORKING idk why
