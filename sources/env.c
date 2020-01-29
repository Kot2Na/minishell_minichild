/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 19:57:55 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/29 21:54:06 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
#include "stdio.h"

void run_exe(char *path, char **argv, t_lst *list)
{
	pid_t	pid;
	char	**env;
	int		status;
	int		i;

	env = cnvrt_to_arr(list);
	pid = fork();
	kill_pid = pid;
	if (pid == 0)
	{
		execve(path, argv, env);
		exit(0);
	}
	waitpid(pid, &status, 0);
	del_double_arr(env);
}

void	run_command(char **argv, char **path,  t_lst *list)
{
	char	*track;

	if (path && (track = path_to_bin(path, argv[0])))
	{
		run_exe(track, argv, list);
		free(track);
	}
	else
	{
		ft_putstr("minishell: command not found: ");
		ft_putstr(argv[0]);
		ft_putstr("\n");
	}
}

t_lst	*to_file_or_dir(char **argv, char **path, t_lst *list)
{
	t_stat	file;

	if (!(stat(argv[0], &file)))
	{
		if (S_ISDIR(file.st_mode) == 0)
		{
			run_exe(argv[0], argv, list);
		}
	}
	else
		ft_putstr("file or dir not exist\n");
	return (list);
}

t_lst	*env_com(char *av, t_lst *list)
{
	char **path;
	char **argv;
	int	i;

	path = ft_strsplit(find_var(list, "PATH"), ':');
	argv = ft_strsplit(av, ' ');
	/*
	i = 0;
	while (argv[i])
	{
		ft_putchar('|');
		ft_putstr(argv[i]);
		ft_putstr("|  - ");
		ft_putnbr(i);
		ft_putchar('\n');
		i++;
	}
	*/
	if (argv[0])
	{
		if (!check_path(argv[0]))
		{
			if (ft_strcmp(argv[0], "cd") == 0)
			{
				list = cd_check(argv, list);
			}
			else if (ft_strcmp(argv[0], "setenv") == 0 || \
						ft_strcmp(argv[0], "unsetenv") == 0)
			{
				list = setenv_check(argv, list);
			}
			else
			{
				run_command(argv, path, list);
			}
		}
		else
		{
			list = to_file_or_dir(argv, path, list);
		}
	}
	del_double_arr(path);
	del_double_arr(argv);
	return (list);
}
