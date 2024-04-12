/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:14:38 by yusekim           #+#    #+#             */
/*   Updated: 2024/03/04 18:51:17 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "structures_bonus.h"

// utils.c
char	**add_str(char **str, char *add);
void	split_free(char **split);
int		split_len(char **split);
char	**merge_strs(char **orig, char **new_strs);
void	ft_assert(int expression, const char *arg, int exit_num);

// utils2.c
void	set_exit(t_env_pack *pack, int code);
void	ft_perror(const char *str, int exit_num);

#endif
