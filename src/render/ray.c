/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_ray	ray_new(t_point3 origin, t_vec3 dir)
{
	t_ray	ray;

	ray.origin = origin;
	ray.dir = dir;
	return (ray);
}

t_point3	ray_at(t_ray ray, double t)
{
	return (vec3_add(ray.origin, vec3_mul(ray.dir, t)));
}

t_ray	generate_ray(t_camera *cam, int px, int py)
{
	double	u;
	double	v;
	t_vec3	dir;

	u = (2.0 * (px + 0.5) / WIN_W - 1.0) * cam->vp_width / 2.0;
	v = (1.0 - 2.0 * (py + 0.5) / WIN_H) * cam->vp_height / 2.0;
	dir = vec3_add(cam->dir, vec3_add(vec3_mul(cam->right, u),
				vec3_mul(cam->up, v)));
	dir = vec3_normalize(dir);
	return (ray_new(cam->pos, dir));
}
