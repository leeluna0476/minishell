/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env_pack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:46:43 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/14 11:11:06 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/env.h"

void	build_envp(t_env_pack *pack, char **envp)
{
	int		idx;
	char	*temp;

	ft_memset(pack, 0, sizeof(t_env_pack));
	idx = 0;
	while (envp[idx])
	{
		temp = ft_strchr(envp[idx], '=');
		*temp = 0;
		add_env_node(pack, envp[idx], temp + 1);
		*temp = '=';
		idx++;
	}
	idx = 0;
}
// 환경변수 패키지 구조체(t_env_pack)를 만드는 함수

void	add_env_node(t_env_pack *pack, char *name, char *value)
{
	t_env	*new;

	new = find_env(name, pack);
	if (new)
	{
		if (!value)
		{
			new->value = NULL;
			return ;
		}
		free(new->value);
		new->value = ft_strdup(value);
		return ;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		exit(1);
	new->name = ft_strdup(name);
	if (!new->name)
		exit(1);
	new->value = ft_strdup(value);
	set_new_env(pack, new);
}
// 환경변수 연결리스트 구조체(t_env)에 새로운 노드를 생성하는 함수
// value 값이 없이 export 빌트인이 실행될 때에도 리스트에 추가해야 하기 때문에 먼저 key값이 있는지 확인한다
// 키 값이 있으면(이미 노드가 존재) value를 처리하고, 없으면 새로 노드를 만들어준다.
// strdup으로 각 key와 value를 가져오고 set_new_env로 초기화랑 대응되는 노드로 연결해준다..

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
