/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:12:15 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/13 00:30:50 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	get_cmdline(char **cmdline, t_minishell **ms);

/**
 * @brief	Runs the minishell main loop
 * @note	This function runs the main loop of the minishell, continuously
 * prompting the user for commands and executing them until termination.
 * It retrieves a command line input from the user, creates a parse tree for
 * the command line, and then traverses and executes the commands represented
 * by the parse tree. If any errors occur during command retrieval, parse tree
 * creation, or tree traversal, it updates the minishell's exit status
 * accordingly. The loop continues until termination is initiated by
 * an external event or command.
 * @param	ms Pointer to the minishell structure (`t_minishell`).
 *	Contains the environment and other necessary data for execution.
 */
void	run_minishell(t_minishell **ms)
{
	int		status;
	char	*cmdline;

	while (true)
	{
		signal_interceptor(INTERACTIVE);
		toggler(IMPLICIT);
		status = get_cmdline(&cmdline, ms);
		if (status == 0)
		{
			(*ms)->root = NULL;
			status = create_tree(cmdline, &((*ms)->root));
			if (status != 0)
				(*ms)->exit_status = status;
			if (status == 0)
				(*ms)->exit_status = traverse_tree(&((*ms)->root), *ms);
			free(cmdline);
		}
		else if (status == EOF)
			break ;
		else if (status == SYNTAX_ERROR)
			(*ms)->exit_status = status;
	}
}

/**
 * @brief	Getting command line input from the user
 * @note	This function prompts the user for a command line input by generating
 * a prompt based on the current minishell status. It then reads the input
 * using the readline library function. If successful, the function adds
 * the input to the command history and validates its syntax. If the input
 * is empty, the function recursively calls itself to get a new command line.
 * If any errors occur during prompt generation, input reading, or syntax
 * validation, appropriate error handling is performed, and the function
 * returns a status code indicating the failure.
 * @param	cmdline Pointer to a pointer to store the command line input
 * @param	ms Pointer to the minishell structure (`t_minishell`)
 * @return	Integer status code indicating the success or failure of the
 * operation
 */
int	get_cmdline(char **cmdline, t_minishell **ms)
{
	int		status;
	char	*prompt;

	status = get_prompt(&prompt, (*ms)->exit_status);
	if (status != 0)
		return (status);
	*cmdline = readline(prompt);
	if (*cmdline == NULL)
	{
		if (handle_ctrl_d(prompt) == MALLOC_ERR)
			ctrl_d_error_handler("Ctrl+d error occured.\n");
		free(prompt);
		return (EOF);
	}
	free(prompt);
	if (ft_strlen(*cmdline) == 0)
	{
		free(*cmdline);
		return (get_cmdline(cmdline, ms));
	}
	add_e_bash_history(*cmdline, ms, 1);
	status = validate_input(*cmdline);
	if (status != 0)
		free(*cmdline);
	return (status);
}
