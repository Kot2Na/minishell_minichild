/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 19:52:11 by crycherd          #+#    #+#             */
/*   Updated: 2020/02/01 17:46:02 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_lst	*change_pwd(char *pwd, t_lst *list)
{
	char	*old_pwd;
	char	*new_pwd;

	if (find_var(list, "PWD"))
		old_pwd = ft_strdup(find_var(list, "PWD"));
	else
	{
		old_pwd = ft_strnew(BUFSIZE + 1);
		old_pwd = getcwd(old_pwd, BUFSIZE);
	}
	new_pwd = ft_strdup(pwd);
	list = ft_setenv(list, "PWD", new_pwd);
	list = ft_setenv(list, "OLDPWD", old_pwd);
	chdir(new_pwd);
	free(old_pwd);
	free(new_pwd);
	return (list);
}

t_lst	*check_pwd(char *pwd, t_lst *list, char *comm)
{
	t_stat	file;
	char	*new_pwd;

	new_pwd = del_double_char(pwd, '/');
	if (!(stat(new_pwd, &file)))
	{
		if (S_ISDIR(file.st_mode) == 0)
			print_error("cd", "not a directory", comm);
		else
			list = change_pwd(new_pwd, list);
	}
	else
		print_error("cd", "no such file or directory", comm);
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

char	*prepare_to_change(char *argv, t_lst *list)
{
	char	**path_arr;
	char	**pwd_arr;
	t_lst	*pwd_list;
	char	*result;

	if (find_var(list, "PWD"))
	{
		pwd_arr = ft_strsplit(find_var(list, "PWD"), '/');
	}
	else
	{
		result = ft_strnew(BUFSIZE + 1);
		result = getcwd(result, BUFSIZE);
		pwd_arr = ft_strsplit(result, '/');
		free(result);
	}
	path_arr = ft_strsplit(argv, '/');
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
			list = check_pwd(argv[1], list, argv[1]);
		else if (argv[1][0] == '-' && argv[1][1] == '\0')
		{
			if (find_var(list, "OLDPWD"))
				list = change_pwd(find_var(list, "OLDPWD"), list);
			else
				ft_putstr("You have deleted OLDPWD :c\n");
		}
		else
		{
			new_pwd = prepare_to_change(argv[1], list);
			list = check_pwd(new_pwd, list, argv[1]);
			free(new_pwd);
		}
	}
	else
		ft_putstr("too much argument for cd\n");
	return (list);
}
