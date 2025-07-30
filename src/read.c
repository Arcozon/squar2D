/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:10:48 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/30 17:42:56 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// uint64_t	calc_size(char *old, char read[BUFF_SIZE], uint64_t br)
// {
// 	uint64_t	size;
	
// }

char	*gnl_join(t_read *rd)
{
	uint64_t	new_size;
	uint64_t	len_oline;
	uint64_t	s_space;
	uint64_t	e_space;
	char		*new;
	
	s_space = 0;
	if (rd->flags & R_CUT_S_SPC && !rd->line)
		while (s_space < (uint64_t)rd->br && rd->content[s_space] == ' ')	
			++s_space;
	new_size = s_space;
	while (new_size < (uint64_t)rd->br && rd->content[new_size] != '\n')
		++new_size;
	e_space = 0;
	// DEBUG("[%c]", rd->content[new_size])
	if (new_size < (uint64_t)rd->br)
	{
		DEBUG("LINE DONE")
		rd->flags |= R_LDONE;
		e_space = 1;
	}
	if (rd->flags & R_CUT_E_SPC && e_space)
		while (rd->content[new_size - e_space] == ' ' && e_space < new_size - s_space)
			++e_space;
	if (e_space)
		--e_space;
	len_oline = 0;
	if (rd->line)
		len_oline = ft_strlen(rd->line);
	new_size -= e_space + s_space;
	// DEBUG("[%lu|%lu]-%.*s-", s_space, new_size , (int)new_size, rd->content + s_space);
	new = malloc(sizeof(char) * (len_oline + new_size + 1));
	if (!new)
		return (rd->error = E_MLC, rd->flags |= R_DONE, free(rd->line), rd->line = NULL);
	ft_memcpy(new, rd->line, len_oline);
	ft_memcpy(new + len_oline, rd->content + s_space, new_size);
	new[len_oline + new_size] = '\0';
	DEBUG("LINE: [%s]", new);
	new_size += e_space + s_space + (new_size < (uint64_t)rd->br);
	DEBUG("Newsize: %lu", new_size);
	// DEBUG("br: %d", rd->br)
	// ft_memcpy(rd->content, rd->content + new_size, rd->br -= new_size);
	// DEBUG("%.*s", rd->br, rd->content);
	// DEBUG("[%c|%c] %lu", rd->content[0], rd->content[new_size], rd->br - new_size)
	ft_strlcpy(rd->content, rd->content + new_size, (rd->br -= new_size));
	// WAIT
	// DEBUG("%.*s", rd->br, rd->content);
	
	// DEBUG("Content Start: [%.5s]", rd->content)
	free(rd->line);
	rd->line = new;
	return (rd->line);
}

char	*gnl(t_read *rd)
{
	rd->flags &= ~R_LDONE;
	free(rd->line);
	rd->line = NULL;
	if (rd->br > 0)
		gnl_join(rd);
	while (!rd->error && (rd->flags & (R_DONE | R_LDONE)) == 0)
	{
		DEBUG("READ=--------------------------------------------")
		rd->br = read(rd->fd, rd->content, sizeof(rd->content));
		if (rd->br < 0)
			return (rd->error = E_READ, rd->flags |= R_DONE, free(rd->line), rd->line = NULL);
		if (rd->br == 0)
			return (rd->flags |= R_DONE, rd->line);
		gnl_join(rd);
	}
	return (rd->line);
}
