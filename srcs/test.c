#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include <unistd.h>

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

// 디렉토리 여부는 d_type == DT_DIR으로 확인.
int	check_wildfixes(char *filename, __uint8_t type, char *pattern)
{
	char	*substr;
	int		filename_len;
	int		remains;
	int		start;
	int		end;
	int		i;


	start = 0;
	end = ft_strlen(pattern) - 1;
	i = 0;
	if (pattern[0] == '*')
	{
		start = 1;
		i = 1;
	}
	while (pattern[i] && pattern[i] != '/')
	{
		if (start != i)
		{
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
		}
		i++;
	}
	if (pattern[i] == '/' && type != DT_DIR)
		return (0);
	if (!start && end == (int)ft_strlen(pattern) - 1)
	{
		if (ft_strncmp(filename, &(pattern[start]), ft_strlen(filename)))
			return (0);
	}
	else if (start < i)
	{
		remains = ft_strlen(&(pattern[start]));
		filename_len = ft_strlen(filename);
		if (ft_strncmp(&(filename[filename_len - remains]), &(pattern[start]), remains))
			return (0);
	}
	return (i);
}

char	**expand_wildcard(char *arg)
{
	DIR				*dp;
	struct dirent	*entry;
	char			**args;
	int				i;

	args = NULL;
	dp = opendir(".");
	entry = readdir(dp);
	entry = readdir(dp);
	entry = readdir(dp);
	while (entry)
	{
		i = check_wildfixes(entry->d_name, entry->d_type, arg);
		if (i)
			args = add_str(args, ft_strjoin(entry->d_name, &(arg[i])));
		entry = readdir(dp);
	}
	closedir(dp);
	return (args);
}

int	main(int ac, char *av[], char *envp[])
{
	char	**expanded_arg;
//	char	**final_arg;
//	pid_t	pid;

	(void)ac;
	(void)av;
	(void)envp;
	expanded_arg = expand_wildcard("*");

//	if (expanded_arg)
//	{
//		final_arg = NULL;
//		final_arg = add_str(final_arg, ft_strdup("ls"));
//		final_arg = add_str(final_arg, ft_strdup("-1G"));
//
//		int	i = 0;
//		while (expanded_arg[i])
//		{
//			final_arg = add_str(final_arg, ft_strdup(expanded_arg[i]));
//			free(expanded_arg[i]);
//			i++;
//		}
//		free(expanded_arg);
//
//		pid = fork();
//		if (pid == 0)
//			execve("/bin/ls", final_arg, envp);
//		else
//			wait(NULL);
//		i = 0;
//		while (final_arg[i])
//		{
//			free(final_arg[i]);
//			i++;
//		}
//		free(final_arg);
//	}
//	else
//		printf("no matches found: %s\n", "*");
	system("leaks -q a.out");
}
