/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_vector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:18:24 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/08 12:45:34 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 0 no err, ERR_MLC err
uint32_t	new_vector(t_vector *vector, const uint8_t sizeof_type)
{
	vector->sizeof_type = sizeof_type;
	vector->size = 0;
	vector->capacity = VECTOR_BASE_SIZE;
	vector->u_ptr.void_ptr = ft_calloc(sizeof_type * vector->capacity);
	if (!vector->u_ptr.void_ptr)
		return (E_MLC);
	return (NO_ERR);
}

uint32_t	realloc_vector(t_vector *vector)
{
	const uint64_t	new_capacity = vector->capacity * 2;
	const uint64_t	new_size = new_capacity * vector->sizeof_type;
	void			*new_ptr;

	new_ptr = ft_calloc(new_size);
	if (!new_ptr)
		return (E_MLC);
	ft_memcpy(new_ptr, vector->u_ptr.void_ptr, new_size);
	free(vector->u_ptr.void_ptr);
	vector->u_ptr.void_ptr = new_ptr;
	vector->capacity *= 2;
	return (NO_ERR);
}

uint32_t	new_vector_minsize(t_vector *vector,
	const uint8_t sizeof_type, const uint64_t min_size)
{
	vector->sizeof_type = sizeof_type;
	vector->size = 0;
	vector->capacity = VECTOR_BASE_SIZE;
	while (vector->capacity < min_size)
		vector->capacity *= 2;
	vector->u_ptr.void_ptr = ft_calloc(sizeof_type * vector->capacity);
			return (E_MLC);
	return (NO_ERR);
}

uint32_t	add_elem_vector(t_vector *vector, void *to_add, const uint8_t sizeof_toadd)
{
	if (vector->size >= vector->capacity && realloc_vector(vector) == E_MLC)
		return (E_MLC);
	ft_memcpy(vector->u_ptr.void_ptr + vector->size, to_add, sizeof_toadd);
	++vector->size;
	return (NO_ERR);
}
