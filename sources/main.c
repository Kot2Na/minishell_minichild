/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 04:39:22 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/28 22:40:14 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	minishell(t_lst *list)
{
	int		i;
	char	*line;
	char	*save;
	char	**arr;

	while(1)
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
				list = env_com(arr[i], list);
				if (ft_strcmp("exit", arr[i]) == 0)
				{
					free(line);
					del_double_arr(arr);
					return (0);
				}
				i++;
			}
			free(line);
			del_double_arr(arr);
		}
	}
	return (0);
}

int main(int ac, char **av, char **env)
{
	t_lst *list;

	list = cnvrt_to_lst(env);
	minishell(list);
	lst_del(list);
	return (0);
}
