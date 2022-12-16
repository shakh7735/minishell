/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:29:03 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/31 22:04:46 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <termios.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ERR_INPUT		"minishell: Invalid number of arguments"
# define ERR_FILE		"minishell: no such file or directory: "
# define ERR_PERMITION	"minishell: permission denied: "
# define ERR_PIPE		"minishell: Invalid pipe"
# define ERR_DUP		"minishell: Invalid dup"
# define ERR_FORK		"minishell: Invalid fork"
# define ERR_COMMAND	"minishell: command not found: "
# define ERR_TOKEN   "minishell: syntax error near unexpected token: "
# define ERR_EXPORT		"minishell: export: not an identifier: "
# define ERR_MALLOC		"minishell: malloc error "
# define ERR_IDENT		"minishell: not a valid identifier: "
# define ERR_EXIT_DIGIT	"minishell: exit: numeric argument required: "
# define ERR_EXIT_ARG	"minishell: exit: too many arguments"
# define ERR_OLDPWD		"minishell: OLDPWD not set"
# define ERR_EOF1		"minishell: unexpected EOF while looking for matching"
# define ERR_EOF2   	"minishell: syntax error: unexpected end of file"

# define HEREDOC		"heredoc_temp.txt"

int	g_heredoc_sig;

typedef struct s_env
{
	struct s_env	*prev;
	int				exp_flag;
	char			*key;
	char			*vol;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd_args
{
	struct s_cmd_args	*prev;
	char				flag;
	char				flag_par;
	char				*arg;
	struct s_cmd_args	*next;
}						t_cmd_args;

typedef struct s_data
{
	int			fd_in;
	int			fd_out;
	int			*pid;
	int			flag_main;
	char		*prog_path;
	char		**cmds;
	char		**cmd_args;
	char		**path;
	t_env		*env;
	t_cmd_args	*cmd_list;
}				t_data;

//===================================================
//	utils
//===================================================

char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_my_substr(char **s, unsigned int start, size_t len);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	ft_exit(char *err, char *cmd, int id, int ercode);
void	ft_my_strtrim(char **s1, char const *set);
void	ft_str_short_begin(char **str, int start);
char	**ft_split(char const *s, char *charset);
void	ft_my_strjoin(char **s1, char const *s2);
char	*ft_strjoin(char *s1, char const *s2);
int		ft_my_strchr(const char *s, int c);
char	*ft_strchr(const char *s, int c);
void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(char *s1, char *s2);
char	*str_to_lowercase(char *s);
char	**ft_split_equal(char *s);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
int		ft_my_atoi(char *str);
char	*ft_epur_str(char *str);
int		is_my_alpha(char c);
void	get_errno(int ret);
int		is_digit(char c);
char	*ft_itoa(int n);

//===================================================
//	signals
//===================================================

void	handler_signals(int sig);
void	handler_signals2(int sig);
void	handler_signals3(int sig);

//===================================================
//	utils_free
//===================================================

void	free_mtx(char **buff);
void	free_env(char **env);

//===================================================
//	utils_list_cmds
//===================================================

void	new_list_arg(t_cmd_args **list, char *arg);
void	free_list_cmd_args(t_cmd_args *list);
void	delete_list_arg(t_cmd_args **list);
void	free_list_arg(t_cmd_args **list);
void	new_list_add(t_cmd_args **list);

//===================================================
//	utils_list_env
//===================================================

void	chenge_vol_list(t_data *data, char *key, char *vol, int flag);
t_env	*list_env_search_key(t_env *env, char *key);
int		check_key_and_add(t_data *data, char *key);
void	list_env_add_back(t_env *env, t_env *new);
void	init_ft_env(t_data *data, char **env);
char	*list_vol(t_env *env, char *key);
t_env	*go_first_point(t_env *list);
t_env	*create_new_elem_list(void);
t_env	*ft_copy_list(t_env *list);
void	free_list(t_env **list);

//===================================================
//	lists
//===================================================

int		check_in_out(t_data *data, t_cmd_args *list,
			t_cmd_args **arg, int main);
int		check_in_out2(t_data *data, t_cmd_args *list,
			t_cmd_args **arg, int main);
void	equal_exist(t_data *data, t_cmd_args **temp, int main);
char	**init_cmd_to_list(t_data *data, char *line, int main);
void	parse_files(t_data *data, t_cmd_args **list, int main);
void	check_make_dollar(t_env *env, t_cmd_args *list);
void	add_env_var(t_data *data, t_cmd_args *list_arg);
char	**list_to_args(t_cmd_args *list);
char	**get_envp(t_data *data);

//===================================================
//	pipex
//===================================================

int		get_multiline(char **line, int id, char *str);
int		pipex_bonus(t_data *data, char *line);
void	pipex(t_data *data, char *line);
void	cmd_pipe(t_data *data, int id);
int		pipe_count(char *str);

//===================================================
//	builtins
//===================================================

void	command_export(t_data *data);
void	command_unset(t_data *data);
void	command_echo(t_data *data);
void	command_exit(t_data *data);
void	command_cd(t_data *data);
void	command_pwd(void);

#endif
