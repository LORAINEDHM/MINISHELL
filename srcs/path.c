/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 10:18:26 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/06 13:41:08 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_check_if_directory(char *path, char **cmdpath, t_ms *ms)
{
	DIR	*directory;

	directory = opendir(path);
	if (directory)
	{
		closedir(directory);
		error_msg(IS_DIRECTORY, path, ms);
		return (0);
	}
	if (errno == ENOTDIR)
	{
		*cmdpath = ft_strdup(path);
		return (1);
	}
	error_msg(PATH, path, ms);
	return (0);
}

char	*ms_join_path(char const *s1, char const *s2)
{
	const size_t	size = ft_strlen(s1) + ft_strlen(s2) + 2;
	char			*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, size);
	ft_strlcat(ptr, "/", size);
	ft_strlcat(ptr, s2, size);
	return (ptr);
}

static char	*ms_test_path(t_ms *ms, char *path_dir,
					char *bash_cmd, t_allcmd *allcmd)
{
	struct dirent	*dirent;
	DIR				*dir_ret;

	dir_ret = opendir(path_dir);
	if (!dir_ret)
	{
		error_msg(-1, strerror(errno), ms);
		return (0);
	}
	while (1)
	{
		dirent = readdir(dir_ret);
		if (!dirent)
			break ;
		if (!ft_strncmp(dirent->d_name, bash_cmd, (ft_strlen(bash_cmd) + 1)))
		{
			allcmd->cmdpath = ms_join_path(path_dir, bash_cmd);
			closedir(dir_ret);
			return (allcmd->cmdpath);
		}
	}
	closedir(dir_ret);
	return (0);
}

static int	find_path(t_ms *ms, char **paths, char *bash_cmd, t_allcmd *allcmd)
{
	int	i;

	i = 0;
	while (paths[i] && ft_strncmp(bash_cmd, "..", 3))
	{
		if (ms_test_path(ms, paths[i++], bash_cmd, allcmd))
		{
			ms_free_and_init_dtab(paths);
			return (1);
		}
	}
	ms_free_and_init_dtab(paths);
	if (!ft_strchr(allcmd->cmd, '/'))
	{
		error_msg(CMD_NOT_FOUND, bash_cmd, ms);
		return (0);
	}
	return (ms_check_if_directory(allcmd->cmd, &allcmd->cmdpath, ms));
}

int	ms_path(t_ms *ms, char *bash_cmd, t_allcmd *allcmd)
{
	const char	*path = ms_get_var_value(ms->env_first, "PATH", 4);
	char		**paths;

	paths = ft_split(path, ':');
	if (!paths && path)
	{
		error_msg(-1, strerror(errno), ms);
		return (0);
	}
	else if (path)
		return (find_path(ms, paths, bash_cmd, allcmd));
	return (ms_check_if_directory(allcmd->cmd, &allcmd->cmdpath, ms));
}
