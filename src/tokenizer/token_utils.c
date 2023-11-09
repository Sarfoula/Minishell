/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:40:06 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/11/08 23:32:46 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Create a new t_token and fills the char * value
*/
t_token	*create_new_token(char *str, int type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (log_error(ERR_MALLOC), NULL);
	new_token->token = str;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	add_back_token(t_token **token_lst, t_token *token)
{
	if (!token_lst || !token)
		return ;
	if (*token_lst)
	{
		get_last_token(*token_lst)->next = token;
	}
	else
		*token_lst = token;
}

t_token	*get_last_token(t_token *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}