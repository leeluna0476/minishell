# BNF (Backers & Naur Form)
- 문맥자유문법(Context Free Grammer: CFG)에서 생성규칙들의 집합을 의미한다.

## 예시
```BNF
<assign> -> <id> = <expr> ; A = B + 10
```
- 생성규칙의 왼쪽(Left hand side: LFS)은 생성규칙의 이름을 나타낸다.
- 생성규칙의 오른쪽(Right hand side: RFS)은 LHS의 이름을 갖는 생성규칙의 내용을 나타낸다.
- 생성규칙을 만들려면 `<id>와 <expr>`이 먼저 구현되어 있어야 한다.

- 하나의 LHS(규칙)는 여러 개의 RHS를 가질 수 있다.
```BNF
<expr> -> <expr> + <expr>
<expr> -> <expr> - <expr>

<expr> -> <expr> + <expr>
        | <expr> - <expr>
```
- 여러 개의 RHS를 가질 경우, 논리기호 `|`를 사용해서 하나의 규칙을 나타낼 수 있다. 하나의 LHS가 여러 개의 RHS 중 하나를 선택하는 구조일 때 사용한다.

### 예시

```BNF
<number> -> <number><digit> | <digit>

<digit> -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9

; 1234 유도.
<number> -> <number><digit>					; <number>를 <number><digit>으로 변환.
         -> <number><digit><digit>
         -> <number><digit><digit><digit>	;
         -> <digit><digit><digit><digit>	; <number>를 <digit>으로 변환.
         -> 1<digit><digit><digit>
         -> 12<digit><digit>
         -> 123<digit>
         -> 1234
```
- <digit>은 0 ~ 9 중 한가지 종류일 수 있고,
- <number>은 한자리, 또는 여러자리일 수 있다.

```BNF
<assign> -> <id> = <expr>

<id> -> A | B | C

<expr> -> <expr> + <expr>
        | <expr> - <expr>
        | (<expr>)
        | <number>

<number> -> <number><digit> | <digit>

<digit> -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9

; A = 3 + (5 - 2)
<assign> -> <id> = <expr>
         -> A = <expr>
         -> A = <expr> + <expr>
         -> A = <number> + <expr>
         -> A = <digit> + <expr>
         -> A = 3 + <expr>
         -> A = 3 + (<expr>)
		 -> A = 3 + (<expr> - <expr>)
         -> A = 3 + (<number> - <expr>)
         -> A = 3 + (<digit> - <expr>)
         -> A = 3 + (5 - <expr>)
         -> A = 3 + (5 - <number>)
         -> A = 3 + (5 - <digit>)
         -> A = 3 + (5 - 2)
```
