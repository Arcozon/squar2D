/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:23:05 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/30 14:51:42 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

# include "types.h"

# define STRLEN_LOW_MASK	0x01010101
# define STRLEN_HIGH_MASK	0x80808080

uint64_t	ft_strlen(const char str[])__attribute__ ((pure, nonnull));
uint64_t	heap_strlen(const char str[])__attribute__ ((pure, nonnull, hot));
bool		ft_strendcmp(const char str[],
				const char end[])__attribute__ ((pure, nonnull, flatten));

void		ft_strlcpy(char *dst, const char *src, uint64_t dst_size)
			__attribute__((flatten, nonnull));
void		ft_strnlcpy(char *dst, const char *src,
				uint64_t dst_size, uint64_t src_size)
			__attribute__((flatten, nonnull));
void		ft_lutoacpy(const uint64_t nb, char str[], const uint64_t size)
			__attribute__((flatten, nonnull));
void		ft_strlcat(char *dst, const char *src, uint64_t dst_size)
			__attribute__((flatten, nonnull));

uint64_t	index_strchr(const char str[], const char find)
			__attribute__((nonnull, pure));
char		*ft_strchr(const char str[], const char to_find)
			__attribute__((nonnull, pure, flatten));
char		*ft_sn_strchr(const char str[], const uint64_t lenstr,
				const char tofind[])__attribute__((nonnull, pure, flatten));
char		*ft_strrchr(const char str[], const char to_find)
			__attribute__((nonnull, pure, flatten));
char		*ft_sn_strrchr(const char str[], const uint64_t lenstr,
				const char tofind[])__attribute__((nonnull, pure, flatten));

void		*ft_calloc(const uint64_t	size);
void		*ft_bzero(void *vptr, uint64_t size);
void		*ft_memcpy(void *dst, const void *src, uint64_t size);
void		*ft_memset(void *ptr, uint64_t size, const uint64_t set);

void		free_2d_vector(t_vector *vector);
void		free_strstr(char **strstr, const uint32_t size);
void		free_vector(t_vector *vector);

# define R_DONE			0b1
# define R_LDONE		0b10
# define R_CUT_S_SPC	0b100
# define R_CUT_E_SPC	0b1000

struct s_read
{
	int			fd;
	int			br;
	char		content[BUFF_SIZE];

	char		*line;
	uint8_t		flags;
	t_err		error;
};

char		*gnl(t_read *rd);

#endif
