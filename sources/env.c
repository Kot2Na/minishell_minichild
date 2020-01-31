/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 19:57:55 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/31 23:10:11 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
#include <stdio.h>

void	run_command(char **argv, char **path, t_lst *list)
{
	char	*track;
	t_stat	file;

	if (path && (track = path_to_bin(path, argv[0])))
	{
		run_exe(track, argv, list);
		free(track);
	}
	else
	{
		track = prepare_to_change(argv[0], list);
		if (!(stat(track, &file)) && S_ISDIR(file.st_mode))
			list = change_pwd(track, list);
		else
			print_error("minishell", "command not found", argv[0]);
		free(track);
	}
}

t_lst	*to_file_or_dir(char **argv, char **path, t_lst *list)
{
	t_stat	file;
	char	*pwd;

	if (argv[0][0] == '/')
		pwd = ft_strdup(argv[0]);
	else if (argv[0][0])
		pwd = prepare_to_change(argv[0], list);
	if (!(stat(pwd, &file)))
	{
		if (S_ISDIR(file.st_mode) == 0)
			run_exe(pwd, argv, list);
		else
		{
			if (count_arr(argv) == 1)
				list = check_pwd(pwd, list, argv[0]);
			else
				print_error("minishell", "permission denied", argv[0]);
		}
	}
	else
		print_error("minishell", "file or dir not exist", argv[0]);
	free(pwd);
	return (list);
}

void	add_to_list(char *str, int i, t_lst **list, int k)
{
	char	*line;
	char	*save;

	if (list)
	{
		line = ft_strnew(i + 1);
		line = ft_strncpy(line, str, i);
		if (check_quote(line) && k)
		{
			save = line;
			line = del_quotes(line);
			free(save);
		}
		to_end(list, new_lst(line));
		free(line);
	}
}

t_lst	*builitins(char **argv, char **path, t_lst *list)
{
	if (ft_strcmp(argv[0], "cd") == 0)
		list = cd_check(argv, list);
	else if (ft_strcmp(argv[0], "setenv") == 0 || \
				ft_strcmp(argv[0], "unsetenv") == 0)
		list = setenv_check(argv, list);
	else if (ft_strcmp(argv[0], "echo") == 0)
		print_echo(argv);
	else if (ft_strcmp(argv[0], "env") == 0)
		print_env(list);
	else if (argv[0][0])
		run_command(argv, path, list);
	return (list);
}

t_lst	*env_com(char *av, t_lst *list)
{
	char	**path;
	char	**argv;
	int		i;

	path = ft_strsplit(find_var(list, "PATH"), ':');
	argv = split_wquote(av, ' ', 1);
	i = 0;
	while (argv[i])
	{
		printf("|%s|\n", argv[i]);
		i++;
	}
	if (argv[0])
	{
		if (!check_path(argv[0]))
			list = builitins(argv, path, list);
		else
			list = to_file_or_dir(argv, path, list);
	}
	del_double_arr(path);
	del_double_arr(argv);
	return (list);
}
