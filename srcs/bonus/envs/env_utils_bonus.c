/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:00:13 by yusekim           #+#    #+#             */
/*   Updated: 2024/03/04 16:13:14 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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

t_env	*find_env(char *name, t_env_pack *package)
{
	t_env	*temp;

	if (*name == '$')
	{
		name++;
		if (*name == '~')
			return (NULL);
	}
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

char	*get_home_dir(void)
{
	char	*curr_dir;
	char	*home_dir;
	int		flag;
	int		i;

	curr_dir = getcwd(NULL, 0);
	home_dir = curr_dir;
	if (!curr_dir)
		return (NULL);
	i = 0;
	flag = 1;
	while (curr_dir[i] && flag < 3)
	{
		i++;
		if (curr_dir[i] == '/')
			flag++;
	}
	home_dir = ft_substr(curr_dir, 0, i);
	free(curr_dir);
	return (home_dir);
}
