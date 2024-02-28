# Minis"hell" 실행부 기록

뽀오나쓰 까지 진행되는 미니셸의 실행부 파트를 맡게 되었다..
일단 이전에 mandatory 파트 부분에서 써먹을 수 있는 부분은 다 긁어왔다(코드 재활용 최고~~).

### 환경변수 Environment variables
터미널에서 `env`를 치거나 인자없이 `export`를 치면 해당 터미널의 환경변수 목록이 나오는데 둘이 약간의 차이가 있다.
`env`는 정렬이 되지 않은 상태로 출력되고, `export`는 각 변수 앞에 `declare -x`가 붙고 정렬이 된 상태로 출력된다. 또 env는 name/value 두 값이 있어야지 출력이 되는데 export의 경우에는 name만 있는 환경변수의 경우에도 출력이 된다.
따라서 두 동작 모두 하나의 연결 리스트로 구현하기 위해 아래와 같이 `t_env` 구조체를 구성하였다.
```c
typedef struct s_env			// 환경변수 연결리스트
{
	char		*name;		// 환경변수 Key값 ($USER=yusekim 에서 'USER' 부분)
	char		*value;		// 환경변수 Value값 ($USER=yusekim 에서 'yusekim' 부분)
	struct s_env	*origin_prev;	// envp 들어온 순서대로 prev node
	struct s_env	*origin_next;	// envp 들어온 순서대로 next node
	struct s_env	*sorted_prev;	// name 기준으로 정렬하였을때의 prev node
	struct s_env	*sorted_next;	// name 기준으로 정렬하였을때의 next node
}	t_env;
```

또, `fork()`를 통해 만든 자식 프로세스에서 `execve()`를 진행할때, 빌트인 export와 unset으로 수정된 envp를 가져가야하기 때문에 위 구조체를 포함한 `t_env_pack` 구조체를 구성하였다.

```c

typedef struct s_env_pack
{
	char	**envp;		// 이중 캐릭터 포인터, 실행부에서 execve할때 넘겨줘야함, 만약 추가되거나 제거된
				// 환경변수가 있으면 그걸 적용하기 위해 export/unset할때 알맞게 업데이트해야함
	t_env	*origin_head;	// envp 순서대로 받았을때의 head node
	t_env	*origin_last;	// envp 순서대로 받았을때의 last node, export 빌트인 시 여기 뒤에 추가한다.
	t_env	*sorted_head;	// 정렬된 순서의 envp head 노드
}	t_env_pack;
```

### 확장, 따옴표, 와일드카드 처리 Expension, quoting and wildcards
*__확장, 따옴표, 와일드카드는 결과적으로 동시에 처리되어야 한다..__* 라고 과거의 유세킴은 생각했습니다.. 물론 동시에 해도 문제는 없죠! 하지만 코드가 굉~~~장히 더러워지고 로직도 난해하고 메모리 누수도 잡기 힘들고 norm까지 맞추려면 벌써부터 머리가 아찔해집니다! 하지만 미니셸 경력직 유세킴은 오랜 고찰 끝에 혁신적인 아이디어를 생각해내게 되는데!
```c
struct s_expand
{
	char		*original;	// 처리할 문자열의 원본
	t_exp_pair	**exp_ptrs;	// original을 돌면서 찾은 '$' 위치들과
	int		exp_num;	// '$' 갯수(확장여부 상관없이)
	char		**result;	// 확장을 완료한 최종 결과물
};

struct s_exp_pair
{
	char	q_flag;			// 따옴표 플래그
	char	*exp_name;		// 환경변수 이름
	char	*exp_pos;		// 확장문자 위치
};

```
위 두 구조체를 적절히 활용하여 `따옴표제거 -> 환경변수 확장 -> 와일드카드 확장`이라는 깔끔하게 처리가 가능하다!!
```c
char	**expand(char *data, t_env_pack *package, int flag)
{
	t_c_expand	expand;

	ft_memset(&expand, 0, sizeof(t_c_expand));
	scan_n_setup(&expand, data);
	// 구조체 셋업, 처리할 문자열을 순회해 $의 갯수만큼 t_exp_pair도 만들어준다.
	if (flag)
		expand.result = add_str(expand.result, ft_strdup(data));
	// flag가 켜질 경우에는 redirection 용 확장이라는 뜻, ambiguous 오류 처리를 위해 result[0] 에 원본 문자열을 넣어준다.
	// ambiguous 오류가 궁금하면 bash에서 다음과 같이 입력해보자
	// export a="a b c"
	// [리다이렉션 문자] $a`
	delete_quotes(&expand);
	// 문자열의 따옴표들을 제거한다.
	find_position(&expand);
	// 따옴표 제거한 문자열을 다시 돌며 '$'문자의 포인터를 t_exp_pair에 기록한다.
	do_expand(&expand, package);
	// t_exp_pair에 기록된 정보를 토대로 확장을 처리한다!!!!
	free_expand(&expand);
	return (expand.result);
}
```

### 빌트인 builtins
미니셸 과제에서는 총 7개의 내장 기능(built-in)을 구현하여야 한다. 두 번째 미니셸인 만큼, 더욱 깔@쌈하게 코드를 짜고 싶은 욕심이 있어 피신때 한번 쓰고 쳐다도 안본 함수 포인터 배열을 써보기로 했다
```c
int	exec_builtin(char **args, t_env_pack *pack)
{
	int		i;
	const t_builtin_ptr	f_ptr_list[] = \
	{do_echo, do_cd, do_pwd, do_export, do_unset, do_env, do_exit};

	i = check_is_builtin(*args);
	if (i == -1)
	{
		ft_printf("not a builtin\n");
		return (0);
	}
	else
		return (f_ptr_list[i](args, pack));
}
```

**- echo**
먼저 `-n` 옵션을 처리하고, 들어온 `arg` 순서대로 프린트해주면 된다.
**- cd**
`getcwd()`, `chdir()`을 활용하여 경로를 옮기고, 환경변수의 `PWD`와 `OLDPWD` 를 갱신한다.
**- pwd**
`getcwd()` 함수를 활용한다
**- export**
먼저 인자의 유무를 확인후(추가 인자가 없으면 환경변수 목록을 아스키 코드 순으로 정렬하여 출력) 먼저 유효한 환경변수 이름인지 확인하고, 환경변수 연결리스트 구조체에 갱신/추가한다.
**- unset**
유효한 환경변수 이름인지 확인하고, 환경변수 연결리스트 구조체에서 해당 노드가 있는지 확인 후 처리한다.
**- env**
먼저 `env` 단일 인자만 들어왔는지 확인 후(그렇지 않을시 에러처리) bash에 맞게 출력한다.
**- exit**
`exit`의 경우 추가 인자는 최대 하나만 받아야하고 숫자값(`atoi`로 변환가능한) 값이 들어와야 한다. 아닐 경우에는 적절한 오류메세지를 출력해준다. 그리고 종료코드를 적절한 값으로 갱신 후 `exit`을 해주면 된다.

### AST 순회 및 파이프/리다이렉션 executing, pipe, and redirection
과거에 진행했던 미니셸과 다르게, 트리 구조로 파싱이 되어 실행부로 넘겨지기 때문에, 재귀를 활용하여 들어온 인자들을 실행시켜주어야 한다.

파싱부에서 처리를 마친 문장은 트리 형식의 구조체로 실행부로 넘어온다.
```c
struct s_ast
{
	enum e_type	type;			// 현재 트리 노드의 타입
	struct s_token	*start;			// 현재 트리가 포함하고 있는 토큰의 시작 노드
	struct s_token	*end;			// 현재 트리가 포함하고 있는 토큰의 마지막 노드
	char		*error;			// 파싱부에서 문법 오류가 있을때 사용되는 에러 문자열(실행부에서는 사용하지 않는다)
	struct s_ast	*left;			// 왼쪽 트리 노드
	struct s_ast	*right;			// 오른쪽 트리 노드
};

struct s_token
{
	enum e_type		type;		// 열거형 type
	char			*string;	// 해당 node의 data
	struct s_token	*next;			// 다음 node
	struct s_token	*prev;			// 이전 node (syntax error 체크)
};
```

실행은 재귀적으로 돌아간다. 현재 노드의 타입이 트리일 경우, 파이프 실행 함수로, 논리 연산자일 경우 논리 연산을 처리해주는 함수로, 단순 명령어 실행의 경우에는 실행해주는 함수를 호출해준다.
```C
void	execute(t_ast *tree, t_env_pack *pack, t_info *info)
{
	if (!tree)
		return ;
	else if (tree->type == T_PIPE)
	{
		info->depths++;
		return (execute_pipe(tree, pack, info, info->depths));
	}
	else if (tree->type == T_OR || tree->type == T_AND)
		return (logical_exp(tree, pack, info));
	else
	{
		do_execution(tree, pack, info);
		if (info->fork_num)
			ft_wait(info, pack);
	}
}
```
여기서 `t_info`라는 구조체를 사용하는데, 이 구조체는 실행, 특히 다중 파이프 실행에 필요한 정보들을 담고 있는 구조체이다. 이 구조체는 execute함수를 들어갈 때마다(재귀 포함) 초기화된다.
```C
struct s_info
{
	int			depths;		// 현재 몇 번째 가지(재귀)에 있는지 확인용
	pid_t			last_pid;	// 가장 마지막에 fork()된 프로세스 id, exit code 확인용
	int			fork_num;		// 몇번 fork()되었는지 기록, wait해야할 프로세스의 개수를 알아야 함
	int			pipe_fds[2];		// pipe()의 결과물을 기록한다.
	int			prev_fd;		// 이전 명령어의 읽기 파이프
	int			redir_fds[2];		// 리다이렉션 파이프, 기본값은 표준입출력 fd이고 만약 in_redir, out_redir이 있을때 해당 파일을 open할 때 리턴받은 fd값으로 바꿔준다
	int			exit_status;		// 프로세스의 종료 상태를 받아오는 변수
};
```

#### 단순 명령어 실행 Simple command execution
받은 트리 구조체를 바로 실행으로 넘기기 전 실행을 편리하게 하기 위해 실행용 구조체로 바꾸는 가공 작업을 거친다.
```C
struct s_cmd_pack
{
	char		**c_args;	// builtin/systemcall, arguments/options를 담고 있는 캐릭터 이중 포인터
	t_redir		*all_redirs;	// 해당 커맨드 블럭(pipe로 구분됨)의 모든 리다이렉션을 기록한 연결리스트, 실행부로 들어올 때, 모든 cmd_pack 구조체의 리다이렉션을 훑고 파일들을 열어야한다
	t_redir		*in_redirs;	// 최종적으로 사용될 input redirection('<', "<<")
	t_redir		*out_redirs;	// 최종적으로 사용될 output redirection('>', ">>")
};
```

만들어진 `t_cmd` 구조체를 활용해, 먼저 `all_redirs`를 순회하며 리다이렉션에 해당되는 파일들을 전부 열고, here_doc도 처리해 준다. 만약 리다이렉션 처리 중 오류가 발생하면, 커멘드 구조체를 할당 헤제하고 실행에 들어가지 않는다.
리다이렉션 처리가 완료되면, 단일 빌트인 여부를 확인한다. depth가 0이고, 명령어의 종류가 빌트인일 경우에는 이전 파이프에서 읽어올 정보가 없고 `fork()`를 할 필요가 없기 때문에 따로 빼서 처리하였다.
그 이외의 경우에는 명령어를 실행해준다.
```C
void	do_execution(t_ast *tree, t_env_pack *pack, t_info *info)
{
	t_cmd	*cmd;

	cmd = build_cmd_pack(tree, pack);
	info->exit_status += scan_n_set_redirs(cmd, pack);
	if (info->exit_status)
		return (free_cmd(cmd));
	if (info->depths == 0 && solo_builtin(cmd, pack) != -1)
		return (free_cmd(cmd));
	if (info->exit_status == 0)
		execute_cmd(cmd, pack, info);
	return (free_cmd(cmd));
}
```

