// lexer: metacharacter를 기준으로 line을 분할.
struct s_piece
{
	char			*string;
	struct s_piece	*next;
};

// tokenizer: string에 type 부여.
// parser: tokenize 된 데이터를 가지고 구문 분석 후 AST script 형식으로 정렬.
struct s_token
{
	char			*string;
	enum e_type		type;
	struct s_token	*prev;
	struct s_token	*next;
};
