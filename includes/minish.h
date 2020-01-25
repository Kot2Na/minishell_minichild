/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 04:41:11 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/25 23:30:04 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H

#include "libft.h"
#include "sys/wait.h"
#include "sys/types.h"
#include "sys/stat.h"

typedef struct		s_lst
{
	char			*data;
	struct s_lst	*next;
}					t_lst;

typedef struct stat t_stat;

t_lst				*new_lst(char *content);
t_lst				*cnvrt_to_lst(char **array);
t_lst				*env_com(char *av, t_lst *list);
t_lst				*change_pwd(char **argv, t_lst *list);
char				*find_var(t_lst *head, char *find);
char				*path_to_bin(char **path, char *com);
char				*join_lst_to_path(t_lst *list);
char				**cnvrt_to_arr(t_lst *list);
char				*join_three(char *fr, char *sc, char *th);
void				to_end(t_lst **head, t_lst *nw);
void				lst_del(t_lst *head);
void				lst_del_last(t_lst **head);
void				del_double_arr(char **arr);
int					check_exist(char **path, char *com);
int					count_list(t_lst *list);
int					count_arr(char **arr);
int					check_path(char *str);

#endif
