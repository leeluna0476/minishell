/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:10:45 by yusekim           #+#    #+#             */
/*   Updated: 2024/03/04 18:55:16 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler_bonus.h"
#include "redirection_bonus.h"
#include "expand_bonus.h"
#include "env_bonus.h"

void	set_term(struct termios *term)
{
	tcgetattr(STDIN_FILENO, term);
	term->c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}

void	reset_term(struct termios *term)
{
	term->c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}

char	*get_filename(void)
{
	char	*path;
	char	*itoa_out;
	char	*temp_filepath;
	int		num;

	path = getcwd(0, 0);
	temp_filepath = ft_strjoin(path, TEMP_FILENAME);
	free(path);
	path = ft_strdup(temp_filepath);
	num = -1;
	while (!access(path, F_OK))
	{
		free(path);
		itoa_out = ft_itoa(++num);
		path = ft_strjoin(temp_filepath, itoa_out);
		free(itoa_out);
	}
	free(temp_filepath);
	return (path);
}

char	*get_heredoc_expval(char *ptr, t_env_pack *pack, int *i)
{
	char	*env_name;
	t_env	*target;

	if (strlen(ptr) == 1 || is_space(*(ptr + 1)))
		return (ft_substr(ptr, 0, 1));
	env_name = find_env_name(ptr);
	*i += ft_strlen(env_name) - 1;
	target = find_env(env_name, pack);
	free(env_name);
	if (!target)
		return (NULL);
	else
		return (ft_strdup(target->value));
}
