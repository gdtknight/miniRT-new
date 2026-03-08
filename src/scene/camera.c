/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/09 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static t_vec3	get_world_up(t_vec3 dir)
{
	t_vec3	world_up;

	world_up = vec3_new(0, 1, 0);
	if (fabs(vec3_dot(dir, world_up)) > 0.999)
		world_up = vec3_new(0, 0, 1);
	return (world_up);
}

void	init_camera_basis(t_camera *cam)
{
	t_vec3	world_up;

	world_up = get_world_up(cam->dir);
	cam->right = vec3_normalize(vec3_cross(world_up, cam->dir));
	cam->up = vec3_cross(cam->dir, cam->right);
}

void	init_camera(t_camera *cam)
{
	double	aspect_ratio;
	double	fov_rad;

	aspect_ratio = (double)WIN_W / (double)WIN_H;
	fov_rad = cam->fov * M_PI / 180.0;
	cam->vp_width = 2.0 * tan(fov_rad / 2.0);
	cam->vp_height = cam->vp_width / aspect_ratio;
}
