/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 04:39:22 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/29 22:23:22 by crycherd         ###   ########.fr       */
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
			save = line;
			line = del_spaces(line);
			free(save);
			arr = ft_strsplit(line, ';');
			i = 0;
			while (arr[i])
			{
				if (ft_strcmp("exit", arr[i]) == 0)
				{
					free(line);
					del_double_arr(arr);
					return (0);
				}
				save = arr[i];
				arr[i] = insert_var(arr[i], list);
				free(save);
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
