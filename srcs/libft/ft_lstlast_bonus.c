/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:36:27 by seojilee          #+#    #+#             */
/*   Updated: 2023/10/13 22:45:29 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*curr_node;
	t_list	*next_node;

	if (!lst)
		return (NULL);
	curr_node = lst;
	while (curr_node->next)
	{
		next_node = curr_node->next;
		curr_node = next_node;
	}
	return (curr_node);
}
