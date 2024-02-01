enum	e_exp
{
// ...	
} t_exp;

enum	e_type
{
// ...	
} t_type;

enum	e_operator
{
// ...	
} t_operator;

typedef struct s_exp
{
	e_type	type;
	char	*value;
	e_exp	kind; // 어떤 확장인지.
	int		loc[2]; // 어디부터 어디까지 확장해야 하는지.
} s_exp;

typedef struct s_word
{
	e_type		type;
	char		*value;
	t_exp		*exp;
} t_word;

typedef struct s_io
{
	int	fd_from;
	int	fd_to;
} t_io;

typedef struct	s_redirect
{
	e_type	type;
	char	*value;
	e_type	operator;
	t_word	*file;
	t_io	*io;
}

typedef struct s_fix
{
	e_type		type;
	char		*value;
	t_word		*word;
	t_redirect	*redirect;
} t_fix;

typedef struct s_command
{
	e_type		type;
	char		*value;
	t_word		*name;
	t_fix		*prefix;
	t_fix		*suffix;
} t_command;

typedef struct s_pipeline
{
	e_type		type;
	char		*value;
	t_command	*cmd;
	struct s_pipeline	*pipeline;
} t_pipeline;

// &&, || 등의 서브 스크립트 구분.
typedef struct s_logical_expression
{
	e_type		type;
	char		*value;
	e_operator	operator;
	t_script	*left;
	t_script	*right;
} t_logical_expression;

// lexer에서 정리해준 순서를 보고 판단.
// 우선순위:
	// 1. logical expression
	// 2. pipeline
	// 3. command
typedef struct s_script
{
	e_type				type;
	char				*value;
	t_logical_expression *log_exp;
	t_pipeline			*pipeline;
	t_command			*cmd;
} t_script;
