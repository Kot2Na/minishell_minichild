/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 20:39:09 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/31 19:51:22 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int		check_exist(char **path, char *com)
{
	int		i;
	int		result;
	char	*box;

	i = 0;
	result = 0;
	while (path[i])
	{
		box = join_three(path[i], "/", com);
		if (!access(box, F_OK))
		{
			result = 1;
			free(box);
			break ;
		}
		free(box);
		i++;
	}
	return (result);
}

char	*path_to_bin(char **path, char *com)
{
	int		i;
	char	*box;

	i = 0;
	while (path[i])
	{
		box = join_three(path[i], "/", com);
		if (!access(box, F_OK))
			return (box);
		free(box);
		i++;
	}
	return (NULL);
}

char	*join_lst_to_path(t_lst *list)
{
	char	*sub;
	char	*str;

	str = ft_strdup("/");
	if (list)
	{
		free(str);
		str = ft_strdup("");
		while (list)
		{
			sub = str;
			str = join_three(str, "/", list->data);
			free(sub);
			list = list->next;
		}
	}
	return (str);
}

void	run_exe(char *path, char **argv, t_lst *list)
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
