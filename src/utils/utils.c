/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:29:01 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/26 16:25:35 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

uint64_t	ft_strlen(char str[])
{
	uint64_t	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

bool		ft_strendcmp(char str[], char end[])
{
	const uint64_t	str_len = ft_strlen(str);	
	const uint64_t	str_end = ft_strlen(end);	
	uint64_t		i;

	i = 0;
	if (str_len < str_end)
		return (false);
	while (i <= str_end)
	{
		if (str[str_len - i] != end[str_end - i])
			return (false);
		++i;
	}
	return (true);
}
