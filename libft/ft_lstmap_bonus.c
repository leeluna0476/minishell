/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:03:17 by seojilee          #+#    #+#             */
/*   Updated: 2023/10/26 07:45:03 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*curr_lst;
	t_list	*curr_new;
	void	*tmp_content;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	curr_lst = lst;
	while (curr_lst)
	{
		tmp_content = (*f)(curr_lst->content);
		curr_new = ft_lstnew(tmp_content);
		if (!curr_new)
		{
			(*del)(tmp_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, curr_new);
		curr_lst = curr_lst->next;
	}
	return (new_list);
}
