/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_rotate_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/09 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"
#include "render.h"

static t_vec3	rodrigues(t_vec3 k, t_vec3 v, double angle)
{
	t_vec3	new_dir;
	t_vec3	cross_kv;
	double	dot_kv;
	double	cos_a;
	double	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	cross_kv = vec3_cross(k, v);
	dot_kv = vec3_dot(k, v);
	new_dir = vec3_add(vec3_mul(v, cos_a),
			vec3_add(vec3_mul(cross_kv, sin_a),
				vec3_mul(k, dot_kv * (1.0 - cos_a))));
	return (new_dir);
}

static t_vec3	*get_obj_axis(t_object *obj)
{
	if (obj->type == OBJ_PLANE)
		return (&obj->data.plane.normal);
	if (obj->type == OBJ_CYLINDER)
		return (&obj->data.cylinder.axis);
	if (obj->type == OBJ_CONE)
		return (&obj->data.cone.axis);
	return (NULL);
}

static void	apply_obj_yaw(t_vec3 *axis, t_vec3 *local_up, double angle)
{
	*axis = vec3_normalize(rodrigues(*local_up, *axis, angle));
}

static void	apply_obj_pitch(t_vec3 *axis, t_vec3 *local_up, double angle)
{
	t_vec3	right;

	right = vec3_normalize(vec3_cross(*local_up, *axis));
	*axis = vec3_normalize(rodrigues(right, *axis, angle));
	*local_up = vec3_normalize(rodrigues(right, *local_up, angle));
}

void	rotate_object(t_scene *scene, int keycode)
{
	t_object	*obj;
	t_vec3		*axis;
	double		angle;

	obj = get_object_by_idx(scene->objects, scene->selected_idx);
	if (!obj)
		return ;
	axis = get_obj_axis(obj);
	if (!axis)
		return ;
	angle = ROT_STEP * M_PI / 180.0;
	if (keycode == KEY_LEFT || keycode == KEY_UP)
		angle = -angle;
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		apply_obj_yaw(axis, &obj->local_up, angle);
	else
		apply_obj_pitch(axis, &obj->local_up, angle);
}
