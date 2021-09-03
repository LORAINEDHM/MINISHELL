/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst.student@19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 15:13:01 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/04 10:57:40 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_add_last(char *content, t_ms *ms, t_token **first, t_token **last)
{
	t_token	*token;

	if (!content)
	{
		error_msg(-1, strerror(errno), ms);
		return (0);
	}
	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
	{
		error_msg(-1, strerror(errno), ms);
		free(content);
		return (0);
	}
	token->content = content;
	ms_remove_quotes(ms, token->content);
	token->previous = *last;
	if (!*first)
		*first = token;
	else
		(*last)->next = token;
	*last = token;
	return (1);
}

int	ms_add_last2(char *content, t_ms *ms, t_token **first, t_token **last)
{
	t_token	*token;

	if (!content)
	{
		error_msg(-1, strerror(errno), ms);
		return (0);
	}
	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
	{
		error_msg(-1, strerror(errno), ms);
		free(content);
		return (0);
	}
	token->content = content;
	token->previous = *last;
	if (!*first)
		*first = token;
	else
		(*last)->next = token;
	*last = token;
	return (1);
}

t_token	*get_token(char *content, t_token *token)
{
	int	sign;
	int	i;

	while (token)
	{
		i = ms_get_index(token->content, &sign);
		if (!ft_strncmp(token->content, content, i)
			&& (!content[i] || content[i] == '=' || content[i] == '+'))
			return (token);
		token = token->next;
	}
	return (NULL);
}

void	remove_env_token_from_list(t_ms *ms, t_token *token)
{
	if (token->content)
		free(token->content);
	if (token == ms->env_first)
		ms->env_first = token->next;
	if (token == ms->env_last)
		ms->env_last = token->previous;
	if (token->next)
		token->next->previous = token->previous;
	if (token->previous)
		token->previous->next = token->next;
	free(token);
}
