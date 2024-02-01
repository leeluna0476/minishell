/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:56:56 by seojilee          #+#    #+#             */
/*   Updated: 2023/10/17 13:44:19 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*curr_node;

	if (!lst || !f)
		return ;
	curr_node = lst;
	while (curr_node)
	{
		(*f)(curr_node->content);
		curr_node = curr_node->next;
	}
}
