/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:06:36 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/20 13:41:08 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_STRUCT_H
# define PARSE_STRUCT_H

# include "exec_structures.h"

//// tokenizer: metacharacter를 기준으로 line을 분할하고 type key를 부여.
//struct s_token
//{
//	char			*string;
//	enum e_type		type;
//	struct s_token	*prev;
//	struct s_token	*next;
//};
//
//struct s_ast
//{
//	enum e_type		type;
//	t_token			*start;
//	t_token			*end;
//	char			*error;
//	struct s_ast	*left;
//	struct s_ast	*right;
//};

struct s_mark
{
	int	start;
	int	end;
};

#endif
