# Fix
1. 명령어를 실행하고 나서 process가 계속 남아있음?
2. 잘못된 명령어가 들어가면 미니쉘이 실행됨.
3. exit builtin이 exit이 안 됨.
4. exit에 쓰이는 ft_putstr_fd()이 ft_printf와 충돌. segmentation fault.
5. pipeline, 환경변수 확장에서 pointer being freed is not allocated 오류.
6. outfile redirection은 파일이 없다면 생성을 하고 있는 것 같은데도 no such file or directory 오류
