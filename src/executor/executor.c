/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:26:23 by cmarrued          #+#    #+#             */
/*   Updated: 2025/06/26 18:15:04 by intherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * args: cmd a ejecutar
 * env: nuestro env propio ya generado
 * fd_in: el archivo del cual leemos
 * fd_out: el archivo al cual escribimos
 * ejecutamos el cmd y retornamos un status. no 
 * hace falta cerrar por el exceve remplaza al prceso
 */
static void	child_execute(char *path, char **args, t_cmd_args *args_child)
{
	if (args_child->input_fd != -1)
	{
		dup2(args_child->input_fd, STDIN_FILENO);
		close(args_child->input_fd);
	}
	if (args_child->pipe_write_fd != -1)
	{
		dup2(args_child->pipe_write_fd, STDOUT_FILENO);
		close(args_child->pipe_write_fd);
	}
	if (execve(path, args, *args_child->env) == -1)
	{
		if (errno == ENOENT)
		{
			perror("No such file or directory");
			exit(127);
		}
		else if (errno == EACCES)
		{
			perror("Permission denied");
			exit(126);
		}
		else
			exit(1);
	}
}

/**
 * pid: pid del fork para esperar que acabe
 * path: puntero a path para poder liberarlo
 * esperamos al fork del hio a que acabe y limpiamos
 */
static int	parent_handle(pid_t pid, char *path)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid error");
		free(path);
		return (1);
	}
	init_signals();
	free(path);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(2, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

/**
 * cmd: cmd singular que ejecutar
 * env: nuestro env propio ya generado
 * buscamos el path al cmd que tenemos que ejecutar
 * vamos al ppath y intentamos ejecutar el comando
 * devolvemos el status
 */
static int	execute_command(t_cmd *cmd, t_cmd_args *args, t_state *state)
{
	pid_t	pid;
	char	*path;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (print_error("command not found", 0, 127, state), 127);
	path = get_command_path(cmd->args[0], *args->env);
	if (!path)
		return (print_error("command not found", 0, 127, state), 127);
	pid = fork();
	if (pid < 0)
		return (print_error(NULL, errno, 1, state), free(path), 1);
	if (pid == 0)
		child_execute(path, cmd->args, args);
	return (parent_handle(pid, path));
}

/**
 * cmd: cmd singular que ejecutar
 * env: nuestro env propio ya generado
 * comprobamos si necesita cambiar la redireccion
 * comprobamos si es un cmd builtin o cmd aparte
 */
static int	execute_single_command(t_cmd *cmd, char ***env, t_state *state)
{
	t_cmd_args	args;
	int			status;

	if (!cmd || !cmd->args)
		return (1);
	args = (t_cmd_args){cmd, env, cmd->settings.pseudo_stdin,
		cmd->settings.pseudo_stdout, 1};
	if (is_builtin(cmd->args[0]))
		status = exec_builtin(cmd, env, state, 1);
	else
		status = execute_command(cmd, &args, state);
	return (status);
}

/**
 * pipe: le pasamos la lista de cmds total
 * env: nuestro env propio ya generado
 * comprobamos que exista la pipeline y que tenga una cantidad
 * si es solo 1 comando, pasamos el cmd a la funcion para salvar lineas de func
 * si es mas de 1, miramos en cada si tiene un heredoc 
 * y al final lo pasamos a la funcion de pipe
 */
int	execute_pipeline(t_pipeline *pipe, char ***env, t_state *state)
{
	if (!pipe)
		return (1);
	if (pipe->amount == 0)
		return (0);
	else if (pipe->amount == 1)
		return (execute_single_command(pipe->cmds[0], env, state));
	return (handle_pipe(pipe->cmds, pipe->amount, state));
}
