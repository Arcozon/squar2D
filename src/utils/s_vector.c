/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_vector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:18:24 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/08 13:38:11 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_vector.h"

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
	if (vector->u_ptr.void_ptr)
		ft_memcpy(new_ptr, vector->u_ptr.void_ptr,
			vector->size * vector->sizeof_type);
	free(vector->u_ptr.void_ptr);
	vector->u_ptr.void_ptr = new_ptr;
	vector->capacity *= 2;
	return (NO_ERR);
}

uint32_t	new_vector_minsize(t_vector *vector,
	const uint32_t sizeof_type, const uint64_t min_size)
{
	vector->sizeof_type = sizeof_type;
	vector->size = 0;
	vector->capacity = VECTOR_BASE_SIZE;
	while (vector->capacity < min_size)
		vector->capacity *= 2;
	vector->u_ptr.void_ptr = ft_calloc(sizeof_type * vector->capacity);
	if (!vector->u_ptr.void_ptr)
		return (E_MLC);
	return (NO_ERR);
}

uint32_t	realloc_vector_minsize(t_vector *vector, const uint64_t min_size)
{
	uint64_t	new_capacity;
	void		*new_ptr;

	new_capacity = vector->capacity;
	while (new_capacity < min_size)
		new_capacity *= 2;
	new_ptr = ft_calloc(vector->sizeof_type * new_capacity);
	if (!new_ptr)
		return (E_MLC);
	ft_memcpy(new_ptr, vector->u_ptr.void_ptr,
		vector->sizeof_type * vector->size);
	free(vector->u_ptr.void_ptr);
	vector->u_ptr.void_ptr = new_ptr;
	vector->capacity = new_capacity;
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

uint32_t	str_to_vector(t_vector *vector, const char *str)
{
	const uint64_t	len_str = ft_strlen(str);

	if (new_vector_minsize(vector, sizeof(*str), len_str))
		return (E_MLC);
	return (add_elems_vector(vector, str, len_str));
}
