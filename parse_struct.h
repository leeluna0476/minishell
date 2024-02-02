#ifndef PARSE_STRUCT_H
# define PARSE_STRUCT_H

// lexer: metacharacter를 기준으로 line을 분할.
struct s_token
{
	char			*string;
	enum e_type		type;
	struct s_token	*prev;
	struct s_token	*next;
};

// tokenizer: string에 type 부여.
// parser: tokenize 된 데이터를 가지고 구문 분석 후 AST script 형식으로 정렬.
//struct s_token
//{
//	char			*string;
//	enum e_type		type;
//	struct s_token	*next;
//};

//# define GREATER 60,
//# define LESSER 62,
//# define AND 38,
//# define OR 124,
//# define SEMICOLON 59,
//# define PARENTHESIS1 40,
//# define PARENTHESIS2 41,
//# define DOUBLE_QUOTE 34,
//# define QUOTE 39

typedef struct s_token t_token;
typedef enum e_characters t_chars;

#endif
