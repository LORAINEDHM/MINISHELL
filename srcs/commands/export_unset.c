/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst.student@19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 11:41:00 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/04 10:57:28 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_get_index(char *content, int *sign)
{
	int	i;

	i = 0;
	*sign = 0;
	if (ft_isdigit(*content) || *content == '+' || *content == '=')
		return (-1);
	while (content[i] && content[i] != '+' && content[i] != '=')
	{
		if (!(ft_isalnum(content[i])) && content[i] != '_')
			return (-1);
		i++;
	}
	if (content[i] == '+')
	{
		*sign = 1;
		i++;
	}
	if (content[i] == '=')
		return (i - *sign);
	else
	{
		if (*sign == 1)
			return (-1);
		return (-2);
	}
}

void	ms_unset(t_ms *ms, char *content, int index, int sign)
{
	t_token	*token;

	(void)index;
	(void)sign;
	token = get_token(content, ms->env_first);
	if (token)
		remove_env_token_from_list(ms, token);
	ms->last_output = 0;
}

int	get_var_name(t_ms *ms, t_token **token, char *content, int index)
{
	char	*var_name;

	var_name = ft_substr(content, 0, index);
	if (!var_name)
	{
		error_msg(-1, strerror(errno), ms);
		return (0);
	}
	*token = get_token(var_name, ms->env_first);
	free(var_name);
	ms->last_output = 0;
	return (1);
}

void	ms_export(t_ms *ms, char *content, int index, int sign)
{
	char	*new_content;
	t_token	*token;

	token = NULL;
	if (!get_var_name(ms, &token, content, index))
		return ;
	if (token)
	{
		if (sign == 1)
			new_content = ft_strjoin(token->content, &content[index + 2]);
		else
			new_content = ft_strdup(content);
		free(token->content);
		token->content = new_content;
		if (!token->content)
		{
			remove_env_token_from_list(ms, token);
			return (error_msg(-1, strerror(errno), ms));
		}
		return ;
	}
	ft_memcpy(content + index, content + index + sign,
		ft_strlen(content + index));
	ms_add_last2(ft_strdup(content), ms, &ms->env_first, &ms->env_last);
}

void	ms_export_unset(t_ms *ms, t_token *args,
			void (*f)(t_ms *, char *, int, int))
{
	int		index;
	int		sign;

	if (f == ms_export && !args)
		ms_env(ms, ms->env_first, 1);
	while (args)
	{
		index = ms_get_index(args->content, &sign);
		if (f == ms_export && index == -1)
		{
			ms->last_output = 1;
			error_msg(EXPORT_UNVALID_IDENTIFIER, args->content, ms);
		}
		else if ((f == ms_export) == (index != -2))
			f(ms, args->content, index, sign);
		args = args->next;
	}
}
