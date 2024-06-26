/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:41:26 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/05 17:04:32 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Function to expand dollar sign token in a string
 * @note	This function iterates through the string and expands
 * dollar sign tokens into the corresponding expression
 * @param	str Pointer to the string to be expanded
 * @param	envp environment array
 * @param	last_exit_status last exit status to expand
 * @return	@c `SUCCESS` if the expansion is successful,
 * @c `MALLOC_ERR` if memory allocation fails during expansion
 */
int	dollar_sign_expansion(char **str, char **envp, int last_exit_status)
{
	if (expand_dollar_sign_generic(str, envp) == MALLOC_ERR)
		return (MALLOC_ERR);
	if (expand_dollar_sign_q_mark(str, last_exit_status)
		== MALLOC_ERR)
		return (MALLOC_ERR);
	return (SUCCESS);
}
