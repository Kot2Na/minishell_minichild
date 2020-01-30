/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 04:39:22 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/31 00:20:51 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int		minishell(t_lst *list)
{
	int		i;
	char	*line;
	char	*save;
	char	**arr;

	while (1)
	{
		ft_putstr("./minishell");
		ft_putstr("->");
		if ((i = get_next_line(0, &line)))
		{
			arr = ft_strsplit(line, ';');
			i = 0;
			while (arr[i])
			{
				save = arr[i];
				arr[i] = insert_var(arr[i], list);
				free(save);
				save = arr[i];
				arr[i] = del_spaces(arr[i]);
				free(save);
				if (ft_strcmp("exit", arr[i]) == 0)
				{
					free(line);
					del_double_arr(arr);
					return (0);
				}
				list = env_com(arr[i], list);
				i++;
			}
			free(line);
			del_double_arr(arr);
		}
	}
	return (0);
}

void	kill_proc(int sig)
{
	if (kill_pid != 0)
	{
		if (kill(kill_pid, sig) == 0)
		{
			kill_pid = 0;
		}
	}
}

int		main(int ac, char **av, char **env)
{
	t_lst *list;

	kill_pid = 0;
	signal(SIGINT, kill_proc);
	list = cnvrt_to_lst(env);
	minishell(list);
	lst_del(list);
	return (0);
}
