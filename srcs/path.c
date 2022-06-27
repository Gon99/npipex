/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:37:31 by goliano-          #+#    #+#             */
/*   Updated: 2022/06/27 11:43:14 by goliano-         ###   ########.fr       */
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

static int	check_access(char *cmd, char **mycmdargs, char **envp, int t)
{
	int	r;

	r = 0;
	if (t)
	{
		if (access(cmd, X_OK) > -1)
		{
			execve(cmd, mycmdargs, envp);
			r = 1;
		}
	}
	else
	{
		if (access(mycmdargs[0], X_OK) > -1)
		{
			execve(mycmdargs[0], mycmdargs, envp);
			r = 1;
		}
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
	if (handle_error(all_paths))
		exit(EXIT_FAILURE);
	if (check_access(cmd, mycmdargs, envp, 0))
		exit(EXIT_SUCCESS);
	i = -1;
	while (all_paths[++i])
	{
		cmd_one = ft_strjoin(all_paths[i], mycmdargs[0]);
		if (check_access(cmd_one, mycmdargs, envp, 1))
			exit(EXIT_SUCCESS);
		free(cmd_one);
	}
	perror("zsh");
	exit(EXIT_FAILURE);
}
