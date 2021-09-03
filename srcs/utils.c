/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst.student@19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 13:27:48 by tvanelst          #+#    #+#             */
/*   Updated: 2021/07/30 13:55:07 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_get_var_value(t_token *env, char *var, int size)
{
	while (env)
	{
		if (!ft_strncmp(env->content, var, size) && env->content[size] == '=')
			return (ft_strchr(env->content, '=') + 1);
		env = env->next;
	}
	return (NULL);
}
