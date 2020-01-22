/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 19:57:55 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/22 23:59:41 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	run_command(char **argv, char **path,  t_lst *list)
{
	char	*track;
	char	**env;
	int		status;
	pid_t	pid;

	if ((track = path_to_bin(path, argv[0])))
	{
		env = cnvrt_to_arr(list);
		pid = fork();
		if (pid == 0)
		{
			execve(track, argv, env);
		}
		waitpid(pid, &status, 0);
		free(track);
		del_double_arr(env);
	}
	else
	{
		ft_putstr("nea\n");
	}
}


void	env_com(char *av, t_lst *list)
{
	char **path;
	char **argv;
	int	i;

	i = 0;
	path = ft_strsplit(find_var(list, "PATH"), ':');
	argv = ft_strsplit(av, ' ');
	if (!check_path(argv[0]))
	{
		run_command(argv, path, list);
	}
	del_double_arr(path);
	del_double_arr(argv);
}
