/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_prints.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:53:21 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/31 19:56:11 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	print_echo(char **argv)
{
	int	i;

	i = 1;
	if (argv)
	{
		while (argv[i])
		{
			ft_putstr(argv[i]);
			i++;
			if (argv[i])
				ft_putchar(' ');
		}
	}
	ft_putchar('\n');
}

void	print_error(char *name, char *text, char *com)
{
	ft_putstr(name);
	ft_putstr(": ");
	ft_putstr(text);
	ft_putstr(": ");
	ft_putstr(com);
	ft_putstr("\n");
}

void	print_env(t_lst *list)
{
	if (list)
	{
		while (list)
		{
			ft_putstr(list->data);
			ft_putchar('\n');
			list = list->next;
		}
	}
}
