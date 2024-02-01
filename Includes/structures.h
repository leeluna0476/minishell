/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:50:21 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/01 14:40:41 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

// 이 파일에는 미니셸 구조체들을 선언한다


enum	e_type
{
	T_ERROR = -1,
	T_WORD,
	T_SPACE,
	T_PIPE,
	T_LESSER,
	T_GREATER,
	T_D_LESSER,
	T_D_GREATER,
	T_AND,
	T_OR,
	T_OPEN_BRACKET,
	T_CLOSE_BRACKET
};

typedef struct s_token
{
	enum e_type		type;
	char			*data;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_tree
{
	enum e_type	this_type;
	void		*this_ptr;
	void		*left_ptr;
	void		*right_ptr;
}	t_tree;


#endif
