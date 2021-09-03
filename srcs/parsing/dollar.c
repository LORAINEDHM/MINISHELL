/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedison <timothyedison@hotmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 11:52:56 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/03 15:13:02 by tedison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_get_var_name_length(char *line)
{
	int	size;

	size = 0;
	if (*line == '?' || ft_isdigit(*line))
		return (1);
	if (!ft_isalnum(*line))
		return (0);
	else
		while (ft_isalnum(line[size]) || line[size] == '_')
			size++;
	return (size);
}

static int	ms_copy_newline_dollar(t_ms *ms, t_var *var, char **line)
{
	const int	newline_length = ft_strlen(*line) - var->name_length
			+ var->value_length + 1;
	char		*new_line;

	new_line = (malloc(sizeof(char) * (newline_length)));
	if (!new_line)
	{
		error_msg(-1, strerror(errno), ms);
		return (0);
	}
	ft_strlcpy(new_line, *line, var->start);
	if (var->value)
		ft_strlcat(new_line, var->value, newline_length);
	ft_strlcat(new_line, line[0] + var->start + var->name_length,
		newline_length);
	if (line[0][var->start] == '?')
		free(var->value);
	free(*line);
	*line = new_line;
	return (1);
}

static int	ms_replace_var_by_value(t_ms *ms, t_var *var, char **line)
{
	var->name_length = ms_get_var_name_length(line[0] + var->start);
	if (line[0][var->start] == '?')
	{
		var->value = ft_itoa(ms->last_output);
		if (!var->value)
		{
			error_msg(-1, strerror(errno), ms);
			return (0);
		}
	}
	else
		var->value = ms_get_var_value(ms->env_first, line[0]
				+ var->start, var->name_length);
	if (var->value)
		var->value_length = ft_strlen(var->value);
	return (ms_copy_newline_dollar(ms, var, line));
}

static int	ms_check_and_record_variable(t_ms *ms, char **line)
{
	t_var	var;
	size_t	i;

	var = (t_var){};
	i = 0;
	while (line[0][i])
	{
		ms_quoteflag(ms, line[0][i++]);
		var.start++;
		if (line[0][i - 1] == '$' && !(S_Q & ms->quoteflag)
			&& line[0][i] && line[0][i] != ' ')
		{
			if (!(D_Q & ms->quoteflag)
				&& (line[0][i] == '\'' || line[0][i] == '"'))
			{
				ft_memcpy(line[0] + i - 1, line[0] + i,
					ft_strlen(line[0] + i) + 1);
				return (1);
			}
			else if (ft_isalnum(line[0][i])
				|| line[0][i] == '_' || line[0][i] == '?')
				return (ms_replace_var_by_value(ms, &var, line));
		}
	}
	return (2);
}

int	ms_dollar(t_ms *ms, char **token)
{
	int	return_value;

	while (1)
	{
		ms->quoteflag = 0;
		return_value = ms_check_and_record_variable(ms, token);
		if (!return_value)
			return (0);
		else if (return_value == 2)
			break ;
	}
	return (1);
}
