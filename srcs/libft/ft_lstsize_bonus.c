/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:27:55 by seojilee          #+#    #+#             */
/*   Updated: 2023/10/17 13:45:43 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*curr;
	t_list	*next;
	int		len;

	len = 0;
	curr = lst;
	while (curr)
	{
		next = curr->next;
		curr = next;
		len++;
	}
	return (len);
}
