/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:32:55 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/20 00:10:49 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H
# include "exec_structures.h"
# include "utils.h"
# define TEMP_FILENAME "/Users/yusekim/goinfre/heredoc_tmp"

// redirections.c
void	append_redir(t_cmd **cmd, t_type type, char **fileinfo);
int		scan_n_set_redirs(t_cmd *cmd, t_env_pack *pack);
int		open_check(t_redir *temp);

// do_heredoc.c
int		heredoc(t_redir *target, t_env_pack *pack);
int		do_heredoc(t_redir *temp, char *f_name, t_env_pack *pack);
void	write_heredoc(t_redir *redir, t_env_pack *pack, int inf_fd);
void	heredoc_expander(int fd, char *input, t_env_pack *pack, int flag);

// redir_utils.c
void	redir_open(t_redir *temp);
char	*trim_quotes(char *data);
int		heredoc_q_flag(char *str);
int		detact_exitcode(int temp);
char	*itoa(int n);
#endif
