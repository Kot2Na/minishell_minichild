/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 19:10:04 by crycherd          #+#    #+#             */
/*   Updated: 2020/02/01 17:06:52 by crycherd         ###   ########.fr       */
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

t_lst	*add_or_del_var(char *str, t_lst *list)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			str[i] = '\0';
			list = ft_setenv(list, str, str + i + 1);
			break ;
		}
		i++;
	}
	return (list);
}

t_lst	*setenv_check(char **argv, t_lst *list)
{
	int i;

	i = 1;
	if (count_arr(argv) > 1)
	{
		while (argv[i])
		{
			if (ft_strcmp(argv[0], "setenv") == 0)
				list = add_or_del_var(argv[i], list);
			else
				list = ft_unsetenv(list, argv[i]);
			i++;
		}
	}
	else
		ft_putstr("minishell: not enough argument\n");
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
