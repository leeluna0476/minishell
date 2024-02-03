/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env_pack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:46:43 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/02 16:02:33 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	build_envp(t_env_pack *pack, char **envp)
{
	int		idx;
	char	*temp;

	pack->origin_head = 0;
	pack->envp = 0;
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
			return ;
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
