/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:32:55 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/13 14:58:16 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H
# include "structures.h"
# include "utils.h"
# define TEMP_FILENAME "/Users/yusekim/goinfre/heredoc_tmp"

// open_redirs.c
void	append_redir(t_cmd_pack *cmd, t_type type, char **fileinfo);
int		scan_n_set_redirs(t_cmd_pack *cmd, t_env_pack *pack);
int		open_check(t_redir *temp);

// do_heredoc.c
int		heredoc(t_redir *target, t_env_pack *pack);
int		do_heredoc(t_redir *temp, char *f_name, t_env_pack *pack);
void	write_heredoc(t_redir *redir, t_env_pack *pack, int inf_fd);
void	heredoc_expander(int fd, char *input, t_env_pack *pack, int flag);

// redir_utils.c
void	redir_open(t_redir *temp);
char	*trim_quotes(char *data);

#endif
