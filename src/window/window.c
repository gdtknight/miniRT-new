/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_window(t_scene *scene)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
		exit_error("mlx_init failed", scene);
	scene->win = mlx_new_window(scene->mlx, WIN_W, WIN_H, "miniRT");
	if (!scene->win)
		exit_error("mlx_new_window failed", scene);
	scene->img.ptr = mlx_new_image(scene->mlx, WIN_W, WIN_H);
	if (!scene->img.ptr)
		exit_error("mlx_new_image failed", scene);
	scene->img.addr = mlx_get_data_addr(scene->img.ptr,
			&scene->img.bpp, &scene->img.line_len, &scene->img.endian);
}

void	destroy_window(t_scene *scene)
{
	if (scene->img.ptr)
		mlx_destroy_image(scene->mlx, scene->img.ptr);
	scene->img.ptr = NULL;
	if (scene->win)
		mlx_destroy_window(scene->mlx, scene->win);
	scene->win = NULL;
}
