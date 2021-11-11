/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:37:31 by goliano-          #+#    #+#             */
/*   Updated: 2021/11/11 17:01:31 by goliano-         ###   ########.fr       */
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

int	check_access(char *cmd, char **mycmdargs, char **envp)
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

int	handle_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**all_paths;
	char	*cmd_one;
	char	**mycmdargs;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
	path = ft_strtrim(envp[i], "PATH=");
	all_paths = ft_split(path, ':');
	mycmdargs = ft_split(cmd, ' ');
	i = 0;
	if (check_access(cmd, mycmdargs, envp))
		return (1);
	if (!all_paths)
	{
		perror("command not found");
		exit(EXIT_FAILURE);
	}
	while (all_paths[i])
	{
		cmd_one = ft_strjoin(all_paths[i], mycmdargs[0]);
		if (check_access(cmd_one, mycmdargs, envp))
			return (1);
		i++;
	}
	perror("zsh");
	exit(EXIT_FAILURE);
}
