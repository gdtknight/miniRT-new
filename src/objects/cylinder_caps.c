/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_hit	check_cy_cap(t_cylinder *cy, t_ray ray,
			t_point3 cap_center, t_vec3 cap_normal)
{
	t_hit	hit;
	t_vec3	diff;
	double	denom;
	double	t;

	hit.hit = 0;
	denom = vec3_dot(cy->axis, ray.dir);
	if (fabs(denom) < EPSILON)
		return (hit);
	diff = vec3_sub(cap_center, ray.origin);
	t = vec3_dot(diff, cy->axis) / denom;
	if (t < EPSILON)
		return (hit);
	hit.point = ray_at(ray, t);
	if (vec3_length(vec3_sub(hit.point, cap_center)) > cy->radius)
		return (hit);
	hit.t = t;
	hit.normal = cap_normal;
	if (vec3_dot(hit.normal, ray.dir) > 0)
		hit.normal = vec3_negate(hit.normal);
	hit.color = cy->color;
	hit.hit = 1;
	return (hit);
}

t_hit	intersect_cy_caps(t_cylinder *cy, t_ray ray)
{
	t_hit		bot;
	t_hit		top;
	t_point3	bot_center;
	t_point3	top_center;

	bot_center = vec3_sub(cy->center, vec3_mul(cy->axis, cy->height / 2.0));
	top_center = vec3_add(cy->center, vec3_mul(cy->axis, cy->height / 2.0));
	bot = check_cy_cap(cy, ray, bot_center, vec3_negate(cy->axis));
	top = check_cy_cap(cy, ray, top_center, cy->axis);
	if (bot.hit && top.hit)
	{
		if (bot.t < top.t)
			return (bot);
		return (top);
	}
	if (bot.hit)
		return (bot);
	return (top);
}
