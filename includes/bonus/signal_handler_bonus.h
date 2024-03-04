/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 02:22:10 by seojilee          #+#    #+#             */
/*   Updated: 2024/03/04 18:51:57 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_BONUS_H
# define SIGNAL_HANDLER_BONUS_H

# include <signal.h>
# include "structures_bonus.h"

void	sig_handler(int signo);
void	signal_readline(void);
void	signal_ign(void);
void	signal_dfl(void);
char	*get_line(char *prompt, t_env_pack *pack);

#endif
