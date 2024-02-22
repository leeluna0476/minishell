/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_define.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:08:25 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/22 11:26:36 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_DEFINE_H
# define PARSE_DEFINE_H

# include "exec_structures.h"

//typedef enum e_type		t_type;
//typedef struct s_token	t_token;
//typedef struct s_mark	t_mark;
//typedef struct s_ast	t_ast;
//
//// 기본값 (syntax check때의 초깃값)
//// 문자
//// Pipe문자 '|'
//// 리다이렉션 '<'
//// 리다이렉션 '>'
//// 리다이렉션 Here_doc "<<"
//// 리다이렉션 append ">>"
//// 논리 연산 AND "&&"
//// 논리 연산 OR "||"
//// 논리 연산 괄호 열림 '('
//// 논리 연산 괄호 닫힘 ')'
//// 개행. 실제로 사용은 안 되지만 metacharacters에 포함되기 때문에 포함시켰다.
//enum	e_type
//{
//	T_ERROR = -1,
//	T_WORD,
//	T_PIPE,
//	T_LESSER,
//	T_GREATER,
//	T_D_LESSER,
//	T_D_GREATER,
//	T_AND,
//	T_OR,
//	T_OPEN_BRACKET,
//	T_CLOSE_BRACKET,
//	T_NEWLINE
//};

#endif
