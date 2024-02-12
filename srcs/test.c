#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

char	**add_str(char **str, char *add)
{
	char	**new;
	int		i;

	if (!add)
		return (str);
	i = 0;
	while (str && str[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		exit(1);
	i = 0;
	while (str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = add;
	i++;
	new[i] = 0;
	if (str)
		free(str);
	return (new);
}

int	check_wildfixes(char *filename, char *pattern)
{
	char	*substr;
	int	start;
	int	end;
	int	i;

	start = 0;
	end = ft_strlen(pattern) - 1;
	i = 0;
	if (pattern[0] == '*')
	{
		start = 1;
		i = 1;
	}
	while (pattern[i])
	{
		// a*
		if (start == 0 && i != 0 && pattern[i] == '*')
		{
			end = i - 1;
			if (ft_strncmp(filename, pattern, i))
				return (0);
			start = i + 1;
		}
		else if (pattern[i] == '*')
		{
			end = i - 1;
			substr = ft_substr(pattern, start, end - start + 1);
			if (!ft_strnstr(filename, substr, ft_strlen(filename)))
			{
				free(substr);
				return (0);
			}
			free(substr);
			start = i + 1;
		}
		i++;
	}
	if (!start && end == (int)ft_strlen(pattern) - 1)
	{
		if (ft_strncmp(filename, &(pattern[start]), ft_strlen(filename)))
			return (0);
	}
	else if (start < i)
	{
		int	remains;
		int	filename_len;
		remains = ft_strlen(&(pattern[start]));
		filename_len = ft_strlen(filename);
		if (ft_strncmp(&(filename[filename_len - remains]), &(pattern[start]), remains))
			return (0);
	}
	return (1);
}

char	**expand_wildcard(char *arg)
{
	DIR				*dp;
	struct dirent	*entry;
	char			**args;

	args = NULL;
	dp = opendir(".");
	entry = readdir(dp);
	entry = readdir(dp);
	entry = readdir(dp);
	while (entry)
	{
		if (check_wildfixes(entry->d_name, arg))
			args = add_str(args, ft_strdup(entry->d_name));
		entry = readdir(dp);
	}
	if (!args)
		args = add_str(args, ft_strdup(arg));
	closedir(dp);
	return (args);
}

int	main(void)
{
	char	**expanded_arg;

	expanded_arg = expand_wildcard("a*");
	
	if (expanded_arg)
	{
		int	i = 0;
		while (expanded_arg[i])
		{
			printf("%s\n", expanded_arg[i]);
			i++;
		}
	}
}
