/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idle_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/09 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "bonus.h"

void	mark_dirty(t_scene *scene)
{
	scene->dirty = 1;
	gettimeofday(&scene->last_input, NULL);
}

int	idle_callback(t_scene *scene)
{
	t_timeval	now;
	long		elapsed_ms;

	if (!scene->dirty)
		return (0);
	gettimeofday(&now, NULL);
	elapsed_ms = (now.tv_sec - scene->last_input.tv_sec) * 1000
		+ (now.tv_usec - scene->last_input.tv_usec) / 1000;
	if (elapsed_ms < DEBOUNCE_MS)
		return (0);
	scene->dirty = 0;
	render_scene(scene);
	render_hud(scene);
	return (0);
}
