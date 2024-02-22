/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:53:02 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/22 20:24:11 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include "tokenizer.h"
#include <unistd.h>

// 자세한 로직은 WILDCARD.md 참고.

// char *를 char **에 추가.
char	**add_str(char **str, char *add)
{
	char	**new;
	int		i;

	if (!add)
		return (str);
	i = 0;
	while (str && str[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		exit(1);
	i = 0;
	while (str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = add;
	i++;
	new[i] = 0;
	if (str)
		free(str);
	return (new);
}

// a*, *a* 등을 검사.
int	check_front_center(char *filename, char *pattern, t_mark *mark, int i)
{
	char	*substr;
	int		ret;

	ret = 1;
	if (pattern[i] == '*')
	{
		if (mark->start == 0 && i != 0)
		{
			mark->end = i - 1;
			if (ft_strncmp(filename, pattern, i))
				ret = 0;
			mark->start = i + 1;
		}
		else
		{
			mark->end = i - 1;
			substr = ft_substr(pattern, \
				mark->start, mark->end - mark->start + 1);
			if (!ft_strnstr(filename, substr, ft_strlen(filename)))
				ret = 0;
			free(substr);
			mark->start = i + 1;
		}
	}
	return (ret);
}

// *a 등을 검사.
int	check_end(char *filename, char *pattern, t_mark mark, int i)
{
	int		filename_len;
	int		remains;

	if (!mark.start && mark.end == (int)ft_strlen(pattern) - 1)
	{
		if (ft_strncmp(filename, &(pattern[mark.start]), ft_strlen(filename)))
			return (0);
	}
	else if (mark.start < i)
	{
		remains = ft_strlen(&(pattern[mark.start]));
		filename_len = ft_strlen(filename);
		if (ft_strncmp(&(filename[filename_len - remains]), \
			&(pattern[mark.start]), remains))
			return (0);
	}
	return (i);
}

// filename이 와일드카드 패턴에 맞는지 검사.
int	check_wildfixes(char *filename, __uint8_t type, char *pattern)
{
	t_mark	mark;
	int		i;

	i = 0;
	if (pattern[0] == '*')
		i = 1;
	mark.start = i;
	mark.end = ft_strlen(pattern) - 1;
	while (pattern[i] && pattern[i] != '/')
	{
		if (mark.start != i && !check_front_center(filename, pattern, &mark, i))
			return (0);
		i++;
	}
	if (pattern[i] == '/' && type != DT_DIR)
		return (0);
	return (check_end(filename, pattern, mark, i));
}

// 현재 디렉토리를 열어서 filename 확인. (., ..  제외)
// filename이 와일드카드 패턴에 맞는다면 확장된 매개변수 리스트에 추가.
char	**expand_wildcard(char *arg)
{
	DIR				*dp;
	struct dirent	*entry;
	char			**args;
	int				i;

	args = NULL;
	if (arg)
	{
		dp = opendir(".");
		entry = readdir(dp);
		entry = readdir(dp);
		entry = readdir(dp);
		while (entry)
		{
			if (!(entry->d_name[0] == '.' && arg[0] != '.'))
			{
				i = check_wildfixes(entry->d_name, entry->d_type, arg);
				if (i)
					args = add_str(args, ft_strjoin(entry->d_name, &(arg[i])));
			}
			entry = readdir(dp);
		}
		closedir(dp);
	}
	return (args);
}
