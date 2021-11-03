/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 15:32:36 by goliano-          #+#    #+#             */
/*   Updated: 2021/11/03 17:02:50 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/pipex.h"

void	handle_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**all_paths;
	char	*cmd_one;
	char	**mycmdargs;

	i = -1;
	printf("HANDLE. %s\n", cmd);
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
	path = ft_strtrim(envp[i], "PATH=");
	all_paths = ft_split(path, ':');
	mycmdargs = ft_split(cmd, ' ');
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

static void	do_child_one(int fd, char *cmd, int *end, char **envp)
{
	int	r;

	r = 0;
	close(end[0]);
	r = dup2(fd, STDIN_FILENO);
	close(fd);
	printf("R1: %d\n", r);
	r = dup2(end[1], STDOUT_FILENO);
	printf("R2: %d\n", r);
	printf("EY\n");
	printf("CM: %s\n", cmd);
	printf("EN: %s\n", envp[0]);
	handle_path(cmd, envp);
	printf("FIN\n");
	exit(0);
}

/*static void	do_child_two(int fd, char **argv, int *end, char **envp)
{
	int	nfd;

	printf("FD2: %d\n", fd);
	close(end[1]);
	nfd = open(argv[4], O_WRONLY);
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	dup2(nfd, STDOUT_FILENO); //para que lo escriba en el archivo
	handle_path(argv[3], envp);
	
}*/

static void	do_parent_one(int fd2, char *cmd, int *end, char **envp)
{
	int status;
	int	r;

	status = 0;
	r = 0;
	waitpid(-1, &status, 0);
	printf("adios\n");
	printf("OuT: %d\n", STDOUT_FILENO);
	//printf("R3: %d\n", r);
	r = dup2(end[0], end[1]);
	printf("R4: %d\n", r);
	//close(end[1]);
	r = dup2(fd2, end[0]);
	close(fd2);
	handle_path(cmd, envp);
}

static void	pipex(int fd1, int fd2, char **argv, char **envp)
{
	int	end[2];
	//int	status;
	pid_t	p1;
	//pid_t	p2;

	pipe(end);
	p1 = fork();
	printf("P1: %d\n", p1);
	if (p1 < 0)
		return (perror("Fork: "));
	if(p1 == 0)
		do_child_one(fd1, argv[2], end, envp);
	else
		do_parent_one(fd2, argv[3], end, envp);
	printf("1");
	/*p2 = fork();
	if (p2 < 0)
		return (perror("Fork: "));
	else if(p2 == 0)
		do_child_two(fd2, argv, end, envp);
	else
		close(end[0]);
	waitpid(p1, &status, 0);
	waitpid(p2, &status, 0);*/
}

int	main(int argc, char **argv, char **envp)
{
	int	fd1;
	int	fd2;

	if (argc == 0)
		return (1);
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0 || fd2 < 0)
		return (-1);
	pipex(fd1, fd2, argv, envp);
}
