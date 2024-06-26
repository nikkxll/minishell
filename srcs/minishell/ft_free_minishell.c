/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:01:52 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/12 19:58:56 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Freeing memory allocated for a minishell structure and its
 * components
 * @note	This function frees the memory allocated for a minishell structure
 * @c `t_minishell` and its associated components, including the environment
 * variables @c `env`, the present working directory @c `pwd`, and the old
 * working directory @c `oldpwd`. It first checks if the provided minishell
 * pointer is valid (@c `NULL` check). If it is, it proceeds to free each
 * component if it has been allocated
 * @param	ms Pointer to the minishell structure to be freed
 * @return	@c `void`
 */
void	ft_free_minishell(t_minishell *ms)
{
	if (!ms)
		return ;
	if (ms->env)
		ft_free_2d_array(ms->env);
	if (ms->pwd)
		free(ms->pwd);
	if (ms->oldpwd)
		free(ms->oldpwd);
	if (ms->history_path)
		free(ms->history_path);
	if (ms->history)
		ft_lstclear(&(ms->history), free);
	if (ms->root)
		free_tree(&(ms->root));
	free(ms);
}
