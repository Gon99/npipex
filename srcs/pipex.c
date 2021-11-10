/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 15:32:36 by goliano-          #+#    #+#             */
/*   Updated: 2021/11/10 17:03:21 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/pipex.h"

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
	while (all_paths[i])
	{
		cmd_one = ft_strjoin(all_paths[i], mycmdargs[0]);
		if (access(cmd_one, F_OK | R_OK | X_OK) > -1)
		{
			execve(cmd_one, mycmdargs, envp);
			return (1);
		}
		i++;
	}
	//perror("zsh");
	exit(1);
}

static void	do_child_one(int fd, char *cmd, int *end, char **envp)
{
	close(end[0]);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(end[1], STDOUT_FILENO);
	handle_path(cmd, envp);
}

/*static void	do_parent_one(char *cfd, char *cmd, int *end, char **envp)
{
	int status;
	int	fd;

	status = 0;
	close(end[1]);
	dup2(end[0], STDIN_FILENO);
	fd = open(cfd, O_CREAT | O_RDWR | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	handle_path(cmd, envp);
}*/

static char	*handle_cmd(char *cmd)
{
	int		l;
	int		i;
	char	*n_cmd;

	l = ft_strlen(cmd);
	n_cmd = malloc(sizeof(char) * (l + 2));
	if (!n_cmd)
		return (0);
	l = 1;
	i = 0;
	n_cmd[0] = '/';
	while (cmd[i])
		n_cmd[l++] = cmd[i++];
	n_cmd[l] = '\0';
	return (n_cmd);
}

void	do_child_two(char *cfd, char *cmd, int *end, char **envp)
{
	int fd;

	close(end[1]);
	fd = open(cfd, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(end[0], STDIN_FILENO);
	//close(end[0]);
	handle_path(cmd, envp);
}

static void	pipex(int fd1, char **argv, char **envp)
{
	int	end[2];
	pid_t	p1;
	pid_t	p2;
	int		status;

	pipe(end);
	p1 = fork();
	if (p1 < 0)
		return (perror("Fork: "));
	if (p1 == 0)
		do_child_one(fd1, argv[2], end, envp);
	p2 = fork();
	if (p2 < 0)
		return (perror("Fork: "));
	if (p2 == 0)
		do_child_two(argv[4], argv[3], end, envp);
	close(end[0]);
	close(end[1]);
	waitpid(p1, &status, 0);
	if (status != 0)
	{
		return (perror("zsh"));
		exit(0);
	}
	waitpid(p2, &status, 0);
	if (status != 0)
	{
		//return (perror("zsh"));
		//exit(0);
	}
}

/*void	leaks(void)
{
	system("leaks -q pipex");
}*/

int	main(int argc, char **argv, char **envp)
{
	int	fd1;
	
	//atexit(leaks);
	if (argc == 0)
		return (1);
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 < 0)
	{
		perror("zsh");
		exit(1);
	}
	argv[2] = handle_cmd(argv[2]);
	argv[3] = handle_cmd(argv[3]);
	pipex(fd1, argv, envp);
	return (0);
}
