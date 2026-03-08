/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_key_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/07 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

int	handle_close_bonus(t_scene *scene)
{
	free_scene(scene);
	exit(0);
	return (0);
}

void	setup_hooks(t_scene *scene)
{
	mlx_hook(scene->win, 2, 1L << 0, handle_keypress_bonus, scene);
	mlx_hook(scene->win, 17, 0, handle_close_bonus, scene);
	mlx_loop_hook(scene->mlx, idle_callback, scene);
}
