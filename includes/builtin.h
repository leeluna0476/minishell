/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:38:38 by yusekim           #+#    #+#             */
<<<<<<< HEAD:includes/builtin.h
/*   Updated: 2024/02/22 18:05:49 by seojilee         ###   ########.fr       */
=======
/*   Updated: 2024/02/23 13:00:59 by yusekim          ###   ########.fr       */
>>>>>>> yusekim_test:Includes/builtin.h
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "exec_structures.h"
# include "utils.h"
# include "env.h"

typedef int	(*t_builtin_ptr)(char **, t_env_pack *);

// builtin_exec.c
int				exec_builtin(char **args, t_env_pack *pack);
enum e_b_type	check_is_builtin(char *arg);
int				solo_builtin(t_cmd *cur, t_env_pack *pack);
void			b_check_redir(t_cmd *cur, int *std_fd, int *in_fd, int *out_fd);

// builtin_utils.c
<<<<<<< HEAD:includes/builtin.h
int				print_export(t_env_pack *pack);
int				check_env_name(char **args, int i);
=======
int				check_env_name(char *name);
>>>>>>> yusekim_test:Includes/builtin.h
int				check_res(int res, t_env_pack *pack, char *path, char **args);
int				check_sign(char *str);
void			builtin_fd_set(int *in_fd, int *out_fd, int *std_fd);

// do_builtin.c
int				do_echo(char **args, t_env_pack *pack);
int				do_cd(char **args, t_env_pack *pack);
int				do_pwd(char **args, t_env_pack *pack);
int				do_exit(char **args, t_env_pack *pack);
void			b_exit(int code);

// do_builtin2.c
void			ft_exit(uint8_t code);
int				do_export(char **args, t_env_pack *pack);
int				print_export(t_env_pack *pack);
void			check_n_add(t_env_pack *pack, char *arg, char *ptr, int *res);
int				do_unset(char **args, t_env_pack *pack);
int				do_env(char **args, t_env_pack *pack);
<<<<<<< HEAD:includes/builtin.h
int				do_exit(char **args, t_env_pack *pack);
void			b_exit(int code);
=======
>>>>>>> yusekim_test:Includes/builtin.h

#endif
