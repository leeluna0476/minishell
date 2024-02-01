# minishell
seojilee &amp;&amp; yusekim's minishell

## Lexer
- metacharacters 기준으로 line을 분할.
  - | & ; ( ) < >

## Tokenizer
- Lexer가 분할한 단어들에 type 부여.

## Parser
- Tokenizer가 형성한 튜플형 리스트가 원래 순서 그대로 문법에 맞는지 확인.
- 문법 검사를 통과하면 AST script 형식으로 정렬.

## Abstract Syntax Tree
- Script를 Logical expression, Pipeline, Command 3가지 포인트로 분할한다.
- Script에 Logical expression이 포함되는지 가장 먼저 확인하고, 포함된다면 해당 부분을 기준으로 다시 2개의 Script로 분할한다.
- Script에 Logical expression이 없다면 Pipeline이 있는지 확인한다. 있다면 첫번째 파이프를 기준으로 왼쪽은 Command, 오른쪽은 다시 파이프라인으로 분할한다.
- Command는 Parser에서 형식에 맞춰서 정렬한 순서를 따라 name, prefix, suffix로 분할한다.
...
