/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static double	solve_quadratic(double a, double b, double disc)
{
	double	t;

	t = (-b - sqrt(disc)) / (2.0 * a);
	if (t > EPSILON)
		return (t);
	t = (-b + sqrt(disc)) / (2.0 * a);
	if (t > EPSILON)
		return (t);
	return (-1.0);
}

t_hit	intersect_sphere(t_sphere *sp, t_ray ray)
{
	t_hit	hit;
	t_vec3	oc;
	double	coef[3];
	double	disc;
	double	t;

	hit.hit = 0;
	oc = vec3_sub(ray.origin, sp->center);
	coef[0] = vec3_dot(ray.dir, ray.dir);
	coef[1] = 2.0 * vec3_dot(oc, ray.dir);
	coef[2] = vec3_dot(oc, oc) - sp->radius * sp->radius;
	disc = coef[1] * coef[1] - 4.0 * coef[0] * coef[2];
	if (disc < 0)
		return (hit);
	t = solve_quadratic(coef[0], coef[1], disc);
	if (t < 0)
		return (hit);
	hit.t = t;
	hit.point = ray_at(ray, t);
	hit.normal = vec3_normalize(vec3_sub(hit.point, sp->center));
	if (vec3_dot(hit.normal, ray.dir) > 0)
		hit.normal = vec3_negate(hit.normal);
	hit.color = sp->color;
	hit.hit = 1;
	return (hit);
}
