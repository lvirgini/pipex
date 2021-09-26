/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:17:28 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/26 23:27:36 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
pid_t	creating_process(t_cmd *cmd, char *env[])
{
	pid_t	cpid;

	if (cmd->pipe[IN] == -1)
		return (-1);
	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (cpid == 0)
	{
		close(cmd->pipe[IN]);
		//dprintf(2,  "IN FILS : INPUT = %d OUTPUT = %d\n", cmd->input[0], cmd->output[1]);
		if (dup2(cmd->pipe[OUT], 1) == -1)
			perror("dup2 output1");
		exec_command(cmd, env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		dprintf(2, "CPID = %d\n", cpid);
		close(cmd->pipe[OUT]);
	}
	return (cpid);
}
int	create_pipe(t_cmd *cmd, t_cmd *last)
{
	if (pipe(cmd->pipe) == -1)
	{
		perror("pipe");
		return (-1);
	}
	dup2

}

int	make_pipex2(t_cmd *cmd, int nb_cmd, char *env[])
{
	int	i;
	int	*input;

	i = 0;
	while (i < nb_cmd)
	{
		make_pipe(cmd[i]), cmd[i - 1];
		creating_process(cmd[i], env);

	}
}


/*
pid_t	creating_process(t_cmd *cmd, int input_fd[2], int output_fd[2],
	char *env[])
{
	pid_t	cpid;

	if (cmd->input == -1 || input_fd[0] == -1)
		return (-1);
	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (cpid == 0)
	{
		close (input_fd[1]);
		close(output_fd[0]);
		if (dup2(input_fd[0], 0) == -1 || dup2(output_fd[1], 1) == -1)
			perror("dup2");
		exec_command(cmd, env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close (input_fd[0]);
		close(output_fd[1]);
	}
	return (cpid);
}*/

void	copy_pipe_fd(int fd[2], int first, int second)
{
	dup2(first, fd[0]);
	dup2(second, fd[1]);
}
/*
**	INFILE		PIPE 1			PIPE 2			PIPE 3			OUTFILE
**	 --0	1-----------0	1-----------0	1-----------0	1-----
**	|	CD1		|		CD2		|		CD3		|		CD4		|
**
*/
/*
void	add_cmd_input_output(t_cmd *cmd, int input[2], int output[2])
{
	dup2(input[0], cmd->input);
	dup2(output[1], cmd->output);
	copy_pipe_fd(cmd->pipefd_to_close, input[1], output[0]);
}

void	ft_close_multi(int	pipefd[2], int	fd1, int fd2)
{
	if (pipefd)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
}

pid_t	creating_process(t_cmd *cmd, char *env[])
{
	pid_t	cpid;

	if (cmd->input == -1)
	{
		ft_close_multi(cmd->pipefd_to_close, cmd->input, cmd->output);
		return (-1);
	}
	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (cpid == 0)
	{
		ft_close_multi(cmd->pipefd_to_close, -1, -1);
		if (dup2(cmd->input, 0) == -1 || dup2(cmd->output, 1) == -1)
			perror("dup2");
		exec_command(cmd, env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("CPID = %d\n", cpid);
		ft_close_multi(NULL, cmd->input, cmd->output);
	}
	return (cpid);
}

int		add_io_to_cmd(t_cmd *cmd, int input[2], int output[2])
{
	cmd->input = dup(input[0]);
	cmd->output = dup(output[1]);
	return (0);
}*/

/*
**
*/


pid_t	creating_process(t_cmd *cmd, char *env[])
{
	pid_t	cpid;

	if (cmd->input[0] == -1)
	{
		close(cmd->output[1]);
		return (-1);
	}
	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (cpid == 0)
	{
		close(cmd->input[1]);
		close(cmd->output[0]);
		dprintf(2,  "IN FILS : INPUT = %d OUTPUT = %d\n", cmd->input[0], cmd->output[1]);
		if (dup2(cmd->input[0], 0) == -1) //|| dup2(cmd->output[1], 1) == -1)
			perror("dup2 input0");
		if (dup2(cmd->output[1], 1) == -1)
			perror("dup2 output1");

		exec_command(cmd, env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("CPID = %d\n", cpid);
		close(cmd->input[0]);
		close(cmd->output[1]);
	}
	return (cpid);
}



int		close_and_get_new_input(int input[2], int output[2])
{
	close(input[1]);
	close(input[0]);
	close(output[1]);
	dup2(input[0], output[0]);
	return (0);
}

int		create_pipe_between_cmds(t_cmd *cmd1, t_cmd *cmd2)
{
	pipe(cmd2->output);
	dup2(cmd1->output[0], cmd2->input[0]);
	close(cmd1->output[1]);
	return (0);
}

int		execute_pipe(t_cmd *cmd1, t_cmd *cmd2, char *env[])
{
	create_pipe_between_cmds(cmd1, cmd2);
	creating_process(cmd2, env);
	close(cmd2->input[0]);
	close(cmd2->output[1]);
	return (cmd2->output[0]);
}

int	make_pipex2(t_cmd *cmd, int	nb_cmd, char *env[])
{

	int		i;

	dup2(0, cmd[0].input[0]);
	cmd[0].input[1] = -1;
	pipe(cmd[0].output);
	creating_process(&cmd[0], env);
	i = 1;
	/*while (i < nb_cmd)
	{
		execute_pipe(&cmd[i - 1], &cmd[i], env);
		i++;
	}*/
	dup2(cmd[i - 1].output[0], cmd[i].input[0]);
	creating_process(&cmd[i], env);
	close(cmd[i].input[0]);
	return (0);



/*

	dup2(parent_fd[0], pipe_input[0]);
	pipe_input[1] = -1;
	while(cmd)
	{
		add_io_to_cmd(cmd, pipe_input, pipe_output);
		if (cmd->input != -1)
			exec_command(cmd, env);
		close_and_get_new_input(pipe_input, pipe_output);
		cmd++;
	}*/
}

/*
int	make_pipex(t_cmd *cmd, int nb_cmd, int outfile, char *env[])
{
	int		i;
	int		input_fd[2];
	int		output_fd[2];
	pid_t	pid[2];


	i = 0;
	copy_pipe_fd(input_fd, 0, -1);
	while(i < nb_cmd - 1)
	{
		if (pipe(output_fd) == -1)
		{
			perror("pipe");
			return (FAILURE);
		}
		add_cmd_input_output(&cmd[i], input_fd, output_fd);
		pid[i] = creating_process(&cmd[i], env);
		copy_pipe_fd(input_fd, output_fd[0], output_fd[1]);
	}
	output_fd[1] = 1;
	add_cmd_input_output(&cmd[i], input_fd, output_fd);
	pid[i] = creating_process(&cmd[i], env);

	waitpid(pid[0], NULL, WUNTRACED);
	waitpid(pid[1], NULL, WUNTRACED);

	return (SUCCESS);
}*/
/*
int	make_pipex(t_cmd *cmd, int nb_cmd, int outfile, char *env[])
{
	int		i;
	int		input_fd[2];
	int		output_fd[2];
	pid_t	pid[2];

	i = 0;
	add_cmd_input_output(&cmd[i], 0, -1);
	copy_pipe_fd(input_fd, 0, -1);
	while (i < nb_cmd - 1)
	{
		if (pipe(output_fd) == -1)
		{
			perror("pipe");
			return (FAILURE);
		}
		pid[i] = creating_process(&cmd[i], input_fd, output_fd, env);
		copy_pipe_fd(input_fd, output_fd[0], output_fd[1]);
		i++;
	}
	copy_pipe_fd(output_fd, -1, outfile);
	pid[i] = creating_process(&cmd[i], input_fd, output_fd, env);
	waitpid(pid[0], NULL, WUNTRACED);
	waitpid(pid[1], NULL, WUNTRACED);


	return (SUCCESS);
}
*/







	// create pipe
	//lecture sur le pipefd[0]  et écriture sur le pipefd[1].
	//  cmd 1 -> pipefd1 = sortie std (1) -----> pipefd0 = entrée std (0) -> cmd 2
	int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

	// create fork
    pid_t cpid;
	pid_t cpid2;
	
    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) //FILS 1
	{   
		// dans le fils : redirection fd : la sortie std du fils deviens l'entrée std du second fils
		//if (dup2(pipefd[1], 1) == -1)
     	//	perror("dup2");
		//write (1, "test\n", 5);
        exec_command(&cmd[0], env);
        exit(EXIT_SUCCESS);
    }
	else 
	{
		wait(NULL);
		cpid2 = fork();
		if (cpid2 == -1)
		{
       		perror("fork");
        	exit(EXIT_FAILURE);
		}
		if (cpid2 == 0) // FILS 2
		{
			//char	buffer[1024];
   			//int		ret;
   			//int		status;

			close(pipefd[1]);
			//if (dup2(pipefd[0], 0) == -1)
     		//	perror("dup2");
       		exec_command(&cmd[1], env);
        	exit (EXIT_SUCCESS);
		}
	}
	return (0);
}