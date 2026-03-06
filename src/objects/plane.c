/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_hit	intersect_plane(t_plane *pl, t_ray ray)
{
	t_hit	hit;
	t_vec3	diff;
	double	denom;
	double	t;

	hit.hit = 0;
	denom = vec3_dot(pl->normal, ray.dir);
	if (fabs(denom) < EPSILON)
		return (hit);
	diff = vec3_sub(pl->point, ray.origin);
	t = vec3_dot(diff, pl->normal) / denom;
	if (t < EPSILON)
		return (hit);
	hit.t = t;
	hit.point = ray_at(ray, t);
	hit.normal = pl->normal;
	if (vec3_dot(hit.normal, ray.dir) > 0)
		hit.normal = vec3_negate(hit.normal);
	hit.color = pl->color;
	hit.hit = 1;
	return (hit);
}
