/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 19:10:04 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/30 23:54:39 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_lst	*find_env(t_lst *list, char *name)
{
	t_lst	*iter;
	int		size;

	iter = NULL;
	if (list)
	{
		iter = list;
		size = ft_strlen(name);
		while (iter)
		{
			if (!ft_strncmp(iter->data, name, size) && iter->data[size] == '=')
				return (iter);
			iter = iter->next;
		}
	}
	return (iter);
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

t_lst	*setenv_check(char **argv, t_lst *list)
{
	int i;
	int j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (ft_strcmp(argv[0], "setenv") == 0)
		{
			while (argv[i][j])
			{
				if (argv[i][j] == '=')
				{
					argv[i][j] = '\0';
					list = ft_setenv(list, argv[i], argv[i] + j + 1);
				}
				j++;
			}
		}
		else
			list = ft_unsetenv(list, argv[i]);
		i++;
	}
	return (list);
}

t_lst	*ft_setenv(t_lst *list, char *name, char *str)
{
	t_lst	*change;
	char	*save;

	if ((change = find_env(list, name)))
	{
		free(change->data);
		change->data = join_three(name, "=", str);
	}
	else
	{
		save = join_three(name, "=", str);
		to_end(&list, new_lst(save));
		free(save);
	}
	return (list);
}

t_lst	*ft_unsetenv(t_lst *list, char *name)
{
	t_lst *del;
	t_lst *change;

	change = list;
	if ((del = find_env(list, name)))
	{
		if (change == del)
		{
			change = del->next;
			free(del->data);
			free(del);
			return (change);
		}
		else
		{
			while (change->next != del)
				change = change->next;
			change->next = del->next;
			free(del->data);
			free(del);
		}
	}
	return (list);
}
