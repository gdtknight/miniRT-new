/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	is_in_shadow(t_scene *scene, t_hit hit)
{
	t_vec3		light_dir;
	double		light_dist;
	t_point3	shadow_origin;
	t_ray		shadow_ray;
	t_hit		shadow_hit;

	light_dir = vec3_sub(scene->light.pos, hit.point);
	light_dist = vec3_length(light_dir);
	light_dir = vec3_normalize(light_dir);
	shadow_origin = vec3_add(hit.point, vec3_mul(hit.normal, EPSILON));
	shadow_ray = ray_new(shadow_origin, light_dir);
	shadow_hit = find_closest_hit(scene->objects, shadow_ray);
	if (shadow_hit.hit && shadow_hit.t > EPSILON
		&& shadow_hit.t < light_dist)
		return (1);
	return (0);
}

t_color3	compute_diffuse(t_light *light, t_hit hit)
{
	t_vec3	light_dir;
	double	cos_angle;

	light_dir = vec3_normalize(vec3_sub(light->pos, hit.point));
	cos_angle = vec3_dot(hit.normal, light_dir);
	if (cos_angle < 0.0)
		cos_angle = 0.0;
	return (color_mul(hit.color, cos_angle * light->brightness));
}

t_color3	compute_lighting(t_scene *scene, t_hit hit)
{
	t_color3	ambient;
	t_color3	diffuse;

	ambient = color_mul(hit.color, scene->ambient.ratio);
	ambient = color_hadamard(ambient, scene->ambient.color);
	if (is_in_shadow(scene, hit))
		return (ambient);
	diffuse = compute_diffuse(&scene->light, hit);
	return (color_clamp(color_add(ambient, diffuse)));
}
