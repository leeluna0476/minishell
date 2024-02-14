/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:42:17 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/14 11:14:07 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/structures.h"
#include "../../Includes/utils.h"

void	split_free(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}


int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

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
// 이중 캐릭터 배열에 새 문자열을 넣어주는 함수
// 예를 들어 str[0] = "ls", str[1] = "-l", str[2] = NULL 이고 add = "-a" 일 때
// 재할당과 해제를 통해 new를 리턴한다
// 이때 new[0] = "ls", new[1] = "-l", new[2] = "-a", new[3] = NULL

char	**merge_strs(char **orig, char **new_strs)
{
	int		orig_len;
	int		new_len;
	int		idx;
	char	**out;

	if (!orig)
		return (new_strs);
	if (!new_strs)
		return (orig);
	orig_len = split_len(orig);
	new_len = split_len(new_strs);
	out = malloc(sizeof(char *) * (orig_len + new_len + 1));
	if (!out)
		exit(1);
	idx = -1;
	while (++idx < orig_len)
		out[idx] = orig[idx];
	idx = -1;
	while (++idx < new_len)
		out[idx + orig_len] = new_strs[idx];
	free(orig);
	free(new_strs);
	return (out);
}

char	*itoa(int n)
{
	int		size;
	int		temp;
	char	*out;

	if (n == 0)
		return (ft_strdup("0"));
	size = 0;
	temp = n;
	while (temp)
	{
		temp /= 10;
		size++;
	}
	out = malloc(sizeof(char) * (size + 1));
	if (!out)
		exit(1);
	out[size] = '\0';
	while (n)
	{
		out[--size] = (n % 10) + '0';
		n /= 10;
	}
	return (out);
}
