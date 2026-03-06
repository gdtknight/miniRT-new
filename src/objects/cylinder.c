/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static t_hit	make_body_hit(t_cylinder *cy, t_ray ray, t_point3 bot, double t)
{
	t_hit	hit;
	t_vec3	radial;
	double	m;

	hit.hit = 0;
	if (t < EPSILON)
		return (hit);
	hit.point = ray_at(ray, t);
	m = vec3_dot(vec3_sub(hit.point, bot), cy->axis);
	if (m < 0 || m > cy->height)
		return (hit);
	radial = vec3_sub(vec3_sub(hit.point, bot), vec3_mul(cy->axis, m));
	hit.normal = vec3_normalize(radial);
	if (vec3_dot(hit.normal, ray.dir) > 0)
		hit.normal = vec3_negate(hit.normal);
	hit.color = cy->color;
	hit.t = t;
	hit.hit = 1;
	return (hit);
}

static void	set_cy_coefs(t_cylinder *cy, t_ray ray,
				t_point3 bot, double coef[4])
{
	t_vec3	d_proj;
	t_vec3	oc_proj;
	t_vec3	oc;

	oc = vec3_sub(ray.origin, bot);
	d_proj = vec3_sub(ray.dir,
			vec3_mul(cy->axis, vec3_dot(ray.dir, cy->axis)));
	oc_proj = vec3_sub(oc,
			vec3_mul(cy->axis, vec3_dot(oc, cy->axis)));
	coef[0] = vec3_dot(d_proj, d_proj);
	coef[1] = 2.0 * vec3_dot(d_proj, oc_proj);
	coef[2] = vec3_dot(oc_proj, oc_proj) - cy->radius * cy->radius;
	coef[3] = coef[1] * coef[1] - 4.0 * coef[0] * coef[2];
}

t_hit	intersect_cy_body(t_cylinder *cy, t_ray ray)
{
	t_hit		hit;
	t_point3	bot;
	double		coef[4];

	bot = vec3_sub(cy->center, vec3_mul(cy->axis, cy->height / 2.0));
	set_cy_coefs(cy, ray, bot, coef);
	if (coef[3] < 0 || coef[0] < EPSILON)
	{
		hit.hit = 0;
		return (hit);
	}
	hit = make_body_hit(cy, ray, bot,
			(-coef[1] - sqrt(coef[3])) / (2.0 * coef[0]));
	if (hit.hit)
		return (hit);
	return (make_body_hit(cy, ray, bot,
			(-coef[1] + sqrt(coef[3])) / (2.0 * coef[0])));
}

t_hit	intersect_cylinder(t_cylinder *cy, t_ray ray)
{
	t_hit	body;
	t_hit	caps;

	body = intersect_cy_body(cy, ray);
	caps = intersect_cy_caps(cy, ray);
	if (body.hit && caps.hit)
	{
		if (body.t < caps.t)
			return (body);
		return (caps);
	}
	if (body.hit)
		return (body);
	return (caps);
}
