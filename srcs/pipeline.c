#include "pipeline.h"
#include "parser.h"
#include <fcntl.h>
#include <unistd.h>

typedef struct s_cmd t_cmd;

struct s_cmd
{
	t_token	*start;
	t_token	*end;
	t_cmd	*prev;
	t_cmd	*next;
};

// 0. ast->type이 redirection 또는 word라면 바로 실행.
// 1. ast->type이 T_PIPE가 될 때까지 재귀를 돈다.
// 2. T_PIPE를 만나면 연결리스트를 만든다.
// 3. 파이프를 만들면서 순차적으로 실행한다.
	// 3-0. redirection: start) 0, pipe[1], mid) pipe1[0], pipe2[1], end) pipe2[0], 1
	// 3-1. get path
	// 3-2. execute

t_cmd	*new_cmd(t_token *start, t_token *end)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (new)
	{
		new->start = start;
		new->end = end;
	}
	return (new);
}

t_cmd	*last_cmd(t_cmd *list)
{
	t_cmd	*curr;

	curr = list;
	while (curr && curr->next)
		curr = curr->next;
	return (curr);
}

void	add_cmd(t_cmd **list, t_cmd *cmd)
{
	t_cmd	*last;

	if (list)
	{
		if (!(*list))
			*list = cmd;
		else
		{
			last = last_cmd(*list);
			last->next = cmd;
			cmd->prev = last;
		}
	}
}


