/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:39:36 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/23 11:01:25 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "exec_structures.h"
# include "utils.h"

# define PROMPT "minishell> "

// execute.c
void	execute(t_ast *tree, t_env_pack *pack, t_info *info);
void	logical_exp(t_ast *tree, t_env_pack *pack, t_info *info);
void	execute_pipe(t_ast *tree, t_env_pack *pack, t_info *info, int level);
void	do_execution(t_ast *tree, t_env_pack *pack, t_info *info);
void	execute_cmd(t_cmd *cmd, t_env_pack *envs, t_info *info);
int		get_exitstat(t_env_pack *pack);


// execute_utils.c
char	**make_envp(t_env_pack *envs);
int		is_route(char *str);
int		is_dir(char *str);
char	*path_join(char *path, char *arg);
void	exec_parent(t_info *info);

// execute_utils2.c
t_cmd	*build_cmd_pack(t_ast *tree, t_env_pack *pack);
void	ft_execve(t_cmd *cmd, t_env_pack *envs);
void	relative_execve(char **args, t_env_pack *envs, char **envp);
void	ft_perror(const char *str, int exit_num);
void	free_cmd(t_cmd *cmd);

// pipe_utils.c
void	set_fds(t_cmd *cur, t_info *info);
void	ft_dup2(t_info *info);
void	ft_wait(t_info *info, t_env_pack *pack);

#endif
