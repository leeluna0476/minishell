/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:32:55 by yusekim           #+#    #+#             */
/*   Updated: 2024/03/04 18:50:04 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_BONUS_H
# define REDIRECTION_BONUS_H

# include "structures_bonus.h"
# include "utils_bonus.h"
# define TEMP_FILENAME "/_bonus.heredoc_tmp"
# define HEREDOC "여기문서> "

// redirections.c
void	append_redir(t_cmd **cmd, t_type type, char **fileinfo);
int		scan_n_set_redirs(t_cmd *cmd, t_env_pack *pack);
int		open_check(t_redir *temp, int *exit_code);

// do_heredoc.c
int		heredoc(t_redir *target, t_env_pack *pack, char *filename);
char	*get_filename(void);
void	do_heredoc(t_redir *temp, char *f_name, t_env_pack *pack);
void	write_heredoc(t_redir *redir, t_env_pack *pack, int inf_fd);
void	heredoc_expander(int fd, char *input, t_env_pack *pack, int flag);

// redir_utils.c
void	redir_open(t_redir *temp);
char	*trim_quotes(char *data);
int		heredoc_q_flag(char *str);

// heredoc_utils.c
void	set_term(struct termios *term);
void	reset_term(struct termios *term);
char	*get_filename(void);
char	*get_heredoc_expval(char *ptr, t_env_pack *pack, int *i);

#endif
