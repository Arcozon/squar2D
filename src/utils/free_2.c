/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:59:42 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 12:59:48 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_vector(t_vector *vector)
{
	free(vector->u_ptr.void_ptr);
	vector->u_ptr.void_ptr = 0;
}

void	free_2d_vector(t_vector *vector)
{
	uint64_t	i;

	if (!vector->u_ptr.void_ptr)
		return ;
	i = 0;
	while (i < vector->size)
	{
		free_vector(&vector->u_ptr.vect_ptr[i]);
		++i;
	}
	free_vector(vector);
}

void	free_strstr(char **strstr, const uint32_t size)
{
	uint32_t	i;

	i = 0;
	if (strstr)
	{
		while (i < size)
		{
			free(strstr[i]);
			++i;
		}
		free(strstr);
	}
}
