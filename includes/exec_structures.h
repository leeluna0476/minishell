/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:50:21 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/28 16:15:53 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_STRUCTURES_H
# define EXEC_STRUCTURES_H
# include "../srcs/libft/libft.h"
// 이 파일에는 미니셸 구조체들을 선언한다

typedef struct s_token		t_token;
typedef struct s_ast		t_ast;
typedef struct s_env		t_env;
typedef struct s_env_pack	t_env_pack;
typedef struct s_cmd_pack	t_cmd;
typedef struct s_redir		t_redir;
typedef struct s_expand		t_c_expand;		// 명령어 확장
typedef struct s_exp_pair	t_exp_pair;
typedef enum e_type			t_type;
typedef struct s_info		t_info;

int							g_exit_status;
// exit code(전역변수)

enum	e_type
{
	T_ERROR = -1,		// 기본값 (syntax check때의 초깃값)
	T_SPACE,			// 공백문자(보통 space)
	T_AND,				// 논리 연산 AND "&&"
	T_OR,				// 논리 연산 OR "||"
	T_PIPE,				// Pipe문자 '|'
	T_WORD,				// 문자
	T_LESSER,			// 리다이렉션 '<'
	T_GREATER,			// 리다이렉션 '>'
	T_D_LESSER,			// 리다이렉션 Here_doc "<<"
	T_D_GREATER,		// 리다이렉션 append ">>"
	T_OPEN_BRACKET,		// 논리 연산 괄호 열림 '('
	T_CLOSE_BRACKET,	// 논리 연산 괄호 닫힘 ')'
	T_NEWLINE
};
// 따옴표 같은 경우 같은 짝(ascii코드로 판별)이 나올때까지 값을 모두 WORD로 해야한다..
// 괄호는 일단 넣었는데, 짝이 안맞을 경우 따옴표와 똑같이 토큰 클리어를 해야하기 때문에 이 부분은 고민 필요

enum	e_b_type
{
	B_FALSE = -1,
	B_ECHO,
	B_CD,
	B_PWD,
	B_EXPORT,
	B_UNSET,
	B_ENV,
	B_EXIT
};

struct s_token
{
	enum e_type		type;		// 열거형 type
	char			*string;		// 해당 node의 data
	struct s_token	*next;		// 다음 node
	struct s_token	*prev;		// 이전 node (syntax error 체크때 유용했었음)
};

struct s_env				// 환경변수 연결리스트
{
	char			*name;			// 환경변수 Key값 ($USER=yusekim 에서 'USER' 부분)
	char			*value;			// 환경변수 Value값 ($USER=yusekim 에서 'yusekim' 부분)
	struct s_env	*origin_prev;	// envp 들어온 순서대로 prev node
	struct s_env	*origin_next;	// envp 들어온 순서대로 next node
	struct s_env	*sorted_prev;	// name 기준으로 정렬하였을때의 prev node
	struct s_env	*sorted_next;	// name 기준으로 정렬하였을때의 next node
};

struct s_env_pack
{
	char	**envp;			// 이중 캐릭터 포인터, 실행부에서 execve할때 넘겨줘야함, 만약 추가되거나 제거된 환경변수가 있으면 그걸 적용하기 위해 export/unset할때 알맞게 업데이트해야함
	t_env	*origin_head;	// envp 순서대로 받았을때의 head node
	t_env	*origin_last;	// envp 순서대로 받았을때의 last node, export 빌트인 시 여기 뒤에 추가한다.
	t_env	*sorted_head;	// 정렬된 순서의 envp head 노드
};
// 확장, 실행부에서 가지고다녀야하는 환경변수 통합 구조체

struct s_cmd_pack
{
	char		**c_args;		// builtin/systemcall, arguments/options를 담고 있는 캐릭터 이중 포인터
	t_redir		*all_redirs;	// 해당 커맨드 블럭(pipe로 구분됨)의 모든 리다이렉션을 기록한 연결리스트, 실행부로 들어올 때, 모든 cmd_pack 구조체의 리다이렉션을 훑고 파일들을 열어야한다
	t_redir		*in_redirs;		// 최종적으로 사용될 input redirection('<', "<<")
	t_redir		*out_redirs;	// 최종적으로 사용될 output redirection('>', ">>")
};
// 커맨드 포괄 구조체, AST의 가장 밑단이 될 것이기 때문에(fianl leftside branch) 포괄 구조체로 해도 문제없다고 판단된다(아직 보너스파트를 안봐서 모른걸수도..)
// all_redirs는 pipe('|'), AND("&&"), OR("||") 를 기준으로 나뉘어진 cmd 블럭에 있는 모든 리다이렉션의 연결리스트이다

struct s_redir
{
	enum e_type	type;			// 어떤 리다이렉션 타입인지 가르쳐준다
	char		**filename;		// 이중 포인터인 이유는 ambigious redirection 에러처리를 위함(확장 예외처리)
	int			fd;				// filename[1] 을 open했을때 반환받는 fd값, type == T_D_LESSER ("<<") 일 경우에는 filename[0]을 DELIMITER로 설정하고 heredoc을 실행한다.
	t_redir		*next;			// next node
};

struct s_expand
{
	char		*original;
	t_exp_pair	**exp_ptrs;		// original을 돌면서 찾은 '$' 위치들과
	int			exp_num;		// '$' 갯수(확장여부 상관없이)
	int			wild_num;		// 확장 전(original)의 wildcard 문자 갯수
	int			wild_flag;		// 확장 전(original)의 와일드카드에 적용된 따옴표 플래그
	char		**result;		// 확장을 완료한 최종 결과물
};

struct s_exp_pair
{
	char	q_flag;			// 따옴표 플래그
	char	*exp_name;		// 환경변수 이름!(나 좀 짱인듯)
	char	*exp_pos;		// 확장문자 위치
};

struct s_ast
{
	enum e_type		type;
	struct s_token	*start;
	struct s_token	*end;
	char			*error;
	struct s_ast	*left;
	struct s_ast	*right;
};

struct s_info
{
	int			depths;				// 현재 몇 번째 가지(재귀)에 있는지 확인용
	pid_t		last_pid;			// 가장 마지막에 fork()된 프로세스 id, exit code 확인용
	int			fork_num;			// 몇번 fork()되었는지 기록, wait해야할 프로세스의 개수를 알아야 함
	int			pipe_fds[2];			// pipe()의 결과물을 기록한다. 3개짜리 int배열이고 첫 두개는 pipe()의 결과물, 3번째칸에는 다중 파이프때의 이전에 사용한 파이프의 fd
	int			prev_fd;
	int			redir_fds[2];		// 리다이렉션 파이프, 기본값은 표준입출력 fd이고 만약 in_redir, out_redir이 있을때 해당 파일을 open할 때 리턴받은 fd값으로 바꿔준다
	int			exit_status;
};

#endif
