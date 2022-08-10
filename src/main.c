/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:45:54 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/10 17:11:22 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"
#include "termios.h"

void	sighandler(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}

void	parse(char *buf, t_env *env)
{
	char	**new;
	char	**dup;
	
	new = ft_split(buf, ' ');
	dup = expander(new, env);
	free_argv_dup(&new);
	int i = 0;
	while (dup[i])
	{
		printf("%s\n", dup[i]);
		free(dup[i]);
		i++;
	}
	free(dup);	
}

void	cancel_echoctl(void)
{
	struct termios settings;

	tcgetattr(1, &settings);
	settings.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &settings);
}

void	reset_echoctl(void)
{
	struct termios settings;

	tcgetattr(1, &settings);
	settings.c_lflag |= ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &settings);
}

int	main(int argc, char **argv, char **envp)
{
	char		*buf;
	t_env		env;
//	char		termcap[2048];
		
	(void)argc;
	(void)argv;

//	init_termcap(termcap);
	init_env(&env, envp);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if(signal(SIGINT, sighandler) == SIG_ERR)
			exit(EXIT_FAILURE);
		//if(signal(SIGQUIT, sighandler) == SIG_ERR)
		//	exit(EXIT_FAILURE);
		cancel_echoctl();
		buf = readline("Minishell>>> ");
//		dprintf(2, "buf = %s\n", buf);
		if (buf  == NULL)
			break ;
		if (unclosed_quotes(buf))
		{
			dprintf(2, "Unclosed quotes\n");
			rl_on_new_line();
			continue ;
		}
		if (fork1() == 0)
			runcmd(parsecmd(buf), &env);
		signal(SIGINT, SIG_IGN);
		//signal(SIGQUIT, SIG_IGN);
		add_history(buf);
		free(buf);
		buf = NULL;
		wait(0);
	}
	clear_history();
	clear_env_data(&env);
	write(1, "Minishell>>> exit\n", 18);
	reset_echoctl();
	return (1);
}
