/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/07 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_hit	intersect_object(t_object *obj, t_ray ray)
{
	t_hit	hit;

	hit.hit = 0;
	if (obj->type == OBJ_SPHERE)
		hit = intersect_sphere(&obj->data.sphere, ray);
	else if (obj->type == OBJ_PLANE)
		hit = intersect_plane(&obj->data.plane, ray);
	else if (obj->type == OBJ_CYLINDER)
		hit = intersect_cylinder(&obj->data.cylinder, ray);
	else if (obj->type == OBJ_CONE)
		hit = intersect_cone(&obj->data.cone, ray);
	return (hit);
}

t_color3	trace_ray(t_scene *scene, t_ray ray)
{
	t_hit		hit;
	t_color3	color;

	hit = find_closest_hit(scene->objects, ray);
	if (!hit.hit)
		return (vec3_new(0.0, 0.0, 0.0));
	hit.view_dir = vec3_negate(ray.dir);
	if (hit.checker)
		hit.color = apply_checkerboard(hit, hit.color);
	color = compute_lighting_bonus(scene, hit);
	if (scene->mode == MODE_OBJECT
		&& hit.obj_idx == scene->selected_idx)
		color = color_mul(color, 1.2);
	return (color_clamp(color));
}
