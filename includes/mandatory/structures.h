/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:02:36 by seojilee          #+#    #+#             */
/*   Updated: 2024/03/05 09:25:02 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "../../srcs/libft/libft.h"

typedef struct s_token		t_token;
typedef struct s_ast		t_ast;
typedef struct s_mark		t_mark;
typedef struct s_env		t_env;
typedef struct s_env_pack	t_env_pack;
typedef struct s_cmd_pack	t_cmd;
typedef struct s_redir		t_redir;
typedef struct s_expand		t_c_expand;	
typedef struct s_exp_pair	t_exp_pair;
typedef enum e_type			t_type;
typedef struct s_info		t_info;

enum	e_type
{
	T_ERROR = -1,
	T_SPACE,
	T_AND,
	T_OR,
	T_PIPE,
	T_WORD,
	T_LESSER,
	T_GREATER,
	T_D_LESSER,
	T_D_GREATER,
	T_OPEN_BRACKET,
	T_CLOSE_BRACKET,
	T_NEWLINE
};

enum	e_b_type
{
	B_FALSE = -1,
	B_ECHO,
	B_CD,
	B_PWD,
	B_EXPORT,
	B_UNSET,
	B_ENV,
	B_EXIT
};

struct s_token
{
	enum e_type		type;
	char			*string;
	struct s_token	*next;
	struct s_token	*prev;
};

struct s_ast
{
	enum e_type		type;
	struct s_token	*start;
	struct s_token	*end;
	char			*error;
	struct s_ast	*left;
	struct s_ast	*right;
};

struct s_mark
{
	int	start;
	int	end;
};

struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*origin_prev;
	struct s_env	*origin_next;
	struct s_env	*sorted_prev;
	struct s_env	*sorted_next;
};

struct s_env_pack
{
	char	**envp;
	t_env	*origin_head;
	t_env	*origin_last;
	t_env	*sorted_head;
};

struct s_cmd_pack
{
	char		**c_args;
	t_redir		*all_redirs;
	t_redir		*in_redirs;
	t_redir		*out_redirs;
};

struct s_redir
{
	enum e_type	type;
	char		**filename;
	int			fd;
	t_redir		*next;
};

struct s_expand
{
	char		*original;
	t_exp_pair	**exp_ptrs;
	int			exp_num;
	int			wild_num;
	int			wild_flag;
	char		**result;
};

struct s_exp_pair
{
	char	q_flag;
	char	*exp_name;
	char	*exp_pos;
};

struct s_info
{
	int			depths;
	pid_t		last_pid;
	int			fork_num;
	int			pipe_fds[2];
	int			prev_fd;
	int			redir_fds[2];
	int			exit_status;
};

#endif
