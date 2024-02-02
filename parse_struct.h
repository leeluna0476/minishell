#ifndef PARSE_STRUCT_H
# define PARSE_STRUCT_H

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
	T_CLOSE_BRACKET		// 논리 연산 괄호 닫힘 ')'
};

// lexer: metacharacter를 기준으로 line을 분할.
struct s_token
{
	char			*string;
	enum e_type		type;
	struct s_token	*prev;
	struct s_token	*next;
};


typedef struct s_token t_token;
typedef enum e_characters t_chars;
typedef enum e_type		t_type;

#endif
