/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 02:22:10 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/23 20:49:47 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# include <signal.h>
# include "exec_structures.h"

void	sig_handler(int signo);
void	signal_readline(void);
void	signal_ign(void);
void	signal_dfl(void);
char	*get_line(char *prompt, t_env_pack *pack);

#endif
