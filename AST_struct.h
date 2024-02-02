#ifndef AST_STRUCT_H
# define AST_STRUCT_H

enum	e_exp
{
// ...	
} t_exp;

enum	t_type
{
// ...	
} t_type;

enum	e_operator
{
// ...	
} t_operator;

typedef struct s_exp
{
	t_type	type;
	char	*value;
	e_exp	kind; // 어떤 확장인지.
	int		loc[2]; // 어디부터 어디까지 확장해야 하는지.
} s_exp;

typedef struct s_word
{
	t_type		type;
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
	t_type	type;
	char	*value;
	t_type	operator;
	t_word	*file;
	t_io	*io;
}

typedef struct s_fix
{
	t_type		type;
	char		*value;
	t_word		*word;
	t_redirect	*redirect;
} t_fix;

typedef struct s_command
{
	t_type		type;
	char		*value;
	t_word		*name;
	t_fix		*prefix;
	t_fix		*suffix;
} t_command;

typedef struct s_pipeline
{
	t_type		type;
	char		*value;
	t_command	*cmd;
	struct s_pipeline	*pipeline;
} t_pipeline;

// &&, || 등의 서브 스크립트 구분.
typedef struct s_logical_expression
{
	t_type		type;
	char		*value;
	e_operator	operator;
	t_script	*left;
	t_script	*right;
} t_logical_expression;

// parser에서 정리해준 순서를 보고 판단.
// 우선순위:
	// 1. logical expression
	// 2. pipeline
	// 3. command
typedef struct s_script
{
	t_type				type;
	char				*value;
	t_logical_expression *log_exp;
	t_pipeline			*pipeline;
	t_command			*cmd;
} t_script;

// value는 현재는 char *로 표현되어 있지만 struct { "value":key } 형태로 갈 듯.

#endif
