/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:12:08 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/12/05 12:31:36 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_prompt(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	ctrl_c_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	new_prompt();
}

/**
 * [Ctrl + \ ]	SIGQUIT
 * [CTRL + C ]	SIGINT
 * [CTRL + D ]	
*/
void	signal_handling(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_handler);
}