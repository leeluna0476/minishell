#ifndef PARSE_STRUCT_H
# define PARSE_STRUCT_H

#include <stdio.h>
#include "../libft/libft.h"

typedef enum e_type			t_type;
typedef struct s_token		t_token;

enum	e_type
{
	T_ERROR = -1,		// 기본값 (syntax check때의 초깃값)
	T_WORD,				// 문자
	T_SPACE,			// 공백문자(보통 space)
	T_PIPE,				// Pipe문자 '|'
	T_LESSER,			// 리다이렉션 '<'
	T_GREATER,			// 리다이렉션 '>'
	T_D_LESSER,			// 리다이렉션 Here_doc "<<"
	T_D_GREATER,		// 리다이렉션 append ">>"
	T_AND,				// 논리 연산 AND "&&"
	T_OR,				// 논리 연산 OR "||"
	T_OPEN_BRACKET,		// 논리 연산 괄호 열림 '('
	T_CLOSE_BRACKET,	// 논리 연산 괄호 닫힘 ')'
	T_NEWLINE,
	T_CMD
};

// tokenizer: metacharacter를 기준으로 line을 분할하고 type key를 부여.
struct s_token
{
	char			*string;
	enum	e_type	type;
	struct	s_token	*prev;
	struct	s_token	*next;
};

// token_utils
t_token	*new_token(char *string, t_type type);
t_token	*last_token(t_token *list);
void	add_token(t_token **list, t_token *token);
void	free_token(t_token **token);
void	free_tokens(t_token **tokens);
void	syntax_error_tokenizer(char *string, t_token **list);

// meta
int		is_meta1(char c);
int		is_meta2(char c);
void	set_type_meta1(char c, int i, t_type *type);
int		get_meta1(char *line, char **string, t_type *type);
int		get_meta2(char *line, char **string, t_type *type);

// tokenizer
int	is_space(char c);
t_type	get_type(char *string, int i);
int	remove_space(char *line);
int	get_word(char *line, char **string, t_type *type);
t_token	*tokenizer(char *line);

#endif
