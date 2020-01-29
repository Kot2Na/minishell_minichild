/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 19:52:11 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/29 23:44:01 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	print_error(char *name, char *text, char *com)
{
	ft_putstr(name);
	ft_putstr(": ");
	ft_putstr(text);
	ft_putstr(": ");
	ft_putstr(com);	
	ft_putstr("\n");
}

t_lst	*change_pwd(char *pwd, t_lst *list)
{
	t_stat	file;
	char	*old_pwd;
	char	*new_pwd;

	new_pwd = ft_strdup(pwd);
	if (!(stat(new_pwd, &file)))
	{
		if (S_ISDIR(file.st_mode) == 0)
		{
			ft_putstr("cd : not a directory: ");
			//ft_putstr(new_pwd);
			ft_putstr("\n");
		}
		else
		{
			old_pwd = ft_strdup(find_var(list, "PWD"));
			list = ft_setenv(list, "PWD", new_pwd);
			list = ft_setenv(list, "OLDPWD", old_pwd);
			chdir(new_pwd);
			free(old_pwd);
		}
	}
	else
	{
		ft_putstr("cd : no such file or directory: ");
		//ft_putstr(new_pwd);
		ft_putstr("\n");
	}
	free(new_pwd);
	return (list);
}

t_lst	*create_new_pwd(t_lst *pwd_list, char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (ft_strcmp(path[i], "..") == 0)
			lst_del_last(&pwd_list);
		else if (ft_strcmp(path[i], ".") != 0)
			to_end(&pwd_list, new_lst(path[i]));
		i++;
	}
	return (pwd_list);
}

char	*prepare_to_change(char **argv, t_lst *list)
{
	char	**path_arr;
	char	**pwd_arr;
	t_lst	*pwd_list;
	char	*result;

	pwd_arr = ft_strsplit(find_var(list, "PWD"), '/');
	path_arr = ft_strsplit(argv[1], '/');
	pwd_list = cnvrt_to_lst(pwd_arr);
	pwd_list = create_new_pwd(pwd_list, path_arr);
	result = join_lst_to_path(pwd_list);
	del_double_arr(pwd_arr);
	del_double_arr(path_arr);
	lst_del(pwd_list);
	return (result);
}

t_lst	*cd_check(char **argv, t_lst *list)
{
	char	*new_pwd;

	if (count_arr(argv) == 1)
		list = change_pwd(find_var(list, "HOME"), list);
	else if (count_arr(argv) == 2)
	{
		if (argv[1][0] == '/')
			list = change_pwd(argv[1], list);
		else if (argv[1][0] == '-' && argv[1][1] == '\0')
			list = change_pwd(find_var(list, "OLDPWD"), list);
		else
		{
			new_pwd = prepare_to_change(argv, list);
			list = change_pwd(new_pwd, list);
			free(new_pwd);
		}
	}
	else
		ft_putstr("too much argument for cd\n");
	return (list);
}
