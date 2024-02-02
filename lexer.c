#include "parse_struct.h"
#include "libft/libft.h"
#include <stdio.h>

int	is_space(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

t_token	*new_token(char *string, t_type type)
{
	t_token	*token;

	if (string)
	{
		token = ft_calloc(1, sizeof(t_token));
		if (token)
		{
			token->string = ft_strdup(string);
			token->type = type;
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
			token->prev = last;
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

t_type	get_type(char *string, int i)
{
	t_type	type;

	type = T_WORD;
	if (is_meta1(string[0]))
	{
		if (string[0] == '<')
		{
			if (i == 2)
				type = T_D_LESSER;
			else
				type = T_LESSER;
		}
		else if (string[0] == '>')
		{
			if (i == 2)
				type = T_D_GREATER;
			else
				type = T_GREATER;
		}
		else if (string[0] == '&')
		{
			if (i == 2)
				type = T_AND;
		}
		else if (string[0] == '|')
		{
			if (i == 2)
				type = T_OR;
			else
				type = T_PIPE;
		}
	}
	else if (is_meta2(string[0]))
	{
		if (string[0] == '(')
			type = T_OPEN_BRACKET;
		else if (string[0] == ')')
			type = T_CLOSE_BRACKET;
	}
	return (type);
}

int	get_meta1(char *line, char **string, t_type *type)
{
	int		i;

	i = 0;
	while (line[i] && line[0] == line[i] && i < 2 && !is_space(line[i]))
		i++;
	*string = ft_substr(line, 0, i);
	*type = get_type(*string, i);
	return (i);
}

int	get_meta2(char *line, char **string, t_type *type)
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
	*type = get_type(*string, i);
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

int	get_word(char *line, char **string, t_type *type)
{
	int	i;

	i = 0;
	while (line[i] && !is_space(line[i]) && !is_meta1(line[i]) && !is_meta2(line[i]))
		i++;
	*string = ft_substr(line, 0, i);
	*type = get_type(*string, i);
	return (i);
}

t_token	*lexer(char *line)
{
	t_token		*list;
	t_token		*node;
	char		*string;
	int			i;
	t_type		type;

	list = NULL;
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (is_meta1(line[i]))
			i += get_meta1(&(line[i]), &string, &type);
		else if (is_meta2(line[i]))
			i += get_meta2(&(line[i]), &string, &type);
		else
			i += get_word(&(line[i]), &string, &type);
		node = new_token(string, type);
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
	tokens = lexer("<<<<<&&&<<<<<<echo .... ---(()\'\"   $USER\"\');; (ls -l | wc -l) > outfile");

	curr = last_token(tokens);
	while (curr)
	{
		printf("%s  ", curr->string);
		printf("%d\n", curr->type);
		curr = curr->prev;
	}
	while (tokens)
	{
		curr = tokens;
		tokens = tokens->next;
		free_token(curr);
	}
}
