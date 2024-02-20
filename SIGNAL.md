# Signal
- Handle Ctrl-C, Ctrl-D and Ctrl-\ which should behave like in bash.
- In interactive mode:
	- Ctrl-C displays a new prompt on a new line.
	- Ctrl-D exits the shell.
	- Ctrl-\ does nothing.

**시그널은 비동기 이벤트 처리를 위한 메커니즘을 제공하는 소프트웨어 인터럽트다. 가장 기본적인 프로세스 간 통신 기법이다.**

## Signal handler
```c
volatile sig_atomic_t	g_status;

void	sig_handler(int signo)
{
	g_status = signo;
}
```
signal handler는 비동기적으로 호출된다.

어떤 작업 중에서도 실행 가능하므로 자신이 손대는 데이터와 기존에 실행되던 작업에 영향을 주지 않도록 각별히 주의해야 한다.

signal handler에서 사용해도 될 만한, *재진입*이 가능한 함수들이 있는데, 이들을 제외한 다른 함수들은 시그널 처리로 인해 잠시 정지되었다가 다시 호출되었을 때 무슨 일이 일어날지 알 수 없으므로 절대 signal handler 안에 포함시켜서는 안 된다.

같은 이유로 signal handler에서 사용하는 공유 개체는 원자적 읽기/쓰기를 보장하는`volatile sig_atomic_t`라는 특별한 자료형을 사용해야 한다.

특정 시그널에 대해 재진입 불가능한 함수를 사용하고 싶다면 위 예제 코드처럼 시그널 번호를 따로 저장해놓고 signal handler 외부에서 동기적으로 처리하는 것이 바람직하다.

### Signal handler에 의한 data race 예시

## 부록
- `volatile` 키워드는 컴파일러 최적화를 거치지 않고 본래의 코드 그대로 어셈블리로 변환되는 것을 보장한다.

- `volatile sig_atomic_t` 을 사용한다 할지라도 `g_status++;`과 같이 다중 명령으로 동작하는 경우에는 원자성을 보장하지 않는다.

- 함수 재진입이 가능한 조건:
  - 정적 (전역) 변수를 사용하면 안 된다.
  - 정적 (전역) 변수의 주소를 반환하면 안 된다.
  - 호출자가 호출 시 제공한 매개변수만으로 동작해야 한다.
  - 싱글턴 객체의 잠금에 의존하면 안 된다.
  - 다른 비-재진입 함수를 호출하면 안 된다.

<details>
<summary>재진입이 가능한 함수 목록</summary>
<div markdown="1">

- abort()
- chdir()
- _exit()
- getgid()
- lseek()
- read()
- setgid()
- signal()
- sysconf()
- timer_settime()
- aio_return()
- close()
- fdatasync()
- getpid()
- open()
- recvmsg()
- setuid()
- sigqueue()
- tcgetattr()
- unlink()
- cfgetispeed()
- dup2()
- fsync()
- getuid()
- poll()
- aio_error()
- clock_gettime()
- fcntl()
- getpgrp()
- mkfifo()
- recvfrom()
- setsockopt()
- sigprocmask()
- tcflush()
- uname()
- bind()
- dup()
- fstat()
- getsockopt()
- pipe()
- select()
- sigaddset()
- sleep()
- tcsetxattr()
- waitpid()
- cfsetospeed()
- _Exit()
- geteuid()
- listen()
- raise()
- alarm()
- creat()
- fpathconf()
- getsockname()
- pause()
- rmdir()
- sigaction()
- sigsuspend()
- tcsendbreak()
- wait()
- cfsetispeed()
- execve()
- getegid()
- link()
- pselect()
- sendmsg()
- sigfillset()
- stat()
- timer_getoverrun()
- access()
- chown()
- fchwon()
- getpeername()
- mkdir()
- recv()
- cfgetospeed()
- execle()
- ftruncate()
- kill()
- posix_trace_event()
- send()
- sigemptyset()
- socketpair()
- time()
- accept()
- chmod()
- fchmod()
- getgroups()
- lstat()
- readlink()
- setpgid()
- sigpause()
- tcdrain()
- times()
- aio_suspend()
- connect()
- fork()
- getppid()
- pathconf()
- rename()

</div>
</details>

### 참고 자료
- LINUX SYSTEM PROGRAMMING (Robert Love)
