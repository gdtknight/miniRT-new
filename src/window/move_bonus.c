/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/07 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static t_point3	*get_obj_pos(t_object *obj)
{
	if (obj->type == OBJ_SPHERE)
		return (&obj->data.sphere.center);
	else if (obj->type == OBJ_PLANE)
		return (&obj->data.plane.point);
	else if (obj->type == OBJ_CYLINDER)
		return (&obj->data.cylinder.center);
	else if (obj->type == OBJ_CONE)
		return (&obj->data.cone.apex);
	return (NULL);
}

static void	move_camera(t_camera *cam, int keycode)
{
	if (keycode == KEY_W)
		cam->pos = vec3_add(cam->pos, vec3_mul(cam->dir, MOVE_STEP));
	else if (keycode == KEY_S)
		cam->pos = vec3_sub(cam->pos, vec3_mul(cam->dir, MOVE_STEP));
	else if (keycode == KEY_A)
		cam->pos = vec3_sub(cam->pos, vec3_mul(cam->right, MOVE_STEP));
	else if (keycode == KEY_D)
		cam->pos = vec3_add(cam->pos, vec3_mul(cam->right, MOVE_STEP));
	else if (keycode == KEY_R)
		cam->pos.y += MOVE_STEP;
	else if (keycode == KEY_F)
		cam->pos.y -= MOVE_STEP;
}

static void	move_pos(t_point3 *pos, int keycode)
{
	if (keycode == KEY_W)
		pos->z += MOVE_STEP;
	else if (keycode == KEY_S)
		pos->z -= MOVE_STEP;
	else if (keycode == KEY_A)
		pos->x -= MOVE_STEP;
	else if (keycode == KEY_D)
		pos->x += MOVE_STEP;
	else if (keycode == KEY_R)
		pos->y += MOVE_STEP;
	else if (keycode == KEY_F)
		pos->y -= MOVE_STEP;
}

void	move_target(t_scene *scene, int keycode)
{
	t_object	*obj;
	t_point3	*pos;

	if (scene->mode == MODE_CAMERA)
	{
		move_camera(&scene->camera, keycode);
		return ;
	}
	if (scene->mode == MODE_LIGHT)
	{
		move_pos(&scene->light.pos, keycode);
		return ;
	}
	obj = get_object_by_idx(scene->objects, scene->selected_idx);
	if (!obj)
		return ;
	pos = get_obj_pos(obj);
	if (!pos)
		return ;
	move_pos(pos, keycode);
}
