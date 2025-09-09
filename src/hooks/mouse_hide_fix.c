/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hide_fix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:28:44 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/09 16:30:11 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"
#include "mlx.h"
#include <X11/extensions/Xfixes.h>

void	cub_mouse_hide(t_xvar *xvar, t_win_list *win, int hide)
{
	int	event_return;
	int	err_return;

	event_return = 0;
	err_return = 0;
	if (!XFixesQueryExtension(xvar->display, &event_return, &err_return))
		return ;
	if (hide)
		XFixesHideCursor(xvar->display, win->window);
	else
		XFixesShowCursor(xvar->display, win->window);
	XFlush(xvar->display);
}
