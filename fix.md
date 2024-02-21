# Fix
1. 명령어를 실행하고 나서 process가 계속 남아있음? -> zombie process?
2. 잘못된 명령어가 들어가면 미니쉘이 실행됨. -> does not exit
3. exit builtin이 exit이 안 됨. -> ?????
4. exit에 쓰이는 ft_putstr_fd()이 ft_printf()와 충돌. segmentation fault. -> use yusekim's ft_printf
5. pipeline, 환경변수 확장에서 pointer being freed is not allocated 오류. -> ??
6. outfile redirection은 파일이 없다면 생성을 하고 있는 것 같은데도 no such file or directory 오류
7. cat -e < Makefile과 같이 리다이렉션이 뒤에 붙는 건 괜찮은데 < Makefile cat -e처럼 앞으로 붙으니까 안 됨.
8. echo에서 공백문자를 출력하는데 마지막 argument 뒤에도 들어간다. minishell> echo -n abc, abc minishell> -> 아직 argument가 더 있을 때만 공백을 출력하면 된다.
9. cd builtin이 실행이 안 됨. cd ~는 또 됨..
