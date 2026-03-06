/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	set_cone_coefs(t_cone *cone, t_ray ray, double coef[4])
{
	t_vec3	w;
	double	da;
	double	wa;
	double	wd;
	double	k;

	w = vec3_sub(ray.origin, cone->apex);
	da = vec3_dot(ray.dir, cone->axis);
	wa = vec3_dot(w, cone->axis);
	wd = vec3_dot(w, ray.dir);
	k = cone->cos_theta * cone->cos_theta;
	coef[0] = da * da - k;
	coef[1] = 2.0 * (wa * da - k * wd);
	coef[2] = wa * wa - k * vec3_dot(w, w);
	coef[3] = coef[1] * coef[1] - 4.0 * coef[0] * coef[2];
}

static t_hit	make_cone_hit(t_cone *cone, t_ray ray, double t)
{
	t_hit	hit;
	t_vec3	v;
	t_vec3	radial;
	double	m;
	double	sin_t;

	hit.hit = 0;
	if (t < EPSILON)
		return (hit);
	hit.point = ray_at(ray, t);
	v = vec3_sub(hit.point, cone->apex);
	m = vec3_dot(v, cone->axis);
	if (m < 0 || m > cone->height)
		return (hit);
	radial = vec3_sub(v, vec3_mul(cone->axis, m));
	sin_t = sqrt(1.0 - cone->cos_theta * cone->cos_theta);
	hit.normal = vec3_sub(
			vec3_mul(vec3_normalize(radial), cone->cos_theta),
			vec3_mul(cone->axis, sin_t));
	if (vec3_dot(hit.normal, ray.dir) > 0)
		hit.normal = vec3_negate(hit.normal);
	hit.color = cone->color;
	hit.t = t;
	hit.hit = 1;
	return (hit);
}

static t_hit	intersect_cone_cap(t_cone *cone, t_ray ray)
{
	t_hit		hit;
	t_point3	cap_c;
	double		denom;
	double		t;

	cap_c = vec3_add(cone->apex, vec3_mul(cone->axis, cone->height));
	denom = vec3_dot(cone->axis, ray.dir);
	hit.hit = 0;
	if (fabs(denom) < EPSILON)
		return (hit);
	t = vec3_dot(vec3_sub(cap_c, ray.origin), cone->axis) / denom;
	if (t < EPSILON)
		return (hit);
	hit.point = ray_at(ray, t);
	if (vec3_length(vec3_sub(hit.point, cap_c)) > cone->radius)
		return (hit);
	hit.normal = cone->axis;
	if (vec3_dot(hit.normal, ray.dir) > 0)
		hit.normal = vec3_negate(hit.normal);
	hit.color = cone->color;
	hit.t = t;
	hit.hit = 1;
	return (hit);
}

t_hit	intersect_cone(t_cone *cone, t_ray ray)
{
	t_hit	body;
	t_hit	cap;
	double	coef[4];

	set_cone_coefs(cone, ray, coef);
	body.hit = 0;
	if (coef[3] >= 0 && fabs(coef[0]) > EPSILON)
	{
		body = make_cone_hit(cone, ray,
				(-coef[1] - sqrt(coef[3])) / (2.0 * coef[0]));
		if (!body.hit)
			body = make_cone_hit(cone, ray,
					(-coef[1] + sqrt(coef[3])) / (2.0 * coef[0]));
	}
	cap = intersect_cone_cap(cone, ray);
	if (body.hit && cap.hit)
	{
		if (body.t < cap.t)
			return (body);
		return (cap);
	}
	if (body.hit)
		return (body);
	return (cap);
}
