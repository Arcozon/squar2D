/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_vector.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:58:22 by gaeudes           #+#    #+#             */
/*   Updated: 2025/08/21 16:03:09 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_VECTOR_H
# define S_VECTOR_H

# include <stdlib.h>

# include "types.h"
# include "utils.h"
# include "errors.h"

# define VECTOR_BASE_SIZE 16

struct s_vector
{
	uint32_t		sizeof_type;
	union	__attribute__((transparent_union, may_alias))
	{
		void		*void_ptr;
		char		*char_ptr;
		char		**cchar_ptr;
		t_vector	*vect_ptr;
	}				u_ptr;
	uint64_t		size;

	uint64_t		capacity;
};

uint32_t	new_vector(t_vector *vector, const uint8_t sizeof_type);
uint32_t	new_vector_minsize(t_vector *vector,
				const uint32_t sizeof_type, const uint64_t min_size);
uint32_t	realloc_vector(t_vector *vector);
uint32_t	realloc_vector_minsize(t_vector *vector, const uint64_t min_size);
uint32_t	add_elems_vector(t_vector *vector, const void *to_add,
				const uint64_t nelemtoadd);
uint32_t	str_to_vector(t_vector *vector, const char *str);

#endif
