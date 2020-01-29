/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 04:41:11 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/29 21:38:21 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H

#include "libft.h"
#include "signal.h"
#include "sys/wait.h"
#include "sys/types.h"
#include "sys/stat.h"

typedef struct		s_lst
{
	char			*data;
	struct s_lst	*next;
}					t_lst;

typedef struct stat t_stat;

pid_t				kill_pid;

t_lst				*new_lst(char *content);
t_lst				*cnvrt_to_lst(char **array);
t_lst				*env_com(char *av, t_lst *list);
t_lst				*change_pwd(char *var, t_lst *list);
t_lst				*cd_check(char **argv, t_lst *list);
t_lst				*setenv_check(char **argv, t_lst *list);
t_lst				*find_env(t_lst *list, char *name);
t_lst				*ft_setenv(t_lst *list, char *name, char *str);
t_lst				*ft_unsetenv(t_lst *list, char *name);
char				*find_var(t_lst *head, char *find);
char				*path_to_bin(char **path, char *com);
char				*join_lst_to_path(t_lst *list);
char				**cnvrt_to_arr(t_lst *list);
char				*join_three(char *fr, char *sc, char *th);
char				*insert_var(char *str, t_lst *list);
char				*del_spaces(char *str);
void				print_env(t_lst *list);
void				to_end(t_lst **head, t_lst *nw);
void				lst_del(t_lst *head);
void				lst_del_last(t_lst **head);
void				del_double_arr(char **arr);
int					check_exist(char **path, char *com);
int					count_list(t_lst *list);
int					count_arr(char **arr);
int					check_path(char *str);

#endif
