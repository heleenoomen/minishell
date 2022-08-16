/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:59:21 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/16 19:53:10 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include<limits.h>

typedef struct t_env_hash
{
	char	*key;
	char	*value;
	bool	for_export;
}

typedef struct s_env_tree
{
	char				*key;
	char				*value;
	bool				for_export;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}						t_env_tree;

typedef struct s_env
{
	t_env_tree	tree;
	int			size;
	int			free;
	int			deleted;
	t_env_hash	*hash;	
	char		*cwd;
}				t_env;


# define NO_QUOTES 0
# define SINGLE_QUOTES 1
# define DOUBLE_QUOTE 2

# define EXPORT 1
# define NO_EXPORT 0

# define UNKNOWN -1

# define WARNING_TOO_MANY_SHLVLS "Minishell: Warning: level of shells (1000) too high, resetting to 0"

/* env_init.c */
void	init_env_struct(t_env *env);
void	startup_without_environment(t_env *env);
void	set_shlvl(t_env *env, char *value, int i);
void	update_shlvl(t_env *env);
void	init_env(t_env *env, char **envp);

/* add_to_env.c */
int		manipulate_ptrs(char *envp_entry, char **value_ptr);
int		add_to_hash(t_env *env, char *key, char *value, for_export);
int		add_key_value_to_env(t_env *env, char *key, char *value, bool for_export)
int		add_str_to_env(t_env *env, char *s, bool for_export)
int		add_key_value_dup_to_env(t_env *env, char *key, char *value, bool for_export); // yet to write

/* update_value.c */
int		update_value(t_env *env, t_tree_node *node, char *value, bool for_export); // yet to write
void	update_hash(t_env *env, t_tree_node *leaf); //written, in add_to_env.c
int		update_value_dup(t_tree_node *node, char *value, bool for_export); //dups value, free existing value and adds new value

/* tree_utils.c */
t_tree_node		*find_node(t_tree_node *root, char *key); //todo
char			*get_value(t_tree_node *root, char *key); //todo
		
/* resize_env.c */
int			resize_env(t_env *env);

/* env_utils.c */
void		clear_env(t_env *env);
int			key_index(t_env *env, char *key);
char		*find_value(t_env *env, char *key);

/* sort_env.c */
int			sort_hash_entry(t_env *env, int i);

#endif

