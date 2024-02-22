/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_splitter_blocks.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:55:41 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/22 20:33:59 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/*
* Function which contains T_AND or T_OR block of string_splitter() recursion
*
* Input:
* - `node` - new node to embed into the Abstract Syntax Tree (AST) structure
* - `str` - string that coming from readline function
* - `type` - current meta character type
* - `i` - index
* 
* Output:
* - `-1` if malloc error occurs, `1` if success, `0` if condition not met
*/
int	and_if_condition_block(t_node_data **node, char *str, int type, int i)
{
	if (str[i] == AND && str[i - 1] == AND)
	{
		if (round_brackets_check(str, i)
			&& quote_check(str, i, S_QUOTE)
			&& quote_check(str, i, D_QUOTE))
			return (set_node_data_and_or_pipe(node, str, i, T_AND));
		else
			return (string_splitter(node, str, type, i - 2));
	}
	else if (str[i] == PIPE && str[i - 1] == PIPE)
	{
		if (round_brackets_check(str, i)
			&& quote_check(str, i, S_QUOTE)
			&& quote_check(str, i, D_QUOTE))
			return (set_node_data_and_or_pipe(node, str, i, T_OR));
		else
			return (string_splitter(node, str, type, i - 2));
	}
	return (0);
}

/*
* Function which contains T_PIPE block of string_splitter() recursion
*
* Input:
* - `node` - new node to embed into the Abstract Syntax Tree (AST) structure
* - `str` - string that coming from readline function
* - `type` - current meta character type
* - `i` - index
* 
* Output:
* - `-1` if malloc error occurs, `1` if success, `0` if condition not met
*/
int	pipe_block(t_node_data **node, char *str, int type, int i)
{
	if (str[i] == PIPE)
	{
		if (round_brackets_check(str, i)
			&& quote_check(str, i, S_QUOTE)
			&& quote_check(str, i, D_QUOTE))
			return (set_node_data_and_or_pipe(node, str, i, type));
		else
			return (string_splitter(node, str, type, i - 1));
	}
	return (0);
}

/*
* Function which contains T_BRACKET block of string_splitter() recursion
*
* Input:
* - `node` - new node to embed into the Abstract Syntax Tree (AST) structure
* - `str` - string that coming from readline function
* - `type` - current meta character type
* 
* Output:
* - `-1` if malloc error occurs, `1` if success, `0` if condition not met
*/
int	brackets_block(t_node_data **node, char *str, int type)
{
	if (first_nonspace_char_is_bracket(str)
		&& last_nonspace_char_is_bracket(str))
		return (set_node_data_bracket(node, str, type));
	return (0);
}
