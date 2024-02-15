# Wildcard
`*`: Wildcard 와일드카드

주어진 패턴에 따라 파일명을 확장한다.

***Wildcards * should work for the current working directory.***

## 확장
```
DIR		*opendir(const char *filename);
struct dirent	*readdir(DIR *dirp);
int		closedir(DIR *dirp);
```
1. 현재 디렉토리를 열어서 파일에 대한 정보를 하나씩 읽는다.
2. 각 파일명이 주어진 패턴에 맞는지 확인한다. (`., ..` 제외.)
3. 맞다면 `char **` 타입의 argument list에 추가한다.
4. 디렉토리를 닫는다.

### 패턴 확인
- `*c`: filename을 뒤에서부터 "c"와 ft_strncmp().
- `a*`: filename을 앞에서부터 "a"와 ft_strncmp().
- `*abc*`: filename과 "abc"를 ft_strnstr().

위 3가지를 반복한다.

파일명은 `'\0'` 또는 `'/'`까지만 검사한다. 하위 디렉토리는 확장을 하지 않기 때문이다.

argument list에 추가할 때는 먼저 `/` 뒤에 있는 문자열과 ft_strjoin()을 한다.

## 예
- `*.c`: ".c" 로 끝나는 모든 파일.
- `a*`: "a"로 시작하는 모든 파일.
- `a*.c`: "a"로 시작하고 ".c"로 끝나는 모든 파일.
- `*abc*`: "abc"를 포함하는 모든 파일.
- `a*abc*.c`: "a"로 시작하고 "abc"를 포함하며, ".c"로 끝나는 모든 파일.
- `a*/*`: 현재 디렉토리에서 "a"로 시작하는 모든 디렉토리 아래에 있는 "*"라는 파일. (하위 디렉토리 확장 X.)
