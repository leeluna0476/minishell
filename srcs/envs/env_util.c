/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:00:13 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/01 17:31:03 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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

t_env	*find_env(char *name, t_env_pack *package)
{
	t_env	*temp;

	temp = package->sorted_head;
	while (temp && (ft_strcmp(temp->name, name)))
		temp = temp->sorted_next;
	return (temp);
}
// package의 node를 순회하며 매개변수 name과 매칭되는 node를 찾아 리턴해준다

void	delete_env(char *name, t_env_pack *package)
{
	t_env	*target;
	t_env	*prev;

	target = find_env(name, package);
	if (!target)
		return ;
	prev = target->origin_prev;
	if (prev)
		prev->origin_next = target->origin_next;
	else
		package->origin_head = target->origin_next;
	if (target->origin_next)
		target->origin_next->origin_prev = prev;
	if (!target->origin_next)
		package->origin_last = target->origin_prev;
	prev = target->sorted_prev;
	if (prev)
		prev->sorted_next = target->sorted_next;
	else
		package->sorted_head = target->sorted_next;
	if (target->sorted_next)
		target->sorted_next->sorted_prev = prev;
	free(target->name);
	free(target->value);
	free(target);
}
// unset에 사용될 함수, name값을 key값으로 가지는 node를 찾고 적절히 연결 후 free하는 함수이다..
