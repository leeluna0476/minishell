/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env_pack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:46:43 by yusekim           #+#    #+#             */
/*   Updated: 2024/04/16 10:38:31 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	set_shlvl(t_env_pack *pack)
{
	t_env	*shlvl_node;
	char	*shlvl_str;

	shlvl_node = find_env("SHLVL", pack);
	if (!shlvl_node)
		return (add_env_node(pack, "SHLVL", "1"));
	shlvl_str = ft_itoa(ft_atoi(shlvl_node->value) + 1);
	add_env_node(pack, "SHLVL", shlvl_str);
	free(shlvl_str);
	return ;
}

void	set_tilde(t_env_pack *pack)
{
	t_env	*home;
	char	*tilde_value;

	home = find_env("HOME", pack);
	if (home)
		tilde_value = ft_strdup(home->value);
	else
		tilde_value = get_home_dir();
	add_env_node(pack, "~", tilde_value);
	free(tilde_value);
}

void	build_envp(t_env_pack *pack, char **envp)
{
	char	*temp;
	int		idx;

	idx = 0;
	if (!*envp)
	{
		ft_putendl_fd("미니쉘: envp not set", STDERR_FILENO);
		exit(1);
	}
	ft_memset(pack, 0, sizeof(t_env_pack));
	add_env_node(pack, "?", "0");
	add_env_node(pack, "~", NULL);
	while (envp[idx])
	{
		temp = ft_strchr(envp[idx], '=');
		*temp = 0;
		add_env_node(pack, envp[idx], temp + 1);
		*temp = '=';
		idx++;
	}
	set_shlvl(pack);
	set_tilde(pack);
	return ;
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
