/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_verctor_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:10:47 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 13:41:27 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_vector.h"

uint32_t	realloc_vector(t_vector *vector)
{
	const uint64_t	new_capacity = vector->capacity * 2;
	const uint64_t	new_size = new_capacity * vector->sizeof_type;
	void			*new_ptr;

	new_ptr = ft_calloc(new_size);
	if (!new_ptr)
		return (E_MLC);
	if (vector->u_ptr.void_ptr)
		ft_memcpy(new_ptr, vector->u_ptr.void_ptr,
			vector->size * vector->sizeof_type);
	free(vector->u_ptr.void_ptr);
	vector->u_ptr.void_ptr = new_ptr;
	vector->capacity *= 2;
	return (NO_ERR);
}

uint32_t	add_elems_vector(t_vector *vector,
	const void *to_add, const uint64_t nelemtoadd)
{
	void	*v_ptr;

	while (vector->capacity < vector->size + nelemtoadd)
		if (realloc_vector(vector) == E_MLC)
			return (E_MLC);
	v_ptr = vector->u_ptr.void_ptr + (vector->size * vector->sizeof_type);
	ft_memcpy(v_ptr, to_add, nelemtoadd * vector->sizeof_type);
	vector->size += nelemtoadd;
	return (NO_ERR);
}
