/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 04:41:11 by crycherd          #+#    #+#             */
/*   Updated: 2020/01/31 21:25:04 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H

#include "libft.h"
#include "signal.h"
#include "sys/wait.h"
#include "sys/types.h"
#include "sys/stat.h"

#define BUFSIZE 255

typedef struct		s_lst
{
	char			*data;
	struct s_lst	*next;
}					t_lst;

typedef struct stat t_stat;

pid_t				kill_pid;

t_lst				*ft_unsetenv(t_lst *list, char *name);
t_lst				*find_env(t_lst *list, char *name);
t_lst				*setenv_check(char **argv, t_lst *list);
t_lst				*ft_setenv(t_lst *list, char *name, char *str);
t_lst				*cnvrt_to_lst(char **array);
t_lst				*new_lst(char *content);
t_lst				*env_com(char *av, t_lst *list);
t_lst				*change_pwd(char *pwd, t_lst *list);
t_lst				*check_pwd(char *pwd, t_lst *list, char *comm);
t_lst				*cd_check(char **argv, t_lst *list);
void				change_flag(int *flag);
void				print_env(t_lst *list);
void				print_error(char *name, char *text, char *com);
void				print_echo(char **argv);
void				lst_del_last(t_lst **head);
void				lst_del(t_lst *head);
void				to_end(t_lst **head, t_lst *new);
void				del_double_arr(char **arr);
void				run_exe(char *path, char **argv, t_lst *list);
void				add_to_list(char *str, int i, t_lst **list, int k);
char				**split_wquote(char *str, char c, int k);
char				*join_three(char *fr, char *sc, char *th);
char				*del_quotes(char *str);
char				*del_spaces(char *str);
char				**cnvrt_to_arr(t_lst *list);
char				*find_var(t_lst *head, char *find);
char				*insert_var(char *str, t_lst *list);
char				*join_lst_to_path(t_lst *list);
char				*path_to_bin(char **path, char *com);
char				*prepare_to_change(char *argv, t_lst *list);
int					count_arr(char **arr);
int					count_list(t_lst *list);
int					check_str(char *str);
int					check_path(char *str);
int					check_parse(char *str, char c);
int					check_quote(char *str);
int					check_exist(char **path, char *com);


#endif
