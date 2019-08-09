/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 04:39:22 by crycherd          #+#    #+#             */
/*   Updated: 2019/08/09 21:19:59 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int main(int ac, char **av, char **env)
{
	int i;
	char *line;
	char **path;
	t_lst *list;
	t_lst *head;

	i = 0;
	line = NULL;
	list = cnvrt_to_lst(env);
	path = ft_strsplit(find_var(list, "PATH"), ':');
	head = list;
	while(1)
	{
		if ((i = get_next_line(0, &line)))
		{
			if (check_exist(path, line))
			{
				ft_putstr(line);
				ft_putstr(" exist\n");
			}
			else
			{
				ft_putstr(line);
				ft_putstr(" don't exist\n");
			}
			if (ft_strcmp("exit", line) == 0)
			{
				free(line);
				break ;
			}
			free(line);
		}
	}
	del_double_arr(path);
	lst_del(head);
	return (0);
}
