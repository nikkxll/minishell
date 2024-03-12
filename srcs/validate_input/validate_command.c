/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/11 12:26:33 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// <v_input> 		::=  <and_or> <newline>
// <and_or>			::=  <pipeline> { ('&&' | '||') <pipeline> }
// <pipeline>		::=  <command> { '|' <command> }
// <command>		::=  <simple_cmd> | '(' <and_or> ')' {<redirect>}
// <simple_cmd>		::=  {( <redirect> | <word> | "any" | 'any')}
// <redirect>		::=  ( '<' | '>' | '<<' | '>>' ) <word>

static char	*validate_brackets(char *str, t_bool *status);

char	*validate_command(char *str, t_bool *status)
{
	char	*next_token;

	next_token = validate_simple_command(str, status);
	if (next_token != str || *status == false)
		return (next_token);
	else if (*str == O_ROUND)
	{
		if (is_blank_string(str + 1) == true)
		{
			*status = false;
			return (str + 1);
		}
		next_token = validate_brackets(str + 1, status);
	}
	return (next_token);
}

static char	*validate_brackets(char *str, t_bool *status)
{
	char	*next_token;

	while (*str == SPACE)
		str++;
	next_token = validate_and_or(str, status);
	if (next_token == str || *status == false)
		return (str);
	if (*next_token != C_ROUND)
	{
		*status = false;
		return (next_token);
	}
	next_token++;
	while (*next_token == SPACE)
		next_token++;
	next_token = validate_redirect(next_token, status);
	return (next_token);
}
