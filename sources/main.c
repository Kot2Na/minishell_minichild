/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 04:39:22 by crycherd          #+#    #+#             */
/*   Updated: 2020/02/01 00:08:10 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
#include <readline/readline.h>

int		minishell(t_lst *list, char *line)
{
	int		i;
	char	*save;
	char	**arr;

	arr = split_wquote(line, ';', 0);
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
			del_double_arr(arr);
			return (1);
		}
		list = env_com(arr[i], list);
		i++;
	}
	del_double_arr(arr);
	return (0);
}

void	kill_proc(int sig)
{
	if (sig == SIGINT && kill_pid != 0)
	{
		if (kill(kill_pid, sig) == 0)
		{
			kill_pid = 0;
		}
		ft_putstr("\n");
		return ;
	}
}

t_lst	*shell_lvl(t_lst *list)
{
	int		i;
	char	*str;

	i = 1;
	if (find_var(list, "SHLVL"))
	{
		i = ft_atoi(find_var(list, "SHLVL"));
		i++;
	}
	str = ft_itoa(i);
	list = ft_setenv(list, "SHLVL", str);
	free(str);
	return (list);
}

int		main(int ac, char **av, char **env)
{
	t_lst	*list;
	char	*line;
	int		i;

	kill_pid = 0;
	signal(SIGINT, kill_proc);
	list = cnvrt_to_lst(env);
	list = shell_lvl(list);
	while (1)
	{
		if ((line = readline("^_^ ->")))
		{
			if (!check_parse(line, ';'))
			{
				if (minishell(list, line))
				{
					free(line);
					break ;
				}
			}
			free(line);
		}
	}
	lst_del(list);
	return (0);
}
