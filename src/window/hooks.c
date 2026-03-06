/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define KEY_ESC 53

int	handle_keypress(int keycode, t_scene *scene)
{
	if (keycode == KEY_ESC)
	{
		free_scene(scene);
		exit(0);
	}
	return (0);
}

int	handle_close(t_scene *scene)
{
	free_scene(scene);
	exit(0);
	return (0);
}

void	setup_hooks(t_scene *scene)
{
	mlx_hook(scene->win, 2, 1L << 0, handle_keypress, scene);
	mlx_hook(scene->win, 17, 0, handle_close, scene);
}
