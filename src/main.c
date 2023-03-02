/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:01:13 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/02 19:36:43 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

t_ms g_ms;

static void	sigint_action(int signal)
{
	rl_replace_line("", signal);
	printf("\n");
	printf(CLR_BLUE"\n[%s]\n"CLR_RST, g_ms.cwd);
	rl_on_new_line();
	rl_redisplay();
}

static void	read_input()
{
	printf(CLR_BLUE"\n[%s]\n"CLR_RST, g_ms.cwd);
	while (1)
	{
		g_ms.input = readline(PROMPT);
		if (g_ms.input && ft_strlen(g_ms.input) != 0)
			break ;
		else if (g_ms.input)
			free(g_ms.input);
		else
			no_leaks(1);
	}
}

// returns the content of the var in env with the name str or just returns str
char	*get_env(char *str)
{
	int		len;
	t_var	*tmp;

	if (str[0] == '$')
		str++;
	len = ft_strlen(str);
	tmp = g_ms.env->top;
	while (tmp->next)
	{
		if (!ft_strncmp(tmp->name, str, len))
			return (tmp->content);
		tmp = tmp->next;
	}
	if (!ft_strncmp(tmp->name, str, len))
		return (tmp->content);
	return (str--);
}

// pushes to tmp, if new name, else changes content to the new one
void	ft_stackpush(t_env *env, char *equal)
{
	int		i;
	char	*name;
	t_var	*tmp;
	t_var	*new;

	i = 0;
	tmp = env->top;
	while (equal[i] != '=')
		i++;
	name = ft_strndup(equal, i);
	if (tmp)
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, name))
			{
				i++;
				tmp->content = ft_strdup(equal + i);
				return ;
			}
			tmp = tmp->next;
		}
	}
	new = malloc(sizeof(t_var));
	new->name = name;
	i++;
	new->content = ft_strdup(equal + i);
	new->next = env->top;
	env->top = new;
	env->size++;
}

// new empty list
t_env	*ft_stacknew(void)
{
	t_env	*ret;

	ret = malloc(sizeof(t_env));
	if (!ret)
		return (NULL);
	ret->size = 0;
	ret->top = NULL;
	return (ret);
}

// creates and fills the env list with var (including name and content)
t_env	*envlist(char **envv)
{
	t_env	*env;
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (envv[i++])
		size++;
	i = size - 1;
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->size = 0;
	env->top = NULL;
	while (i >= 0)
		ft_stackpush(env, envv[i--]);
	return (env);
}

static void	fill_args(char **envv)
{
	if (g_ms.cwd)
		free(g_ms.cwd);
	g_ms.envv = envv;
	g_ms.env = envlist(envv);
	g_ms.tmp = ft_stacknew();
	g_ms.path = ft_split(get_env("PATH"), ':');
	g_ms.cwd = getcwd(NULL, 4096);
	g_ms.tokensfreed = 1;
	return ;
}

// env builtin, prints all env
void	env()
{
	t_var	*tmp;

	tmp = g_ms.env->top;
	if (!tmp)
		return ;
	while (tmp->next)
	{
		printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
	printf("%s=%s\n", tmp->name, tmp->content);
}

void	echo(int flag)
{
	int		i;
	int		size;
	char	*tmp;

	size = 0;
	i = 1;
	if (flag)
		i++;
	while (g_ms.tokens[i])
	{
		if (g_ms.tokens[i][0] == '$')
		{
			size = ft_strlen(get_env(g_ms.tokens[i]));
			tmp = malloc(sizeof(char) * (size + 1));
			tmp = get_env(g_ms.tokens[i]);
			ft_free(g_ms.tokens[i]);
			g_ms.tokens[i] = malloc(sizeof(char) * (size));
			g_ms.tokens[i] = tmp;
		}
		printf("%s", g_ms.tokens[i++]);
		if (!flag)
			printf("\n");
	}
}

//export (add a=x expression, if previously stored in tmp to env)
void	export()
{
	int		i;
	t_var	*tmpenv;
	t_var	*tmp;
	t_var	*new;

	i = 1;
	new = malloc(sizeof(t_var));
	tmpenv = g_ms.tmp->top;
	tmp = g_ms.env->top;
	while (g_ms.tokens[i])
	{
		tmpenv = g_ms.tmp->top;
		while (tmpenv)
		{
			if (!ft_strcmp(tmpenv->name, g_ms.tokens[i]))
			{
				while (tmp)
				{
					if(!ft_strcmp(tmpenv->name, tmp->name))
					{
						tmp->content = tmpenv->content;
						free (new);
						return ;
					}
					tmp = tmp->next;
				}
				new->name = ft_strdup(tmpenv->name);
				new->content = ft_strdup(tmpenv->content);
				new->next = g_ms.env->top;
				g_ms.env->top = new;
				g_ms.env->size++;
			}
			tmpenv = tmpenv->next;
		}
		i++;
	}
}

//unset (remove a=x expression, if stored in env or in tmp)
void	unset()
{
	int		i;
	t_var	*tmpenv;
	t_var	*prev;

	i = 1;
	while (g_ms.tokens[i])
	{
		prev = NULL;
		tmpenv = g_ms.tmp->top;
		while (tmpenv)
		{
			if (!ft_strcmp(tmpenv->name, g_ms.tokens[i]))
			{
				ft_free(tmpenv->name);
				ft_free(tmpenv->content);
				g_ms.tmp->size--;
				if (prev)
					prev->next = tmpenv->next;
				else
					g_ms.tmp->top = tmpenv->next;
			}
			prev = tmpenv;
			tmpenv = tmpenv->next;
		}
		prev = NULL;
		tmpenv = g_ms.env->top;
		while (tmpenv)
		{
			if (!ft_strcmp(tmpenv->name, g_ms.tokens[i]))
			{
				ft_free(tmpenv->name);
				ft_free(tmpenv->content);
				if (prev)
					prev->next = tmpenv->next;
				else
				{
					g_ms.env->top = tmpenv->next;
				}
				g_ms.env->size--;
			}
			prev = tmpenv;
			tmpenv = tmpenv->next;
		}
		i++;
	}
}

//stores a=x expression in tmp
void	store_equals(char *equal)
{
	ft_stackpush(g_ms.tmp, equal);
}

//if there is a a=x expression, store it in tmp
int	find_equals()
{
	int	i;
	int	j;
	int r;

	r = 0;
	i = 0;
	while (g_ms.tokens[i])
	{
		j = 0;
		while (g_ms.tokens[i][j])
		{
			if (g_ms.tokens[i][j] == '=')
			{
				store_equals(g_ms.tokens[i]);
				r = 1;
				break ;
			}
			j++;
		}
		i++;
	}
	return (r);
}

// for testing purposes, print tmp list
void	printtmp()
{
	t_var	*tmp;

	tmp = g_ms.tmp->top;
	if (!tmp)
		return ;
	while (tmp->next)
	{
		printf("%s = %s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
	printf("%s = %s\n", tmp->name, tmp->content);
}

void	handle_input()
{
	g_ms.tokens = ft_split(g_ms.input, ' ');
	g_ms.tokensfreed = 0;

	if (find_equals())
		return ;
	if (!ft_strcmp(g_ms.tokens[0], "exit"))
		no_leaks(1);
	else if (!ft_strcmp(g_ms.tokens[0], "pwd"))
		printf("%s\n", g_ms.cwd);
	else if (!ft_strcmp(g_ms.tokens[0], "env"))
		env();
	else if (!ft_strcmp(g_ms.tokens[0], "echo"))
	{
		if (!ft_strcmp(g_ms.tokens[1], "-n"))
			echo(1);
		else
			echo(0);
	}
	else if (!ft_strcmp(g_ms.tokens[0], "unset"))
		unset();
	else if (!ft_strcmp(g_ms.tokens[0], "export"))
		export();
	else if (!ft_strcmp(g_ms.tokens[0], "cd"))
		cd();
	else if ((!ft_strcmp(g_ms.tokens[0], "ptmp"))) //for testing
		printtmp();
	else
		exec_if_exists(g_ms.tokens[0], NULL);
	// printf("%s\n", g_ms.cwd);
	// else if (!ft_strcmp(g_ms.input, "pwd"))

}


//add

void	exec(char *pathtoexe, char **argv)
{
	pid_t	pid;

	pid = fork();
	// execve(pathtoexe, argv, g_ms.envv);
	if (pid == 0)
		execve(pathtoexe, argv, g_ms.envv);
	else
		waitpid(pid, NULL, 0);
}

void	exec_if_exists(char *exe, char **argv)
{
	char	*pathtoexe;
	int		i;

	i = 0;
	while(g_ms.path[i])
	{
		pathtoexe = ft_strjoin(g_ms.path[i], "/");
		pathtoexe = ft_strjoin(pathtoexe, exe);
		if (access(pathtoexe, F_OK) == 0)
		{
			exec(pathtoexe, argv);
			free(pathtoexe);
			return ;
		}
		free(pathtoexe);
		i++;
	}
	pathtoexe = ft_strjoin(g_ms.cwd, "/");
	pathtoexe = ft_strjoin(pathtoexe, exe);
	if (access(pathtoexe, F_OK) == 0)
	{
		exec(pathtoexe, argv);
		free(pathtoexe);
		return ;
	}
	else
		printf("minishell: command not found: %s", exe);
	return ;
}

int	main(int argc, char **argv, char **envv)
{
	(void)argc;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_action);
	fill_args(envv);
	while (1)
	{
		read_input();
		add_history(g_ms.input);
		handle_input();

		// printf("%s\n", g_ms.input);
		//no_leaks(0);
	}
	return (0);
}
