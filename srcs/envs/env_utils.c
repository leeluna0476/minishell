/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:00:13 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/10 16:53:35 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env	*find_env(char *name, t_env_pack *package)
{
	t_env	*temp;

	if (*name == '$')
		name++;
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

void	free_envs(t_env *head)
{
	t_env	*temp;
	t_env	*next;

	temp = head;
	while (temp)
	{
		next = temp->origin_next;
		free(temp->name);
		free(temp->value);
		free(temp);
		temp = next;
	}
}
