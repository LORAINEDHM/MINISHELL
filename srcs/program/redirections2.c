/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst.student@19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 15:03:05 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/05 14:12:59 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	EOF_error(int line_nbr, char *stop, char *flag)
{
	if (!g_env.fd_heredoc)
	{
		ft_putstr_fd("bash: warning: here-document at line ", 1);
		ft_putnbr_fd(line_nbr, 1);
		ft_putstr_fd(" delimited by end-of-file (wanted `", 1);
		ft_putstr_fd(stop, 1);
		ft_putstr_fd("')\n", 1);
	}
	else
		dup2(g_env.fd_heredoc, STDIN_FILENO);
	*flag = 0;
}

static int	compare_input_and_stop(char *line, char *stop, int fd)
{
	if (strncmp(line, stop, ft_strlen(line)))
	{
		ft_putendl_fd(line, fd);
		free(line);
		return (1);
	}
	return (0);
}

static int	ms_id_redirection(char *stop, int fd, int line_nbr, char *flag)
{
	char		*line;
	int			count_iter;

	g_env.heredoc = 1;
	count_iter = 0;
	while (19)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			EOF_error(line_nbr, stop, flag);
			return (count_iter);
		}
		count_iter++;
		if (compare_input_and_stop(line, stop, fd))
			continue ;
		free(line);
		break ;
	}
	return (count_iter);
}

int	ms_all_id_redirection(t_ms *ms, t_token *input)
{
	int			fd;
	static int	line_nbr = 1;
	char		flag;

	flag = 1;
	while (input)
	{
		flag = 1;
		fd = get_fd(ms, HEREDOC, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
			return (0);
		line_nbr += ms_id_redirection(input->content, fd, line_nbr, &flag);
		g_env.heredoc = 0;
		close(fd);
		if (g_env.fd_heredoc)
		{
			g_env.fd_heredoc = 0;
			line_nbr++;
			return (0);
		}
		if (input == ms->allcmd->dinputl)
			line_nbr++;
		input = input->next;
	}
	return (flag);
}
