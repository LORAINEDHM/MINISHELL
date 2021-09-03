/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedison <timothyedison@hotmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 16:55:39 by tedison           #+#    #+#             */
/*   Updated: 2021/08/03 18:23:37 by tedison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg3(int error, char *str, t_ms *ms)
{
	ft_putstr(str);
	if (error == CMD_NOT_FOUND)
	{
		ft_putstr(": command not found");
		ms->last_output = 127;
	}
	else if (error == I_REDIRECTION_ERROR)
		ft_putstr(": No such file or directory");
	else if (error == TOO_MANY_ARGS)
		ft_putstr("too many arguments");
	else if (error == HOME_NOT_SET)
		ft_putstr("HOME not set");
	else if (error == PATH)
	{
		ft_putstr(": ");
		ft_putstr(strerror(errno));
	}
	else if (error == IS_DIRECTORY)
	{
		ft_putstr(": Is a directory");
		ms->last_output = 126;
	}
}

void	error_msg2(int error, char *str, t_ms *ms)
{
	if (error == SYNTAX_ERROR)
	{
		ft_putstr("syntax error near unexpected token `");
		if (!*str)
			ft_putstr("newline");
		else if (*str == *(str + 1))
			write(1, str, 2);
		else
			write(1, str, 1);
		ft_putstr("'");
	}
	else if (error == EXPORT_UNVALID_IDENTIFIER)
	{
		ft_putstr("export: `");
		ft_putstr(str);
		ft_putstr("': not a valid identifier");
	}
	else if (error == NUMERIC_ARGUMENT_REQUIRED)
	{
		ft_putstr("exit: ");
		ft_putstr(str);
		ft_putstr(": numeric argument required");
	}
	else
		error_msg3(error, str, ms);
}

void	error_msg(int error, char *str, t_ms *ms)
{
	if (error == ERROR_RETRIEVING_CURRENT_DIRECTORY)
	{	
		ft_putstr("cd: error retrieving current directory: getcwd: cannot access \
parent directories: No such file or directory\n");
		return ;
	}
	if (error == NO_SUCH_FILE_DIRECTORY)
	{
		ft_putstr("env: ");
		ft_putstr(str);
		ft_putstr(": No such file or directory\n");
		return ;
	}
	ft_putstr("bash: ");
	if (error == UNVALID_PATH)
	{
		ft_putstr("cd: ");
		ft_putstr(str);
		ft_putstr(": ");
		ft_putstr(strerror(errno));
		ms->last_output = 1;
	}
	else
		error_msg2(error, str, ms);
	ft_putstr("\n");
}
