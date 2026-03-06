/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS

# include "render.h"

static int	is_shadow_light(t_scene *scene, t_hit hit, t_light *light)
{
	t_vec3		light_dir;
	double		light_dist;
	t_point3	shadow_origin;
	t_ray		shadow_ray;
	t_hit		shadow_hit;

	light_dir = vec3_sub(light->pos, hit.point);
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

static t_color3	diffuse_colored(t_light *light, t_hit hit)
{
	t_vec3		light_dir;
	t_color3	diffuse;
	double		cos_angle;

	light_dir = vec3_normalize(vec3_sub(light->pos, hit.point));
	cos_angle = vec3_dot(hit.normal, light_dir);
	if (cos_angle < 0.0)
		cos_angle = 0.0;
	diffuse = color_mul(hit.color, cos_angle * light->brightness);
	diffuse = color_hadamard(diffuse, light->color);
	return (diffuse);
}

static t_color3	sum_lights(t_scene *scene, t_hit hit)
{
	t_color3	sum;
	t_light		*cur;

	sum = color_new(0.0, 0.0, 0.0);
	cur = scene->lights;
	while (cur)
	{
		if (!is_shadow_light(scene, hit, cur))
			sum = color_add(sum, diffuse_colored(cur, hit));
		cur = cur->next;
	}
	return (sum);
}

t_color3	compute_lighting_bonus(t_scene *scene, t_hit hit)
{
	t_color3	ambient;
	t_color3	result;

	ambient = color_mul(hit.color, scene->ambient.ratio);
	ambient = color_hadamard(ambient, scene->ambient.color);
	result = color_add(ambient, sum_lights(scene, hit));
	if (scene->lights)
		result = color_add(result,
				compute_specular(scene->lights, hit, hit.view_dir));
	return (color_clamp(result));
}

#endif
