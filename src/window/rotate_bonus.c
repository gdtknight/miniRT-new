/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/09 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"
#include "render.h"

static t_vec3	rodrigues_rotate(t_vec3 k, t_vec3 v, double angle)
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

static void	apply_yaw(t_camera *cam, int keycode)
{
	t_vec3	new_dir;
	double	angle;

	angle = ROT_STEP * M_PI / 180.0;
	if (keycode == KEY_LEFT)
		angle = -angle;
	new_dir = rodrigues_rotate(cam->up, cam->dir, angle);
	cam->dir = vec3_normalize(new_dir);
}

static void	apply_pitch(t_camera *cam, int keycode)
{
	t_vec3	new_dir;
	double	angle;

	angle = ROT_STEP * M_PI / 180.0;
	if (keycode == KEY_UP)
		angle = -angle;
	new_dir = rodrigues_rotate(cam->right, cam->dir, angle);
	cam->dir = vec3_normalize(new_dir);
}

void	rotate_camera(t_scene *scene, int keycode)
{
	t_camera	*cam;

	if (scene->mode != MODE_CAMERA)
		return ;
	cam = &scene->camera;
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		apply_yaw(cam, keycode);
	if (keycode == KEY_UP || keycode == KEY_DOWN)
		apply_pitch(cam, keycode);
	init_camera(cam);
}
