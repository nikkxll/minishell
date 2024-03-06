/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_simple_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/05 13:24:49 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*validate_simple_command(char *str)
{
	char	*next_token;

	while (*str == SPACE)
		str++;
	next_token = validate_redirect(str);
	if (next_token == str)
		next_token = validate_word(str);
	if (next_token != str)
		next_token = validate_simple_command(next_token);
	return (next_token);
}