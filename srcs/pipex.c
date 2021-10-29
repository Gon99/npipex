/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 15:32:36 by goliano-          #+#    #+#             */
/*   Updated: 2021/10/29 17:50:58 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/pipex.h"

void	handle_path(char **env, char **argv, char **envp)
{
	int		i;
	char	*path;
	char	**all_paths;
	char	*cmd_one;
	char	**mycmdargs;

	i = -1;
	while (env[++i])
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
	path = ft_strtrim(env[i], "PATH=");
	all_paths = ft_split(path, ':');
	mycmdargs = ft_split(argv[2], ' ');
	i = 0;
	while (all_paths[i])
	{
		all_paths[i] = ft_strcatslash(all_paths[i]);
		cmd_one = ft_strjoin(all_paths[i], mycmdargs[0]);
		printf("C: %s\n", cmd_one);
		execve(cmd_one, mycmdargs, envp);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	/*int		end[2];
	pid_t	child1;
	pid_t	child2;

	pipe(end);
	child1 = fork();
	if (child1 < 0)
	if (argc == 0)
		return (0);
	*/
	if (argc == 0)
		return (0);
	handle_path(envp, argv, envp);	
}
