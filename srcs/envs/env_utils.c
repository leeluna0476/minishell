/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:00:13 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/02 16:02:34 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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

void	set_new_env(t_env_pack *pack, t_env *new)
{
	new->origin_next = 0;
	new->sorted_next = 0;
	new->origin_prev = 0;
	new->sorted_prev = 0;
	if (!(pack->origin_head))
	{
		pack->origin_head = new;
		pack->origin_last = new;
		pack->sorted_head = new;
	}
	else
	{
		new->origin_prev = pack->origin_last;
		pack->origin_last->origin_next = new;
		pack->origin_last = new;
		add_sorted_node(&(pack->sorted_head), new);
	}
}
// new를 초기화하고 t_env_pack을 검사하며 orgin_next/prev를 연결하는 함수

void	add_sorted_node(t_env **sorted_head, t_env *new)
{
	t_env	*temp;
	t_env	*temp_next;

	temp = *sorted_head;
	if (ft_strcmp(new->name, temp->name) < 0)
	{
		*sorted_head = new;
		new->sorted_next = temp;
		temp->sorted_prev = new;
		return ;
	}
	while (temp->sorted_next && \
	ft_strcmp(new->name, temp->sorted_next->name) > 0)
		temp = temp->sorted_next;
	temp_next = temp->sorted_next;
	temp->sorted_next = new;
	if (temp_next)
		temp_next->sorted_prev = new;
	new->sorted_prev = temp;
	new->sorted_next = temp_next;
}
// new노드의 sort_next/prev를 적절히 연결하는 함수
