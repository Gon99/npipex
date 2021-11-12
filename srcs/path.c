/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:37:31 by goliano-          #+#    #+#             */
/*   Updated: 2021/11/12 12:38:50 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	check_cmd_path(char *cmd)
{
	int	r;

	r = 1;
	if (cmd[0] == '/' || cmd[0] == '.' || cmd[0] == '~')
		r = 0;
	return (r);
}

static int	check_access(char *cmd, char **mycmdargs, char **envp)
{
	int	r;

	r = 0;
	if (access(cmd, X_OK) > -1)
	{
		execve(cmd, mycmdargs, envp);
		r = 1;
	}
	return (r);
}

static int	handle_error(char **all_paths)
{
	int	r;

	r = 0;
	if (!all_paths)
	{
		perror("zsh");
		r = 1;
	}
	return (r);
}

static int	path_index(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (i);
}

int	handle_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**all_paths;
	char	*cmd_one;
	char	**mycmdargs;

	i = path_index(envp);
	path = ft_strtrim(envp[i], "PATH=");
	all_paths = ft_split(path, ':');
	mycmdargs = ft_split(cmd, ' ');
	if (check_access(cmd, mycmdargs, envp))
		return (1);
	if (handle_error(all_paths))
		exit(EXIT_FAILURE);
	i = -1;
	while (all_paths[++i])
	{
		cmd_one = ft_strjoin(all_paths[i], mycmdargs[0]);
		if (check_access(cmd_one, mycmdargs, envp))
			return (1);
		free(cmd_one);
	}
	perror("zsh");
	exit(EXIT_FAILURE);
}
