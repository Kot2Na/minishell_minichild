/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 19:57:55 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/31 00:12:05 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	run_exe(char *path, char **argv, t_lst *list)
{
	pid_t	pid;
	char	**env;
	int		status;
	int		i;

	env = cnvrt_to_arr(list);
	pid = fork();
	kill_pid = pid;
	if (pid == 0)
	{
		execve(path, argv, env);
		exit(0);
	}
	waitpid(pid, &status, 0);
	del_double_arr(env);
}

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
	else
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

int		check_quote(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

void	change_flag(int *flag)
{
	if (flag)
	{
		if (*flag)
			*flag = 0;
		else
			*flag = 1;
	}
}

char	*del_quotes(char *str)
{
	char	*copy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	copy = ft_strnew(ft_strlen(str));
	while (str[i])
	{
		while (str[i] == '"')
			i++;
		copy[j] = str[i];
		j++;
		i++;
	}
	return (copy);
}

void	add_to_list(char *str, int i, t_lst **list)
{
	char	*line;
	char	*save;

	if (list)
	{
		line = ft_strnew(i + 1);
		line = ft_strncpy(line, str, i);
		if (check_quote(line))
		{
			save = line;
			line = del_quotes(line);
			free(save);
		}
		to_end(list, new_lst(line));
		free(line);
	}
}

char	**prep_argv(char *str)
{
	t_lst	*argv;
	char	**result;
	int		i;
	int		flag;

	i = 0;
	argv = NULL;
	flag = 1;
	while (str[i])
	{
		if (str[i] && str[i] == ' ' && flag)
		{
			add_to_list(str, i, &argv);
			str += i + 1;
			i = 0;
		}
		if (str[i] == '"')
			change_flag(&flag);
		i++;
	}
	add_to_list(str, i, &argv);
	result = cnvrt_to_arr(argv);
	lst_del(argv);
	return (result);
}

t_lst	*env_com(char *av, t_lst *list)
{
	char	**path;
	char	**argv;
	int		i;

	path = ft_strsplit(find_var(list, "PATH"), ':');
	argv = prep_argv(av);
	if (argv[0])
	{
		if (!check_path(argv[0]))
		{
			if (ft_strcmp(argv[0], "cd") == 0)
				list = cd_check(argv, list);
			else if (ft_strcmp(argv[0], "setenv") == 0 || \
						ft_strcmp(argv[0], "unsetenv") == 0)
				list = setenv_check(argv, list);
			else
				run_command(argv, path, list);
		}
		else
			list = to_file_or_dir(argv, path, list);
	}
	del_double_arr(path);
	del_double_arr(argv);
	return (list);
}
