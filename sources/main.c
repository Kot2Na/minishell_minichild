/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 04:39:22 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/25 20:08:02 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int main(int ac, char **av, char **env)
{
	int i;
	char *line;
	t_lst *list;
	t_lst *head;

	i = 0;
	line = NULL;
	list = cnvrt_to_lst(env);
	head = list;
	while(1)
	{
		ft_putstr(av[0]);
		ft_putstr("->");
		if ((i = get_next_line(0, &line)))
		{
			list = env_com(line, list);
			if (ft_strcmp("exit", line) == 0)
			{
				free(line);
				break ;
			}
			free(line);
		}
	}
	lst_del(head);
	return (0);
}
