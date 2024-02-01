# Minis"hell" 실행부 기록

뽀오나쓰 까지 진행되는 미니셸의 실행부 파트를 맡게 되었다..
일단 이전에 mandatory 파트 부분에서 써먹을 수 있는 부분은 다 긁어왔다(코드 재활용 최고~~).

### 환경변수 Environment variables
터미널에서 `env`를 치거나 인자없이 `export`를 치면 해당 터미널의 환경변수 목록이 나오는데 둘이 약간의 차이가 있다.
`env`는 정렬이 되지 않은 상태로 출력되고, `export`는 각 변수 앞에 `declare -x`가 붙고 정렬이 된 상태로 출력된다.
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

### 확장과 따옴표 처리 Expension and quoting

### 빌트인 builtins
**- echo**
**- cd**
**- pwd**
**- export**
**- unset**
**- env**
**- exit**

### 시그널 처리 / 종료 코드 Signal handling / exit code

### AST 순회 및 파이프/리다이렉션 executing, pipe, and redirection
