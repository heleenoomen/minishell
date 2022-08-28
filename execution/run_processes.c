/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 21:27:43 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/28 18:14:29 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	run_cmd_child(t_exec *exec, t_cmd_def *cmd, t_minishell *minishell)
{
	char	**env;

	close(exec->pipe_fd[0]);
	exec->curr_cmd = /* put into array the list of cmds*/;
	if (exec->curr_cmd)
	{
		duplicate_fd(exec)
		env = /*get env // path */;
		if (execve(exec->curr_cmd[0], exec->curr_cmd, env) == -1)
			perror("exec failed");
		/*free env // path */
	}
	if (exec->fd_in > 0)
		close(exec->fd_in);
	close(exec->pipe_fd[1]);
	free(exec->curr_cmd);
	/*free list of cmnds */
	/*free minishell */
	exit(g_global_exit_status);
}

int	child_process(t_exec *exec, t_cmd_def *cmd, t_minishell *minishell)
{
	int	status;

	status = 0;
	child_send_signal();
	/* free table */
	/* free cmd */
	status = 0;
	if (exec->fd_in >= 0 && exec->fd_out > 0)
		status = run_cmd_child(exec, cmd, minishell);
	else
	{
		close(exec->pipe_fd[0]);
		close(exec->pipe_fd[1]);
		/* free cmd */
		/* free shell */
		if (exec->fd_in < 0 || exec->fd_out < 0)
			exit(g_global_exit_status);
		else
			exit(EXIT_SUCCESS);
	}
	return (status);
}

/*check CAT CMD!!!*/
int	parent_process(t_exec *exec, t_cmd_def *cmd)
{
	t_ast	*node;

	node = lst_get_content(*exec->cmds_list);
	if (ft_lstsize(*exec->cmds_list) && cmd && cmd->cmd && \
		node->type != N_AND && node->type != N_OR)
		waitpid(exec->pid, NULL, 0);
	else
		waitpid(exec->pid, NULL, 1);
	close(exec->pipe_fd[1]);
	if (exec->fd_in > 0)
		close(exec->fd_in);
}

int	fork_process(t_exec *exec_cmds, t_cmd_def *cmds, t_minishell *minishell)
{
	int	status;

	status = 0;
	if (pipe(exec_cmds->pipe_fd) == -1)
	/* status = error */
	exec_cmds->pid = fork();
	if (exec_cmds->pid == -1)
		status = /* error */
	if (status == 0)
		exec_cmds->forks = 1;
	parent_send_signal();
	if (exec_cmds->pid == 0 && status == 0)
		status = child_process(exec_cmds, cmds, minishell);
	parent_process(exec_cmds, cmds);
	return (status);
}
