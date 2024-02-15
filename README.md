# minishell
seojilee &amp;&amp; yusekim's minishell

## Tokenizer
```
enum	e_type
{
	T_ERROR = -1,		// 기본값 (syntax check때의 초깃값)
	T_WORD,			// 문자
	T_SPACE,		// 공백문자(보통 space)
	T_PIPE,			// Pipe문자 '|'
	T_LESSER,		// 리다이렉션 '<'
	T_GREATER,		// 리다이렉션 '>'
	T_D_LESSER,		// 리다이렉션 Here_doc "<<"
	T_D_GREATER,		// 리다이렉션 append ">>"
	T_AND,			// 논리 연산 AND "&&"
	T_OR,			// 논리 연산 OR "||"
	T_OPEN_BRACKET,		// 논리 연산 괄호 열림 '('
	T_CLOSE_BRACKET,	// 논리 연산 괄호 닫힘 ')'
	T_NEWLINE		// 개행. 실제로 사용은 안 되지만 metacharacters에 포함되기 때문에 포함시켰다.
};

struct s_token
{
	char	*string;
	enum	e_type	type;
	struct	s_token	*prev;
	struct	s_token	*next;
};
```
**Token**: A sequence of characters considered a single unit by the shell. It is either a word or an operator.
**토큰**: 쉘에 의해 단일 단위로 간주되는 일련의 문자. 그것은 단어이거나 연산자이다.
- 따옴표 규칙을 지키면서 metacharacters를 기준으로 line을 토큰으로 분할.
  - `| & ; ( ) < > (space) (newline)`
- 분할 규칙:
  - `< > & | ; (space) (newline)` -> space는 무시.
    - 연달아 들어오면 두개까지 하나로 묶는다.
  - `( ) " '`
    - 짝을 찾음.
	- `( )`는 안에서 다시 분할한다.
	  - 짝이 맞는지는 파서에서 확인.
	- `"", ''`는 안에서 분할하지 않는다.
	  - 따옴표 짝이 맞는지 확인.
	  - 따옴표 안에 있는 문자들은 메타문자일지라도 일반 문자로 취급한다.
	  - `$, *` 등의 확장은 파싱이 끝난 후 실행부에서 처리한다.
	  - 따옴표 제거는 파싱이 끝난 후 실행부에서 처리한다.
- 분할하면서 type 부여.

## Parser
```
struct s_ast
{
	enum e_type	type;
	t_token		*start;
	t_token		*end;
	char		*error;
	struct s_ast	*left;
	struct s_ast	*right;
};
```
- Tokenizer가 형성한 튜플형 리스트가 문법에 맞는지 확인하면서 AST 형성.
- 문법 검사를 통과하면 완성된 AST를 반환, 통과하지 못하면 AST의 루트 노드만 남기고 반환, error string 표시.

- **center**(가지 분할 기준 토큰):
  -  `&&, ||, |` 를 기준으로 가지를 나눈다.
  -  쉘 명령어들은 병렬적으로 실행되어야 하기 때문에 토큰 리스트를 뒤에서부터 가지를 나눈다.
    - 깊이우선탐색으로 트리의 왼쪽 부분부터 실행
  -  우선 `&&, ||` 논리 연산자를 기준으로 가지를 나눈다.
  -  논리 연산자가 없다면 `|` 파이프를 기준으로 가지를 나눈다.
  -  논리 연산자, 파이프 둘 다 없다면 하나의 simple command로 유지한다.
  -  괄호가 있다면 괄호 바깥쪽에 있는 기준 문자를 먼저 확인한다.
    - 분할이 끝나고 노드에 토큰을 추가할 때, 가장 바깥에서 토큰들을 감싸고 있는 한 쌍의 괄호가 있다면 더 이상 필요하지 않으므로 건너뛴다.

- **type**(노드의 타입):
  - center로 분할이 되는 시점에서는 center의 타입이 노드의 타입이 된다.
  - 더 이상 분할이 되지 않는다면 start 토큰의 타입이 노드의 타입이 된다.

### 참고 자료
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
