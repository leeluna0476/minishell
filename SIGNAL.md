# Signal
- Handle Ctrl-C, Ctrl-D and Ctrl-\ which should behave like in bash.
- In interactive mode:
	- Ctrl-C displays a new prompt on a new line.
	- Ctrl-D exits the shell.
	- Ctrl-\ does nothing.

## Signal handler
```c
volatile sig_atomic_t	g_status;

void	sig_handler(int signo)
{
	g_status = signo;
}
```
signal handler는 비동기 작업을 지원하기 때문에 data race가 발생할 수 있고, 특별한 자료형을 사용해야 한다.

`volatile sig_atomic_t` 자료형은 시그널과 같은 비동기 작업에서도 원자적인 접근을 보장한다.
*`volatile` 키워드는 컴파일러 최적화를 거치지 않고 본래의 코드 그대로 어셈블리로 변환되는 것을 보장한다.*
