#include "parse_struct.h"
#include "libft/libft.h"
#include <stdio.h>

int	is_space(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

t_token	*new_token(char *string)
{
	t_token	*token;

	if (string)
	{
		token = ft_calloc(1, sizeof(t_token));
		if (token)
		{
			token->string = ft_strdup(string);
		}
		return (token);
	}
	return (NULL);
}

t_token	*last_token(t_token *list)
{
	t_token	*curr;

	curr = list;
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	return (curr);
}

void	add_token(t_token **list, t_token *token)
{
	t_token	*last;

	if (list)
	{
		if (*list)
		{
			last = last_token(*list);
			last->next = token;
		}
		else
		{
			*list = token;
		}
	}
}

void	free_token(t_token *token)
{
	free(token->string);
	free(token);
}

int	is_meta1(char c)
{
	const char	*meta1 = "><&|;";
	int			i;

	i = 0;
	while (meta1[i])
	{
		if (c == meta1[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_meta2(char c)
{
	const char	*meta2 = "()\"\'";
	int			i;

	i = 0;
	while (meta2[i])
	{
		if (c == meta2[i])
			return (1);
		i++;
	}
	return (0);
}

int	get_meta1(char *line, char **string)
{
	int		i;

	i = 0;
	while (line[i] && is_meta1(line[i]) && i < 2 && !is_space(line[i]))
		i++;
	*string = ft_substr(line, 0, i);
	return (i);
}

int	get_meta2(char *line, char **string)
{
	int	i;

	i = 1;
	if (line[0] == '\"' || line[0] == '\'')
	{
		while (line[i] && line[i] != line[0])
			i++;
		i++;
	}
	*string = ft_substr(line, 0, i);
	return (i);
}

int	remove_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	return (i);
}

int	get_word(char *line, char **string)
{
	int	i;

	i = 0;
	while (line[i] && !is_space(line[i]) && !is_meta1(line[i]) && !is_meta2(line[i]))
		i++;
	*string = ft_substr(line, 0, i);
	return (i);
}

t_token	*lexer(char *line)
{
	t_token		*list;
	t_token		*node;
	char		*string;
	int			i;
	int			temp;

	list = NULL;
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (is_meta1(line[i]))
			i += get_meta1(&(line[i]), &string);
		else if (is_meta2(line[i]))
			i += get_meta2(&(line[i]), &string);
		else
			i += get_word(&(line[i]), &string);
		node = new_token(string);
		add_token(&list, node);
		free(string);
		i += remove_space(&(line[i]));
	}
	return (list);
}

void	leaks(void)
{
	system("leaks -q a.out");
}

int	main(void)
{
	t_token	*tokens;
	t_token	*curr;

	atexit(leaks);
	tokens = lexer("<<<<<<<<<<<echo .... ---(()\'\"   $USER\"\');; (ls -l | wc -l) > outfile");

	curr = tokens;
	while (curr)
	{
		printf("%s\n", curr->string);
		curr = curr->next;
	}
	while (tokens)
	{
		curr = tokens;
		tokens = tokens->next;
		free_token(curr);
	}
}
