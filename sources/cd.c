/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 19:52:11 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/25 23:30:01 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
#include <stdio.h>

t_lst	*change_pwd(char **argv, t_lst *list)
{
	char *str;
	char **path;
	char **pwd;
	t_lst *pwd_list;
	t_lst *iter;
	t_stat	file;
	int i;

	if (count_arr(argv) < 3)
	{
		i = 0;
		pwd = ft_strsplit(find_var(list, "PWD"), '/');
		pwd_list = cnvrt_to_lst(pwd);
		path = ft_strsplit(argv[1], '/');
		while (path[i])
		{
			iter = pwd_list;
			if (ft_strcmp(path[i], "..") == 0)
			{
				lst_del_last(&pwd_list);
			}
			else if (ft_strcmp(path[i], ".") != 0)
			{
				to_end(&pwd_list, new_lst(path[i]));
			}
			i++;
		}
		str = join_lst_to_path(pwd_list);
		ft_putstr(str);
		ft_putchar('\n');

		if (!(stat(str, &file)))
		{
			if (S_ISDIR(file.st_mode) == 0)
			{
				ft_putstr("it is file\n");
			}
			else
			{
				ft_putstr("yea, let's change pwd\n");
			}
		}
		else
		{
			ft_putstr("file or dir not exist\n");
		}

		del_double_arr(pwd);
		del_double_arr(path);
		lst_del(pwd_list);
	}
	return (list);
}
