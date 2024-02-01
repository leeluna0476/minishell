#include "parse_struct.h"
#include "libft/libft.h"
#include <stdio.h>

int	is_space(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

t_piece	*new_piece(char *string)
{
	t_piece	*piece;

	if (string)
	{
		piece = ft_calloc(1, sizeof(t_piece));
		if (piece)
		{
			piece->string = ft_strdup(string);
		}
		return (piece);
	}
	return (NULL);
}

t_piece	*last_piece(t_piece *list)
{
	t_piece	*curr;

	curr = list;
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	return (curr);
}

void	add_piece(t_piece **list, t_piece *piece)
{
	t_piece	*last;

	if (list)
	{
		if (*list)
		{
			last = last_piece(*list);
			last->next = piece;
		}
		else
		{
			*list = piece;
		}
	}
}

void	free_piece(t_piece *piece)
{
	free(piece->string);
	free(piece);
}

t_bool	is_meta1(char c)
{
	const char	*meta1 = "><&|;";
	int			i;

	i = 0;
	while (meta1[i])
	{
		if (c == meta1[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	is_meta2(char c)
{
	const char	*meta2 = "()\"\'";
	int			i;

	i = 0;
	while (meta2[i])
	{
		if (c == meta2[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
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
	*string = ft_substr(line, 0, 1);
	return (1);
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

t_piece	*lexer(char *line)
{
	t_piece		*pieces;
	t_piece		*node;
	char		*string;
	int			i;
	int			temp;

	pieces = NULL;
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (is_meta1(line[i]))
			i += get_meta1(&(line[i]), &string);
		else if (is_meta2(line[i]))
			i += get_meta2(&(line[i]), &string);
		else
			i += get_word(&(line[i]), &string);
		node = new_piece(string);
		add_piece(&pieces, node);
		free(string);
		i += remove_space(&(line[i]));
	}
	return (pieces);
}

void	leaks(void)
{
	system("leaks -q a.out");
}

int	main(void)
{
	t_piece	*pieces;
	t_piece	*curr;

	atexit(leaks);
	pieces = lexer("echo \"$USER\"; (ls -l | wc -l) > outfile");

	curr = pieces;
	while (curr)
	{
		printf("%s\n", curr->string);
		curr = curr->next;
	}
	while (pieces)
	{
		curr = pieces;
		pieces = pieces->next;
		free_piece(curr);
	}
}
